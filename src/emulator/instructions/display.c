#include "instructions.h"

#include <logger.h>

void clearScreen(struct Memory* memory) {
    memset(memory->data + 0xF00, 0, 256);
}

void drawSprite(struct Cpu* cpu, struct Memory* memory, int xReg, int yReg, int height) {
    int xPosition = cpu->registers[xReg];
    int yPosition = cpu->registers[yReg];

    logMessage(LOG_LEVEL_DEBUG, "Drawing 8x%d sprite from %04x at (%d, %d) \n", height, cpu->address, xPosition, yPosition);

    int byteOffset = (xPosition / 8) + (64 / 8) * yPosition;
    int bitOffset = xPosition & 0x07;

    for (int i = 0; i != height; i++) {
        if (0xF00 + byteOffset + i * (64 / 8) < memory->size) {
            memory->data[0xF00 + byteOffset + i * (64 / 8)] ^= memory->data[cpu->address + i] >> bitOffset;
        }

        if (bitOffset) {
            if (0xF00 + byteOffset + 1 + i * (64 / 8) < memory->size) {
                memory->data[0xF00 + byteOffset + 1 + i * (64 / 8)] ^= memory->data[cpu->address + i] << (8 - bitOffset);
            }
        }
    }
}
