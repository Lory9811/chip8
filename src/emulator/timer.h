#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

struct Timer {
    uint8_t counter;
};

struct Timer initTimer(void);
void tickTimer(struct Timer* timer);

#endif
