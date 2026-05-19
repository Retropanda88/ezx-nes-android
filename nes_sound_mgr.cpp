#include <SDL/SDL.h>
#include <string.h>
#include <stdio.h>
#include "nes/types.h"
#include "nes_sound_mgr.h"
#include "nes/debug.h"

// Redefinimos el búfer circular para que mida exactamente en base a muestras de 16-bit
// Usamos 735 muestras por bloque (SOUND_BUF_LEN / 2) con un multiplicador amplio de amortiguación
#define SAMPLES_PER_BLOCK   735
#define RING_SAMPLES_SIZE   (SAMPLES_PER_BLOCK * 16)

// El búfer intermedio que usa el emulador para depositar las muestras
static uint8_t FakeAudioBuffer[SOUND_BUF_LEN * 4]; 
static uint32_t write_offset = 0;

// SOLUCIÓN AL "GRRR": Forzamos a la cola circular a almacenar datos nativos de 16-bit
static int16_t RingBuffer[RING_SAMPLES_SIZE];
static volatile uint32_t ring_head = 0;
static volatile uint32_t ring_tail = 0;

// Búfer de respaldo unificado a 16-bit para evitar chasquidos en los vacíos
static int16_t LastValidBuffer[SAMPLES_PER_BLOCK];
static bool has_valid_backup = false;

// ====================================================
// CALLBACK SDL 1.2: El hardware extrae sonido alineado
// ====================================================
void sdl_audio_callback(void *userdata, uint8_t *stream, int len)
{
    // SDL pide los datos en bytes (len), pero nuestro hardware trabaja a 16 bits (2 bytes por muestra)
    int samples_requested = len / sizeof(int16_t);
    int16_t *dest_stream = (int16_t*)stream;

    // Calculamos el espacio ocupado medido estrictamente en muestras de 16-bit
    uint32_t head = ring_head;
    uint32_t tail = ring_tail;
    uint32_t available_samples = (head >= tail) ? (head - tail) : (RING_SAMPLES_SIZE - tail + head);

    // Si la CPU del emulador se retrasa y no hay suficientes muestras listas
    if (available_samples < (uint32_t)samples_requested) {
        if (has_valid_backup) {
            // Repetimos de forma limpia la última onda generada en lugar de meter silencio o estática
            int to_copy = (samples_requested > SAMPLES_PER_BLOCK) ? SAMPLES_PER_BLOCK : samples_requested;
            memcpy(dest_stream, LastValidBuffer, to_copy * sizeof(int16_t));
            
            // Si el canal pide más datos de los que tiene el respaldo, el resto va a cero suave
            if (samples_requested > to_copy) {
                memset(dest_stream + to_copy, 0, (samples_requested - to_copy) * sizeof(int16_t));
            }
        } else {
            memset(stream, 0, len);
        }
        return;
    }

    // Extracción atómica de 16 bits: Se respeta el signo y la forma de la onda de la NES
    for (int i = 0; i < samples_requested; i++) {
        dest_stream[i] = RingBuffer[ring_tail];
        ring_tail = (ring_tail + 1) % RING_SAMPLES_SIZE;
    }
}

// ====================================================
// CONSTRUCTOR: Inicialización limpia del bus de audio
// ====================================================
ezx_sound_mgr::ezx_sound_mgr(bool dummy)
{
    buffer_locked = false;
    dspfd = -1; 
    memset(FakeAudioBuffer, 0, sizeof(FakeAudioBuffer));
    memset(RingBuffer, 0, sizeof(RingBuffer));
    memset(LastValidBuffer, 0, sizeof(LastValidBuffer));
    has_valid_backup = false;
    ring_head = 0;
    ring_tail = 0;

    SDL_AudioSpec wanted;
    wanted.freq     = SAMPLE_RATE;          // 22050 Hz
    wanted.format   = AUDIO_S16SYS;         // 16 bits nativos con signo
    wanted.channels = 2;                    // Mono
    wanted.samples  = 512;                  // Búfer bajo para máxima respuesta táctil y sónica
    wanted.callback = sdl_audio_callback;   
    wanted.userdata = NULL;

    if (SDL_OpenAudio(&wanted, NULL) < 0) {
        fprintf(stderr, "[AUDIO ERROR] Imposible abrir mezclador: %s\n", SDL_GetError());
    } else {
        SDL_PauseAudio(0); // Abrir compuertas del mezclador Android
    }
}

ezx_sound_mgr::~ezx_sound_mgr()
{
    SDL_CloseAudio(); 
    dspfd = -1;
}

// ====================================================
// MÉTODOS DE INTERCAMBIO CON EL EMULADOR
// ====================================================
boolean ezx_sound_mgr::lock(sound_buf_pos pos, void** buf, uint32* buf_len)
{
    if (buffer_locked) return false;
    buffer_locked = true;
    
    if (pos == SOUND_BUF_LOW) {
        write_offset = 0;
    } else {
        write_offset = SOUND_BUF_LEN;
    }
    
    *buf = (void*)(FakeAudioBuffer + write_offset);
    *buf_len = SOUND_BUF_LEN;
    
    return true;
}

void ezx_sound_mgr::unlock()
{
    if (!buffer_locked) return;
    buffer_locked = false;

    // Convertimos el búfer plano de la NES a un puntero real de 16-bit
    int16_t *src_samples = (int16_t*)(FakeAudioBuffer + write_offset);

    // Guardamos la ráfaga de respaldo en su formato correcto de 16-bit
    memcpy(LastValidBuffer, src_samples, SAMPLES_PER_BLOCK * sizeof(int16_t));
    has_valid_backup = true;

    uint32_t head = ring_head;
    uint32_t tail = ring_tail;
    uint32_t ocupado = (head >= tail) ? (head - tail) : (RING_SAMPLES_SIZE - tail + head);
    uint32_t espacio_libre = RING_SAMPLES_SIZE - ocupado - 1;

    // Si el búfer circular se encuentra al límite, adelantamos el puntero de salida (Soft Drop)
    // para liberar espacio sin romper el bloque de 16 bits
    if (espacio_libre < SAMPLES_PER_BLOCK) {
        SDL_LockAudio();
        ring_tail = (ring_tail + SAMPLES_PER_BLOCK) % RING_SAMPLES_SIZE;
        SDL_UnlockAudio();
    }

    // Inyectamos las muestras completas de 16-bit en la cola circular de SDL
    SDL_LockAudio();
    for (uint32_t i = 0; i < SAMPLES_PER_BLOCK; i++) {
        RingBuffer[ring_head] = src_samples[i];
        ring_head = (ring_head + 1) % RING_SAMPLES_SIZE;
    }
    SDL_UnlockAudio();
}

sound_mgr::sound_buf_pos ezx_sound_mgr::get_currently_playing_half()
{
    static sound_mgr::sound_buf_pos last = SOUND_BUF_HIGH;
    last = (last == SOUND_BUF_HIGH) ? SOUND_BUF_LOW : SOUND_BUF_HIGH;
    return last;
}

void ezx_sound_mgr::ezx_pause(bool pause, bool dummy)
{
    SDL_PauseAudio(pause ? 1 : 0);
}

int ezx_sound_mgr::get_sample_rate() { return SAMPLE_RATE; }
int ezx_sound_mgr::get_sample_bits() { return SAMPLE_BITS; }
boolean ezx_sound_mgr::IsNull() { return FALSE; }
