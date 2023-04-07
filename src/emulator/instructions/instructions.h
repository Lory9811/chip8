#ifndef INSTRUCCTIONS_H
#define INSTRUCTIONS__H

#include "../cpu.h"
#include "../mem.h"
#include "../display.h"
#include "../timer.h"
#include "../keypad.h"

#include <stdint.h>

#define INSTRUCTIONS_CMP_EQU 0
#define INSTRUCTIONS_CMP_NEQ 1

void callNative(struct Cpu* cpu, uint16_t address);
/* 00E0 */
void clearScreen(struct Memory* memory);
/* 00EE */
void ret(struct Cpu* cpu, struct Memory* memory);
/* 1NNN */
void jump(struct Cpu* cpu, uint16_t address);
/* 2NNN */
void call(struct Cpu* cpu, struct Memory* memory, uint16_t address);
/* 3XNN, 4XNN */
void cmpi(struct Cpu* cpu, int reg, uint8_t value, int cond);
/* 5XY0, 9XY0 */
void cmp(struct Cpu* cpu, int reg, int otherReg, int cond);
/* 6XNN */
void set(struct Cpu* cpu, int reg, uint8_t value);
/* 7XNN */
void inc(struct Cpu* cpu, int reg, uint8_t value);
/* 8XY0 */
void copy(struct Cpu* cpu, int dstReg, int srcReg);
/* 8XY1 */
void or(struct Cpu* cpu, int dstReg, int srcReg);
/* 8XY2 */
void and(struct Cpu* cpu, int dstReg, int srcReg);
/* 8XY3 */
void xor(struct Cpu* cpu, int dstReg, int srcReg);
/* 8XY4 */
void add(struct Cpu* cpu, int dstReg, int srcReg);
/* 8XY5 */
void sub(struct Cpu* cpu, int dstReg, int srcReg);
/* 8XY6 */
void rsh(struct Cpu* cpu, int dstReg, int srcReg);
/* 8XY7 */
void sub2(struct Cpu* cpu, int dstReg, int srcReg);
/* 8XYE */
void lsh(struct Cpu* cpu, int dstReg, int srcReg);

/* ANNN */
void loadIndex(struct Cpu* cpu, uint16_t value);
/* BNNN */
void offsetJump(struct Cpu* cpu, uint16_t address);
/* CXNN */
void getRandom(struct Cpu* cpu, int reg, uint8_t mask);
/* DXYN */
void drawSprite(struct Cpu* cpu, struct Memory* memory, int xReg, int yReg, int height);
/* EX9E, EXA1 */
void keyTest(struct Cpu* cpu, struct Keypad* keypad, int reg, int cond);
/* FX0A */
void keyWait(struct Cpu* cpu, struct Keypad* keypad, int reg);
/* FX07 */
void getDelayTimer(struct Cpu* cpu, struct Timer* timer, int reg);
/* FX15, FX18 */
void setTimer(struct Cpu* cpu, struct Timer* timer, int reg);
/* FX1E */
void addAddress(struct Cpu* cpu, struct Memory* memory, int reg);
/* FX29 */
void getCharAddress(struct Cpu* cpu, int reg);
/* FX33 */
void storeBcd(struct Cpu* cpu, struct Memory* memory, int reg);
/* FX55 */
void strStoreRegister(struct Cpu* cpu, struct Memory* memory, int reg);
/* FX65 */
void strLoadRegister(struct Cpu* cpu, struct Memory* memory, int reg);

#endif
