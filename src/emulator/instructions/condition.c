#include "instructions.h"

#include <logger.h>

/* 3XNN, 4XNN */
void cmpi(struct Cpu* cpu, int reg, uint8_t value, int cond) {
    if (cond == INSTRUCTIONS_CMP_EQU) {
        logMessage(LOG_LEVEL_INFO, "register[%x] (%d) == %d\n", reg, cpu->registers[reg], value);
    } else if (cond == INSTRUCTIONS_CMP_NEQ) {
        logMessage(LOG_LEVEL_INFO, "register[%x] (%d) != %d\n", reg, cpu->registers[reg], value);
    }

    if ((cpu->registers[reg] == value) != cond) {
        cpu->pc += 2;
    }
}

/* 5XY0, 9XY0 */
void cmp(struct Cpu* cpu, int reg, int otherReg, int cond) {
    if (cond == INSTRUCTIONS_CMP_EQU) {
        logMessage(LOG_LEVEL_INFO, "register[%x] (%d) == register[%x] (%d)\n", reg, cpu->registers[reg], otherReg, cpu->registers[otherReg]);
    } else if (cond == INSTRUCTIONS_CMP_NEQ) {
        logMessage(LOG_LEVEL_INFO, "register[%x] (%d) != register[%x] (%d)\n", reg, cpu->registers[reg], otherReg, cpu->registers[otherReg]);
    }

    if ((cpu->registers[reg] == cpu->registers[otherReg]) != cond) {
        cpu->pc += 2;
    }
}
