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

/* 8XY0 */
void copy(struct Cpu* cpu, int dstReg, int srcReg) {
    logMessage(LOG_LEVEL_INFO, "register[%x] = register[%x] (%d)\n", dstReg, srcReg, cpu->registers[srcReg]);
    cpu->registers[dstReg] = cpu->registers[srcReg];
}

/* 8XY1 */
void or(struct Cpu* cpu, int dstReg, int srcReg) {
    logMessage(LOG_LEVEL_INFO, "register[%x] (%d) |= register[%x] (%d)\n", dstReg, cpu->registers[dstReg], srcReg, cpu->registers[srcReg]);
    cpu->registers[dstReg] |= cpu->registers[srcReg];
    cpu->registers[0xF] = 0;    // CHIP-8 quirk
}

/* 8XY2 */
void and(struct Cpu* cpu, int dstReg, int srcReg) {
    logMessage(LOG_LEVEL_INFO, "register[%x] (%d) &= register[%x] (%d)\n", dstReg, cpu->registers[dstReg], srcReg, cpu->registers[srcReg]);
    cpu->registers[dstReg] &= cpu->registers[srcReg];
    cpu->registers[0xF] = 0;    // CHIP-8 quirk
}

/* 8XY3 */
void xor(struct Cpu* cpu, int dstReg, int srcReg) {
    logMessage(LOG_LEVEL_INFO, "register[%x] (%d) ^= register[%x] (%d)\n", dstReg, cpu->registers[dstReg], srcReg, cpu->registers[srcReg]);
    cpu->registers[dstReg] ^= cpu->registers[srcReg];
    cpu->registers[0xF] = 0;    // CHIP-8 quirk
}

/* 8XY4 */
void add(struct Cpu* cpu, int dstReg, int srcReg) {
    logMessage(LOG_LEVEL_INFO, "register[%x] (%d) += register[%x] (%d)\n", dstReg, cpu->registers[dstReg], srcReg, cpu->registers[srcReg]);

    /* Calculate carry */
    uint8_t carry = cpu->registers[dstReg] > (0xFF - cpu->registers[srcReg]);
    cpu->registers[dstReg] += cpu->registers[srcReg];
    cpu->registers[0xF] = carry; 
}

/* 8XY5 */
void sub(struct Cpu* cpu, int dstReg, int srcReg) {
    logMessage(LOG_LEVEL_INFO, "register[%x] (%d) -= register[%x] (%d)\n", dstReg, cpu->registers[dstReg], srcReg, cpu->registers[srcReg]);
    
    /* Calculate borrow (negated) */
    uint8_t borrow = cpu->registers[srcReg] < cpu->registers[dstReg];
    cpu->registers[dstReg] -= cpu->registers[srcReg];
    cpu->registers[0xF] = borrow;
}

/* 8XY6 */
void rsh(struct Cpu* cpu, int dstReg, int srcReg) {
    uint8_t lsb = cpu->registers[srcReg] & 0x01;
    cpu->registers[dstReg] = cpu->registers[srcReg] >> 1;
    cpu->registers[0xF] = lsb;
}

/* 8XY7 */
void sub2(struct Cpu* cpu, int dstReg, int srcReg) {
    logMessage(LOG_LEVEL_INFO, "register[%x] (%d) |= register[%x] (%d)\n", dstReg, cpu->registers[dstReg], srcReg, cpu->registers[srcReg]);
    
    /* Calculate borrow (negated) */
    uint8_t borrow = cpu->registers[srcReg] > cpu->registers[dstReg];
    cpu->registers[dstReg] = cpu->registers[srcReg] - cpu->registers[dstReg];
    cpu->registers[0xF] = borrow;
}

/* 8XYE */
void lsh(struct Cpu* cpu, int dstReg, int srcReg) {
    uint8_t msb = (cpu->registers[srcReg] & 0x80) >> 7;
    cpu->registers[dstReg] = cpu->registers[srcReg] << 1;
    cpu->registers[0xF] = msb;
}
