#include <SDL2/SDL.h>

#include "system.h"
#include "keypad.h"

#include <logger.h>

#include <stdio.h>
#include <stdbool.h>

void handleKeyEvent(struct System* system, SDL_KeyboardEvent* event) {
    uint16_t keyState = 0;

    switch (event->keysym.sym) {
    case SDLK_z:
        keyState = KEYPAD_KEY_A;
        break;
    case SDLK_x:
        keyState = KEYPAD_KEY_0;
        break;
    case SDLK_c:
        keyState = KEYPAD_KEY_B;
        break;
    case SDLK_v:
        keyState = KEYPAD_KEY_F;
        break;
    case SDLK_a:
        keyState = KEYPAD_KEY_7;
        break;
    case SDLK_s:
        keyState = KEYPAD_KEY_8;
        break;
    case SDLK_d:
        keyState = KEYPAD_KEY_9;
        break;
    case SDLK_f:
        keyState = KEYPAD_KEY_E;
        break;
    case SDLK_q:
        keyState = KEYPAD_KEY_4;
        break;
    case SDLK_w:
        keyState = KEYPAD_KEY_5;
        break;
    case SDLK_e:
        keyState = KEYPAD_KEY_6;
        break;
    case SDLK_r:
        keyState = KEYPAD_KEY_D;
        break;
    case SDLK_1:
        keyState = KEYPAD_KEY_1;
        break;
    case SDLK_2:
        keyState = KEYPAD_KEY_2;
        break;
    case SDLK_3:
        keyState = KEYPAD_KEY_3;
        break;
    case SDLK_4:
        keyState = KEYPAD_KEY_C;
        break;
    }

    switch (event->state) {
    case SDL_RELEASED:
        updateKeys(system, 0, keyState);
        break;
    case SDL_PRESSED:
        updateKeys(system, keyState, 0);
        break;
    }
}

int main(int argc, char** argv) {
    logInit(LOG_LEVEL_ALL);
    struct System* system = initSystem();
    loadRom(system, "../roms/chip8-test-suite.ch8");
    logMessage(LOG_LEVEL_INFO, "Starting\n");

    selectPlatform(system, 3);
    selectTest(system, 5);

    int cyclesPerFrame = 30;
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
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                    handleKeyEvent(system, &event.key);
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
            tickTimers(system);
            drawScreen(system);
            cycles = 0;
            lastDraw = now;
        }
    }

    logClose();

    return 0;
}
