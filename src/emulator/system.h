#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdint.h>

struct System;

struct System* initSystem(void);
void loadRom(struct System* system, uint16_t address, const char* const fileName);
void executeCycle(struct System* system);
void executeInstruction(struct System* system, uint16_t opcode);
void selectPlatform(struct System* system, int platform);
void selectTest(struct System* system, int testNum);
void drawScreen(struct System* system);
void tickTimers(struct System* system);
void updateKeys(struct System* system, uint16_t pressed, uint16_t released);

#endif
