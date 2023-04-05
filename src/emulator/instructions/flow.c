#include "instructions.h"

#include <stdio.h>

const uint16_t callStackAddress = 0xEFF;
const uint8_t maxStackDepth = 48;

/* 00EE */
void ret(struct Cpu* cpu, struct Memory* memory) {
    uint32_t returnAddress = (memory->data[cpu->sp] << 8) | memory->data[cpu->sp + 1];
    printf("Returning to %04x (sp %04x)\n", returnAddress, cpu->sp);
    cpu->sp += 2;
    cpu->pc = returnAddress;
}

/* 1NNN */
void jump(struct Cpu* cpu, uint16_t address) {
    printf("Jumping to %04x\n", address);
    cpu->pc = address;
}

/* 2NNN */
void call(struct Cpu* cpu, struct Memory* memory, uint16_t address) {
    printf("Calling %04x from %04x\n", address, cpu->pc);
    cpu->pc += 2;
    memory->data[cpu->sp--] = cpu->pc & 0xFF; 
    memory->data[cpu->sp--] = (cpu->pc >> 8) & 0xFF; 
    cpu->pc = address;
}
