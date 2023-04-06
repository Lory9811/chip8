#include "timer.h"

void tickTimer(struct Timer* timer) {
    if (timer->counter > 0) {
        timer->counter -= 1;
    }
}
