#include "instructions.h"

#include <logger.h>

/* ANNN */
void loadIndex(struct Cpu* cpu, uint16_t value) {
    logMessage(LOG_LEVEL_INFO, "I = %04x\n", value);
    cpu->address = value;
}

/* FX1E */
void addAddress(struct Cpu* cpu, struct Memory* memory, int reg) {
    cpu->address += cpu->registers[reg];
}

/* FX33 */
void storeBcd(struct Cpu* cpu, struct Memory* memory, int reg) {
    writeMemory(memory, cpu->address, cpu->registers[reg] / 100);
    writeMemory(memory, cpu->address + 1, (cpu->registers[reg] / 10) % 10);
    writeMemory(memory, cpu->address + 2, cpu->registers[reg] % 10);

    logMessage(LOG_LEVEL_DEBUG, "hex %04x -> bcd %d%d%d\n", cpu->registers[reg], 
        readMemory(memory, cpu->address), readMemory(memory, cpu->address + 1), readMemory(memory, cpu->address + 2));
}

/* FX55 */
void strStoreRegister(struct Cpu* cpu, struct Memory* memory, int reg) {
    for (int i = 0; i != reg + 1; i++) {
        logMessage(LOG_LEVEL_INFO, "$(%04x) = cpu->registers[%x] (%d)\n", cpu->address + i, i, cpu->registers[i]);
        writeMemory(memory, cpu->address + i, cpu->registers[i]);
    }

    cpu->address += reg + 1;    // CHIP-8 Quirk
}

/* FX65 */
void strLoadRegister(struct Cpu* cpu, struct Memory* memory, int reg) {
    for (int i = 0; i != reg + 1; i++) {
        logMessage(LOG_LEVEL_INFO, "cpu->registers[%x] = $(%04x) (%d)\n", i, cpu->address + i, readMemory(memory, cpu->address + i));
        cpu->registers[i] = readMemory(memory, cpu->address + i);
    }

    cpu->address += reg + 1;    // CHIP-8 Quirk
}
