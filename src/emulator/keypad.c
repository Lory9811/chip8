#include "keypad.h"

struct Keypad initKeys(void) {
    struct Keypad keypad = {
        .keys = 0,
        .lastKeys = 0,
    };

    return keypad;
}

void pressKeys(struct Keypad* keypad, uint16_t keys) {
    keypad->lastKeys = keypad->keys;
    keypad->keys |= keys;
}

void releaseKeys(struct Keypad* keypad, uint16_t keys) {
    keypad->lastKeys = keypad->keys;
    keypad->keys &= ~keys;
}
