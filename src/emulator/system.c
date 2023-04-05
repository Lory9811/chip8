#include "system.h"

#include "cpu.h"
#include "mem.h"
#include "display.h"

#include "instructions/instructions.h"

#include <logger.h>

#include <SDL2/SDL.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

struct System {
    struct Cpu cpu;
    struct Memory memory;
    struct Display display;
};

struct System* initSystem(void) {
    SDL_Init(SDL_INIT_EVENTS | SDL_INIT_AUDIO);
    struct System* system = malloc(sizeof(struct System));

    logMessage(LOG_LEVEL_INFO, "Initializing CHIP-8\n");

    system->cpu = initCpu();
    system->memory = initMemory(4096);
    system->display = initDisplay();

    logMessage(LOG_LEVEL_INFO, "Finished CHIP-8 initalization\n");

    return system;
}

void loadRom(struct System* system, const char* const fileName) {
    FILE* file = fopen(fileName, "rb");
    fseek(file, 0, SEEK_SET);
    
    uint16_t address = 0x200;
    uint16_t bytesRead = 0;
    uint8_t* restrict buffer = malloc(512);

    logMessage(LOG_LEVEL_INFO, "Loading ROM %s at address %04x\n", fileName, address);

    while (bytesRead = fread(buffer, 1, 512, file)) {
        logMessage(LOG_LEVEL_INFO, "Writing %d bytes at %04x\n", bytesRead, address);
        bulkWriteMemory(&system->memory, buffer, address, bytesRead);
        address += bytesRead;
    }

    fclose(file);

    logMessage(LOG_LEVEL_INFO, "Loaded ROM\n");
}

void executeCycle(struct System* system) {
    uint16_t opcode = readWordMemory(&system->memory, system->cpu.pc);
    // logMessage(LOG_LEVEL_INFO, "Read at %04x opcode %04x\n", system->cpu.pc, opcode);
    executeInstruction(system, opcode);
}

void executeInstruction(struct System* system, uint16_t opcode) {
    if (opcode == 0x00E0) {
        clearScreen(&system->memory);
        stepInstruction(&system->cpu);
    } else if ((opcode & 0xF000) == 0x1000) {
        jump(&system->cpu, opcode & 0x0FFF);
    } else if ((opcode & 0xF000) == 0x3000) {
        cmpi(&system->cpu, (opcode & 0x0F00) >> 8, opcode & 0x00FF, INSTRUCTIONS_CMP_EQU);
        stepInstruction(&system->cpu);
    } else if ((opcode & 0xF000) == 0x4000) {
        cmpi(&system->cpu, (opcode & 0x0F00) >> 8, opcode & 0x00FF, INSTRUCTIONS_CMP_NEQ);
        stepInstruction(&system->cpu);
    } else if ((opcode & 0xF000) == 0x5000) {
        call(&system->cpu, &system->memory, opcode & 0x0FFF);
    } else if ((opcode & 0xF000) == 0x6000) {
        set(&system->cpu, (opcode & 0x0F00) >> 8, opcode & 0x00FF);
        stepInstruction(&system->cpu);
    } else if ((opcode & 0xF000) == 0x7000) {
        inc(&system->cpu, (opcode & 0x0F00) >> 8, opcode & 0x00FF);
        stepInstruction(&system->cpu);
    } else if ((opcode & 0xF000) == 0xA000) {
        loadIndex(&system->cpu, opcode & 0x0FFF);
        stepInstruction(&system->cpu);
    } else if ((opcode & 0xF000) == 0xD000) {
        drawSprite(&system->cpu, &system->memory, (opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4, opcode & 0x000F);
        stepInstruction(&system->cpu);
    } else if ((opcode & 0xF0FF) == 0xF00A) {

    } else if ((opcode & 0xF0FF) == 0xF065) {
        strLoadRegister(&system->cpu, &system->memory, (opcode & 0x0F00) >> 8);
        stepInstruction(&system->cpu);
    } else {
        logMessage(LOG_LEVEL_INFO, "Unimplemented instruction %04x\n", opcode);
        // stepInstruction(&system->cpu);
    }
}

void selectTest(struct System *system, int testNum) {
    writeMemory(&system->memory, 0x1FF, testNum);
}

void drawScreen(struct System* system) {
    drawFrame(&system->display, &system->memory);
}
