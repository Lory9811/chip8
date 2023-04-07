#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

struct Memory {
    uint8_t* data;
    uint16_t size;
};

struct Memory initMemory(uint16_t size);
void loadFont(struct Memory* memory);
uint8_t readMemory(struct Memory* memory, uint16_t address);
uint16_t readWordMemory(struct Memory* memory, uint16_t address);
void writeMemory(struct Memory* memory, uint16_t address, uint8_t value);
void bulkWriteMemory(struct Memory* memory, uint8_t* data, uint16_t start, uint16_t bytes);

#endif
