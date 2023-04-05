#include "instructions.h"

#include <stdio.h>

/* ANNN */
void loadIndex(struct Cpu* cpu, uint16_t value) {
    printf("I = %04x\n", value);
    cpu->address = value;
}

/* FX65 */
void strLoadRegister(struct Cpu* cpu, struct Memory* memory, int reg) {
    for (int i = 0; i != reg + 1; i++) {
        printf("cpu->registers[%x] = $%04x (%d)\n", i, cpu->address + i, readMemory(memory, cpu->address + i));
        cpu->registers[i] = readMemory(memory, cpu->address + i);
    }
}
