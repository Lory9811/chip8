#include "instructions.h"

#include <stdlib.h>

/* CXNN */
void getRandom(struct Cpu* cpu, int reg, uint8_t mask) {
    cpu->registers[reg] = rand() & mask;
}
