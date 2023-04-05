#include "cpu.h"

#include "instructions/instructions.h"

#include <stdio.h>

struct Cpu initCpu(void) {
    printf("Initializing CPU\n");
    
    struct Cpu cpu = {
        .pc = 0x200,
        .sp = 0xEFF,
    };

    printf("Finished CPU initialization\n");

    return cpu;
}

void stepInstruction(struct Cpu* cpu) {
    cpu->pc += 2;
}
