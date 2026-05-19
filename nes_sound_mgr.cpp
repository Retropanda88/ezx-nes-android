#include "nes/types.h"
#include "nes_sound_mgr.h"
#include "nes/debug.h"
#include <string.h>

#define NES_FREGMENT	(10 | 4 << 16)
#define NES_CHANNELS	1

// ====================================================
// SOLUCIÓN: Creamos un bloque de memoria real en RAM 
// para que el emulador escriba sin crashear en Android
// ====================================================
static uint8_t FakeAudioBuffer[SOUND_BUF_LEN * 4]; 

ezx_sound_mgr::ezx_sound_mgr(bool mute)
{
    buffer_locked = false;
    dspfd = -1; // Desactivamos el hardware obsoleto de 2006
    memset(FakeAudioBuffer, 0, sizeof(FakeAudioBuffer));
}

ezx_sound_mgr::~ezx_sound_mgr()
{
    dspfd = -1;
}

boolean ezx_sound_mgr::lock(sound_buf_pos, void** buf, uint32* buf_len)
{
    if (buffer_locked) return false;
  
    buffer_locked = true;
    
    // ASIGNACIÓN SEGURA: Le entregamos al emulador nuestro arreglo real en RAM.
    // Al escribir aquí, Android no detectará un acceso ilegal.
    *buf = (void*)FakeAudioBuffer;
    *buf_len = SOUND_BUF_LEN;
    
    return true;
}

void ezx_sound_mgr::unlock()
{
    if (!buffer_locked) return;
    buffer_locked = false;
    
    // Omitimos ezx_play_dsp ya que no estamos en el procesador físico de 2006
}

sound_mgr::sound_buf_pos ezx_sound_mgr::get_currently_playing_half()
{
    static sound_mgr::sound_buf_pos last = SOUND_BUF_HIGH;
  
    if (last == SOUND_BUF_HIGH)
        last = SOUND_BUF_LOW;
    else
        last = SOUND_BUF_HIGH;
  
    return last;
}

void ezx_sound_mgr::ezx_pause(bool pause, bool mute)
{
    // No requiere lógica física en C4droid
}

int ezx_sound_mgr::get_sample_rate() 
{ 
    return SAMPLE_RATE;
}

int ezx_sound_mgr::get_sample_bits() 
{ 
    return SAMPLE_BITS;
}

boolean ezx_sound_mgr::IsNull() 
{ 
    return FALSE;
}
