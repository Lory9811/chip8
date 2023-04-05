#include "instructions.h"

#include <logger.h>

/* ANNN */
void loadIndex(struct Cpu* cpu, uint16_t value) {
    logMessage(LOG_LEVEL_INFO, "I = %04x\n", value);
    cpu->address = value;
}

/* FX65 */
void strLoadRegister(struct Cpu* cpu, struct Memory* memory, int reg) {
    for (int i = 0; i != reg + 1; i++) {
        logMessage(LOG_LEVEL_INFO, "cpu->registers[%x] = $%04x (%d)\n", i, cpu->address + i, readMemory(memory, cpu->address + i));
        cpu->registers[i] = readMemory(memory, cpu->address + i);
    }
}
