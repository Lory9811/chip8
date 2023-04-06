#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdint.h>

struct System;

struct System* initSystem(void);
void loadRom(struct System* system, const char* const fileName);
void executeCycle(struct System* system);
void executeInstruction(struct System* system, uint16_t opcode);
void selectTest(struct System* system, int testNum);
void drawScreen(struct System* system);
void tickTimers(struct System* system);

#endif
