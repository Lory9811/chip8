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

    selectTest(system, 2);
    bool quit = false;
    int cycles = 0;
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
        /*if (cycles < 64) {
            executeCycle(system);
        }*/

        executeCycle(system);
        drawScreen(system);
        cycles += 1;
    }

    logClose();

    return 0;
}
