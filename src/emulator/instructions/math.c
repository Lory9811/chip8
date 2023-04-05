#include "instructions.h"

#include <stdio.h>

void set(struct Cpu* cpu, int reg, uint8_t value) {
    printf("register[%x] (%d) = %d\n", reg, cpu->registers[reg], value);
    cpu->registers[reg] = value;
}

void inc(struct Cpu* cpu, int reg, uint8_t value) {
    printf("register[%x] (%d) += %d\n", reg, cpu->registers[reg], value);
    cpu->registers[reg] += value;
}
