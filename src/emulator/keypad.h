#ifndef KEYPAD_H
#define KEYPAD_H

#include <stdint.h>

#define KEYPAD_KEY_A (1 << 0)
#define KEYPAD_KEY_0 (1 << 1)
#define KEYPAD_KEY_B (1 << 2)
#define KEYPAD_KEY_F (1 << 3)

#define KEYPAD_KEY_7 (1 << 4)
#define KEYPAD_KEY_8 (1 << 5)
#define KEYPAD_KEY_9 (1 << 6)
#define KEYPAD_KEY_E (1 << 7)

#define KEYPAD_KEY_4 (1 << 8)
#define KEYPAD_KEY_5 (1 << 9)
#define KEYPAD_KEY_6 (1 << 10)
#define KEYPAD_KEY_D (1 << 11)

#define KEYPAD_KEY_1 (1 << 12)
#define KEYPAD_KEY_2 (1 << 13)
#define KEYPAD_KEY_3 (1 << 14)
#define KEYPAD_KEY_C (1 << 15)

struct Keypad {
    uint16_t keys;
    uint16_t lastKeys;
};

struct Keypad initKeys(void);
void pressKeys(struct Keypad* keypad, uint16_t keys);
void releaseKeys(struct Keypad* keypad, uint16_t keys);

#endif
