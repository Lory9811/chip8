#include "display.h"

#include <logger.h>

struct Display initDisplay(void) {
    logMessage(LOG_LEVEL_INFO, "Initializing Display\n");

    SDL_Init(SDL_INIT_VIDEO);

    struct Display display;

    // SDL_CreateWindowAndRenderer(640, 480, 0, &display._window, &display._renderer);
    display._window = SDL_CreateWindow("CHIP-8", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 320,
        0);

    display._screenSurface = SDL_CreateRGBSurface(0, 64, 32, 32, 0xFF0000, 0x00FF00, 0x0000FF, 0);
    //display._screenTexture = SDL_CreateTexture(display._renderer, SDL_PIXELFORMAT_RGB444, SDL_TEXTUREACCESS_STREAMING, 64, 32);

    logMessage(LOG_LEVEL_INFO, "Finished Display initialization\n");

    return display;
}

void fillDisplay(struct Display* display, uint32_t color) {
    /*SDL_SetRenderDrawColor(display->_renderer, (color >> 24) & 0xFF, (color >> 16) & 0xFF, (color >> 8) & 0xFF, (color) & 0xFF);
    SDL_RenderClear(display->_renderer);
    
    SDL_RenderPresent(display->_renderer);*/

    
}

void drawFrame(struct Display* display, struct Memory* memory) {

    SDL_LockSurface(display->_screenSurface);

    SDL_PixelFormat* format = display->_screenSurface->format;

    for (int i = 0; i != 256; i++) {
        uint8_t vramData = memory->data[0xF00 + i];

        for (int j = 0; j != 8; j++) {
            int pixelOffset = 8 * i + j;
            uint32_t color = 0x9E6F01;
            if (vramData & (0x80 >> j)) {
                color = 0xFCB102;
            }
            ((uint32_t*)display->_screenSurface->pixels)[pixelOffset] = color;
        }
    }

    SDL_UnlockSurface(display->_screenSurface);

    SDL_Surface* windowSurface = SDL_GetWindowSurface(display->_window);

    int scale = windowSurface->h / display->_screenSurface->h;
    int scaledWidth = scale * display->_screenSurface->w;

    SDL_Rect dstRect = {
        .x = (windowSurface->w - scaledWidth) / 2, .y = 0,
        .w = scaledWidth, .h = windowSurface->h
    };
    SDL_BlitScaled(display->_screenSurface, 0, windowSurface, &dstRect);
    SDL_UpdateWindowSurface(display->_window);
}
