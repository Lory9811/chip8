#include <SDL2/SDL.h>

#include "system.h"

#include <logger.h>

#include <stdio.h>
#include <stdbool.h>

int main(int argc, char** argv) {
    logInit(LOG_LEVEL_ALL);
    struct System* system = initSystem();
    loadRom(system, "../roms/chip8-test-suite.ch8");
    logMessage(LOG_LEVEL_INFO, "Starting\n");

    selectTest(system, 3);

    int cyclesPerFrame = 50;
    bool quit = false;
    int cycles = 0;
    uint64_t lastDraw = SDL_GetPerformanceCounter();
    while (!quit) {
        {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                
                default:
                    break;
                }
            }
        }

        if (cycles < cyclesPerFrame) {
            executeCycle(system);
            cycles += 1;
        }
        
        uint64_t now = SDL_GetPerformanceCounter();
        if ((((now - lastDraw) * 1000) / SDL_GetPerformanceFrequency()) > 16) {
            // logMessage(LOG_LEVEL_INFO, "last %d now %d\n", lastDraw, now);
            tickTimers(system);
            drawScreen(system);
            cycles = 0;
            lastDraw = now;
        }
    }

    logClose();

    return 0;
}
