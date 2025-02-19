#include <avr/io.h>
#include "TinyTimber.h"
#include "reader.h"

int horizontal(const Reader *const self, __attribute__((unused)) int _x) {
    ASYNC(self->handler, switchGen, 0);
    return 0;
}

int vertical(const Reader *const self, __attribute__((unused)) int _x) {
    ASYNC(self->handler, changeFreq, PINB);
    return 0;
}
