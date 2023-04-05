#include "instructions.h"

#include <logger.h>

void set(struct Cpu* cpu, int reg, uint8_t value) {
    logMessage(LOG_LEVEL_INFO, "register[%x] (%d) = %d\n", reg, cpu->registers[reg], value);
    cpu->registers[reg] = value;
}

void inc(struct Cpu* cpu, int reg, uint8_t value) {
    logMessage(LOG_LEVEL_INFO, "register[%x] (%d) += %d\n", reg, cpu->registers[reg], value);
    cpu->registers[reg] += value;
}
