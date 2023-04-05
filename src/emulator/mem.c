#include "mem.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Memory initMemory(uint16_t size) {
    printf("Initializing Memory\n");

    struct Memory memory = {
        .data = calloc(size, sizeof(uint8_t)),
        .size = size,
    };

    printf("Finished Memory initialization\n");

    return memory;
}

uint8_t readMemory(struct Memory* memory, uint16_t address) {
    return memory->data[address];
}

uint16_t readWordMemory(struct Memory* memory, uint16_t address) {
    return (memory->data[address] << 8) | (memory->data[address + 1]);
}

void writeMemory(struct Memory* memory, uint16_t address, uint8_t value) {
    memory->data[address] = value;
}

void bulkWriteMemory(struct Memory* memory, uint8_t* const data, uint16_t start, uint16_t bytes) {
    if (start > memory->size
    || start + bytes > memory->size
    || start + bytes < start) {
        printf("Invalid bulk write at %x with size %x\n", start, bytes);
        return;
    } 
    memcpy(memory->data + start, data, bytes);
}
