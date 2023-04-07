#include "instructions.h"

/* FX07 */
void getDelayTimer(struct Cpu* cpu, struct Timer* timer, int reg) {
    cpu->registers[reg] = timer->counter;
}

/* FX15, FX18 */
void setTimer(struct Cpu* cpu, struct Timer* timer, int reg) {
    timer->counter = cpu->registers[reg];
}
