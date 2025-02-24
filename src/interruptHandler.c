#include <avr/io.h>
#include "interruptHandler.h"

int horizontal(InterruptHandler *self, __attribute__((unused)) int _x) {
    ASYNC(self->manager, switchGen, PINE);
    return 0;
}

int vertical(InterruptHandler *self, __attribute__((unused)) int _x) {
    ASYNC(self->manager, changeOrStash, PINB);
    return 0;
}
