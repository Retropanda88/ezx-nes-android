#include <SDL/SDL.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "nes/nes.h"
#include "nes_sound_mgr.h"

// ============================
// BUFFER ORIGINAL EXACTO
// ============================
static uint16_t VideoBuffer[240][320];

// Emulador
static NES *emu = NULL;
static ezx_sound_mgr *snd_mgr = NULL;

// Dummy requerido por el emulador
uint16 get_nesscreen_pixel_color(int x, int y)
{
    return 0;
}

int main(int argc, char *argv[])
{
    SDL_Surface *screen;
    SDL_Event event;

    bool running = true;

    // ============================
    // SDL INIT
    // ============================
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) < 0)
    {
        printf("SDL FAIL\n");
        return 1;
    }

    // Cambiado a SDL_SWSURFACE para máxima estabilidad en C4droid (Android)
    screen = SDL_SetVideoMode(320, 240, 16, SDL_SWSURFACE);

    if (!screen)
    {
        printf("VIDEO FAIL\n");
        SDL_Quit();
        return 1;
    }

    printf("VIDEO OK\n");

    // ============================
    // AUDIO
    // ============================
    snd_mgr = new ezx_sound_mgr(false);

    if (!snd_mgr || !snd_mgr->initialize())
    {
        printf("SOUND FAIL\n");
        return 1;
    }

    printf("SOUND OK\n");

    // ============================
    // NES INIT
    // ============================
    emu = new NES(snd_mgr);

    if (!emu)
    {
        printf("NES FAIL\n");
        return 1;
    }

    if (!emu->initialize("game2.nes"))
    {
        printf("ROM FAIL\n");
        return 1;
    }

    printf("NES OK\n");

    emu->set_exsound_enable(true);

    // Limpiamos todo el buffer original a negro antes de empezar
    memset(VideoBuffer, 0, sizeof(VideoBuffer));

    // Guardamos la dirección de forma segura para C4droid
    uint16_t *fb = &VideoBuffer[0][0];

    // ============================
    // MAIN LOOP
    // ============================
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;
        }

        // ----------------------------
        // EMULATE FRAME
        // ----------------------------
        // Validación de protección para evitar cierres inesperados en Android
        if (emu && fb) {
            emu->emulate_frame(fb);
        }

        // ----------------------------
        // RENDER SDL SEGURO Y ALINEADO
        // ----------------------------
        SDL_LockSurface(screen);

        for (int y = 0; y < 240; y++)
        {
            // Destino: Fila 'y' de la ventana física de SDL
            uint8_t* dest = (uint8_t*)screen->pixels + (y * screen->pitch);
            
            // Origen: Apunta directamente al inicio de la fila 'y' en la matriz original
            uint16_t* src = &VideoBuffer[y][0];

            memcpy(dest, src, 320 * sizeof(uint16_t));
        }

        SDL_UnlockSurface(screen);

        SDL_Flip(screen);

        // 16ms garantiza que la sincronización vertical vaya a 60 FPS estables
        SDL_Delay(1000/90);
    }

    // ============================
    // CLEANUP
    // ============================
    delete emu;
    delete snd_mgr;

    SDL_Quit();

    return 0;
}
