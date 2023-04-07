#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdbool.h>

struct Cpu {
    uint8_t registers[16];  // V0..E are general purpose; VF is for flags 
    uint16_t address;       // I register, 12 bits
    uint16_t pc;
    uint16_t sp;
    int sleepFrames;
    bool waitKey;
};

struct Cpu initCpu(void);
void stepInstruction(struct Cpu* cpu);

#endif
