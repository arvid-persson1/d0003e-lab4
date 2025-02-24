#include <avr/io.h>
#include "interruptHandler.h"

int horizontal(const InterruptHandler *const self, __attribute__((unused)) const int _x) {
    ASYNC(self->manager, switchGen, PINE);
    return 0;
}

int vertical(const InterruptHandler *const self, __attribute__((unused)) const int _x) {
    ASYNC(self->manager, changeOrStash, PINB);
    return 0;
}
