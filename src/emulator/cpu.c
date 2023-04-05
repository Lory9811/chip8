#include "cpu.h"

#include "instructions/instructions.h"

#include <logger.h>

struct Cpu initCpu(void) {
    logMessage(LOG_LEVEL_INFO, "Initializing CPU\n");
    
    struct Cpu cpu = {
        .pc = 0x200,
        .sp = 0xEFF,
    };

    logMessage(LOG_LEVEL_INFO, "Finished CPU initialization\n");

    return cpu;
}

void stepInstruction(struct Cpu* cpu) {
    cpu->pc += 2;
}
