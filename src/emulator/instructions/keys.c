#include "instructions.h"

#include <logger.h>

#define KEY_TO_VALUE(X) if (keycode & KEYPAD_KEY_ ## X) return 0x ## X;
int keyToValue(uint16_t keycode) {
    KEY_TO_VALUE(0)
    KEY_TO_VALUE(1)
    KEY_TO_VALUE(2)
    KEY_TO_VALUE(3)
    KEY_TO_VALUE(4)
    KEY_TO_VALUE(5)
    KEY_TO_VALUE(6)
    KEY_TO_VALUE(7)
    KEY_TO_VALUE(8)
    KEY_TO_VALUE(9)
    KEY_TO_VALUE(A)
    KEY_TO_VALUE(B)
    KEY_TO_VALUE(C)
    KEY_TO_VALUE(D)
    KEY_TO_VALUE(E)
    KEY_TO_VALUE(F)
}
#undef KEY_TO_VALUE

#define VALUE_TO_KEY(X) case 0x ## X: return KEYPAD_KEY_ ## X;
int valueToKey(uint16_t value) {
    switch (value) {
    VALUE_TO_KEY(0)
    VALUE_TO_KEY(1)
    VALUE_TO_KEY(2)
    VALUE_TO_KEY(3)
    VALUE_TO_KEY(4)
    VALUE_TO_KEY(5)
    VALUE_TO_KEY(6)
    VALUE_TO_KEY(7)
    VALUE_TO_KEY(8)
    VALUE_TO_KEY(9)
    VALUE_TO_KEY(A)
    VALUE_TO_KEY(B)
    VALUE_TO_KEY(C)
    VALUE_TO_KEY(D)
    VALUE_TO_KEY(E)
    VALUE_TO_KEY(F)
    }
}
#undef VALUE_TO_KEY

/* FX0A */
void keyWait(struct Cpu* cpu, struct Keypad* keypad, int reg) {
    cpu->waitKey = true;
    uint16_t releasedKeys = (keypad->keys ^ keypad->lastKeys) & keypad->lastKeys;
    // logMessage(LOG_LEVEL_DEBUG, "Key states %04x last %04x released %04x\n", keypad->keys, keypad->lastKeys, releasedKeys);
    if (releasedKeys) {
        cpu->registers[reg] = keyToValue(releasedKeys);
        cpu->waitKey = false;
        cpu->pc += 2;
    }
}

/* EX9E, EXA1 */
void keyTest(struct Cpu* cpu, struct Keypad* keypad, int reg, int cond) {
    if (!!(valueToKey(cpu->registers[reg]) & keypad->keys) != cond) {
        cpu->pc += 2;
    }
}
