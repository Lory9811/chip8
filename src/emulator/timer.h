#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

struct Timer {
    uint8_t counter;
};

void tickTimer(struct Timer* timer);

#endif
