#ifndef DISPLAY_H
#define DISPLAY_H

#include "mem.h"

#include <SDL2/SDL.h>

#include <stdint.h>

struct Display {
    SDL_Window* _window;
    SDL_Surface* _screenSurface;
};

struct Display initDisplay(void);
void drawFrame(struct Display* display, struct Memory* memory);

#endif
