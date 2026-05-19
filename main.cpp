#include <SDL/SDL.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "nes/nes.h"
#include "nes_sound_mgr.h"

// ==========================================
// CONFIGURACIÓN CONSTANTES DE PRODUCCIÓN
// ==========================================
#define SCREEN_WIDTH      320
#define SCREEN_HEIGHT     240
#define SCREEN_BPP        16
#define TARGET_FPS        60
#define DELAY_FRAME       (1000 / TARGET_FPS)

#define NES_WIDTH         256 // Ancho real de la imagen NES

#define SAVE_STATE_SLOT   "save_slot0.sav"

// Búfer original requerido por la estabilidad del core
static uint16_t VideoBuffer[SCREEN_HEIGHT][SCREEN_WIDTH];

// Instancias globales del sistema
static NES *emu               = NULL;
static ezx_sound_mgr *snd_mgr = NULL;

// Requerido por la interfaz del núcleo del emulador
uint16 get_nesscreen_pixel_color(int x, int y)
{
    return 0;
}

// ==========================================
// FUNCIÓN DE ESCALADO DE VIDEO (INTEGRADA)
// ==========================================
void render_scaled_frame(SDL_Surface *screen)
{
    SDL_LockSurface(screen);

    for (int y = 0; y < SCREEN_HEIGHT; y++)
    {
        // Puntero a la fila actual en la pantalla de destino de SDL (320px)
        uint16_t* dest_row = (uint16_t*)((uint8_t*)screen->pixels + (y * screen->pitch));
        
        // Sintaxis nativa y limpia para punteros bidimensionales en G++ 64-bits
        uint16_t* src_row = VideoBuffer[y];

        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            // Ajustado a 16 para capturar el inicio real de la pantalla NES de forma simétrica
            int nes_x = 16 + (x * NES_WIDTH) / SCREEN_WIDTH;
            
            // Asignamos el píxel escalado directamente ocupando todo el ancho
            dest_row[x] = src_row[nes_x];
        }
    }

    SDL_UnlockSurface(screen);
}

// ==========================================
// CONTROL DE EVENTOS DE ENTRADA (FORMAL)
// ==========================================
void handle_input_event(SDL_Event *event, NES_pad *pad, bool *running)
{
    bool is_pressed = (event->type == SDL_KEYDOWN);
    
    switch (event->key.keysym.sym)
    {
        // Dirección (D-Pad)
        case SDLK_UP:     pad->nes_UP    = is_pressed; break;
        case SDLK_DOWN:   pad->nes_DOWN  = is_pressed; break;
        case SDLK_LEFT:   pad->nes_LEFT  = is_pressed; break;
        case SDLK_RIGHT:  pad->nes_RIGHT = is_pressed; break;
        
        // Botones de Acción principales
        case SDLK_z:      pad->nes_A     = is_pressed; break; 
        case SDLK_x:      pad->nes_B     = is_pressed; break; 
        
        // Sistema clásico
        case SDLK_RETURN: pad->nes_START  = is_pressed; break; 
        case SDLK_SPACE:  pad->nes_SELECT = is_pressed; break; 
        
        // Atajos de Sistema Avanzados
        case SDLK_F5: 
            if (is_pressed && emu) {
                if (emu->saveState(SAVE_STATE_SLOT)) {
                    printf("SISTEMA: Partida guardada con éxito.\n");
                }
            }
            break;
            
        case SDLK_F6: 
            if (is_pressed && emu) {
                if (emu->loadState(SAVE_STATE_SLOT)) {
                    printf("SISTEMA: Partida cargada con éxito.\n");
                }
            }
            break;
            
        case SDLK_F9: 
            if (is_pressed && emu) {
                emu->reset();
                printf("SISTEMA: Consola reiniciada.\n");
            }
            break;
            
        case SDLK_ESCAPE: 
            if (is_pressed) {
                *running = false;
            }
            break;
            
        default:
            break;
    }
}

// ==========================================
// FUNCIÓN PRINCIPAL DEL SISTEMA
// ==========================================
int main(int argc, char *argv[])
{
    SDL_Surface *screen = NULL;
    SDL_Event event;
    bool running = true;

    printf("[INFO] Iniciando subsistemas del emulador...\n");

    // 1. Inicialización de Librería Gráfica con Soporte de Audio Explícito
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0)
    {
        fprintf(stderr, "[ERROR] No se pudo inicializar SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Superficie por software para entornos móviles (C4droid)
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    if (!screen)
    {
        fprintf(stderr, "[ERROR] Modo de video inválido: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    printf("[OK] Video e Inicializadores básicos listos.\n");

    // 2. Inicialización del Sistema de Audio
    snd_mgr = new ezx_sound_mgr(false);
    if (!snd_mgr || !snd_mgr->initialize())
    {
        fprintf(stderr, "[ERROR] Error al levantar el Admin de Sonido.\n");
        SDL_Quit();
        return 1;
    }
    printf("[OK] Sistema de Audio inicializado.\n");

    // 3. Inicialización del Core del Emulador NES
    emu = new NES(snd_mgr);
    if (!emu)
    {
        fprintf(stderr, "[ERROR] No se pudo construir la CPU NES.\n");
        delete snd_mgr;
        SDL_Quit();
        return 1;
    }

    // Carga de Cartucho
    if (!emu->initialize("game.nes"))
    {
        fprintf(stderr, "[ERROR] Error Crítico: No se pudo leer el archivo 'game.nes'.\n");
        delete emu;
        delete snd_mgr;
        SDL_Quit();
        return 1;
    }
    printf("[OK] Cartucho cargado y verificado en memoria.\n");

    // Forzar activación del chip de audio extendido
    emu->set_exsound_enable(true);

    // Limpieza física del búfer de intercambio de fotogramas
    memset(VideoBuffer, 0, sizeof(VideoBuffer));
    
    // Conversión explícita a puntero simple para el emulador
    uint16_t *fb = (uint16_t*)VideoBuffer;

    // Obtener la referencia interna del control del jugador 1
    NES_pad *pad = emu->get_pad(0);

    printf("[INFO] Entrando al bucle principal de ejecución...\n");

    // Variable para rastrear el tiempo exacto del sistema
    uint32_t tiempo_siguiente_frame = SDL_GetTicks();

    // ==========================================
    // BUCLE DE EJECUCIÓN PRINCIPAL (MAIN LOOP)
    // ==========================================
    while (running)
    {
        // Procesamiento ininterrumpido de eventos de entrada
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
            {
                handle_input_event(&event, pad, &running);
            }
        }

        // REGULADOR DE VELOCIDAD OPTIMIZADO: Sincroniza a 60 FPS sin bloquear hilos
        uint32_t tiempo_actual = SDL_GetTicks();
        if (tiempo_actual >= tiempo_siguiente_frame)
        {
            // Protección contra retrasos severos de hardware
            if (tiempo_actual > tiempo_siguiente_frame + 100) {
                tiempo_siguiente_frame = tiempo_actual;
            }

            // Ejecución del fotograma NES
            if (emu && fb) 
            {
                emu->emulate_frame(fb);
            }

            // Renderizado con escalado inteligente adaptado de 16px
            render_scaled_frame(screen);

            // Volcar búfer de intercambio a pantalla física
            SDL_Flip(screen);

            // Programamos el siguiente ciclo exactamente a 60 FPS
            tiempo_siguiente_frame += DELAY_FRAME;
        }
        else
        {
            // Cede el control de forma milimétrica para no saturar la CPU
            SDL_Delay(1); 
        }
    }

    // ==========================================
    // CIERRE SEGURO Y LIMPIEZA DE MEMORIA (CLEANUP)
    // ==========================================
    printf("[INFO] Cerrando emulador y liberando recursos...\n");
    
    if (emu)     delete emu;
    if (snd_mgr) delete snd_mgr;

    SDL_Quit();
    printf("[OK] Aplicación finalizada con éxito.\n");

    return 0;
}
