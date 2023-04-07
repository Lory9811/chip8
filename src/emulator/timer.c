#include "timer.h"

struct Timer initTimer(void) {
    struct Timer timer = {
        .counter = 0,
    };

    return timer;
}

void tickTimer(struct Timer* timer) {
    if (timer->counter > 0) {
        timer->counter -= 1;
    }
}
