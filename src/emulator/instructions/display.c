#include "instructions.h"

#include <logger.h>
#include <stdbool.h>

void clearScreen(struct Memory* memory) {
    logMessage(LOG_LEVEL_DEBUG, "Clearing screen\n");
    memset(memory->data + 0xF00, 0, 256);
}

void drawSprite(struct Cpu* cpu, struct Memory* memory, int xReg, int yReg, int height) {
    int xPosition = cpu->registers[xReg] % 64;
    int yPosition = cpu->registers[yReg] % 32;

    logMessage(LOG_LEVEL_DEBUG, "Drawing 8x%d sprite from %04x at (%d, %d) \n", height, cpu->address, xPosition, yPosition);

    int byteOffset = (xPosition / 8) + (64 / 8) * yPosition;
    int bitOffset = xPosition & 0x07;
    bool collision = false;

    for (int i = 0; i != height; i++) {
        if (0xF00 + byteOffset + i * (64 / 8) < 0xFFF) {
            uint8_t newByte = memory->data[cpu->address + i] >> bitOffset;
            memory->data[0xF00 + byteOffset + i * (64 / 8)] ^= newByte;
            if ((memory->data[0xF00 + byteOffset + i * (64 / 8)] & newByte) != newByte) {
                collision = true;
            }
        }

        if (bitOffset && xPosition < (64 - bitOffset)) {
            if (0xF00 + byteOffset + 1 + i * (64 / 8) < memory->size) {
                uint8_t newByte = memory->data[cpu->address + i] << (8 - bitOffset);
                memory->data[0xF00 + byteOffset + 1 + i * (64 / 8)] ^= newByte;
                if ((memory->data[0xF00 + byteOffset + 1 + i * (64 / 8)] & newByte) != newByte) {
                    collision = true;
                }
            }
        }
    }

    cpu->registers[0xF] = collision;
    cpu->sleepFrames = 1;
}
