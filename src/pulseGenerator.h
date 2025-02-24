#ifndef _PULSE_H
#define _PULSE_H

#include "TinyTimber.h"

typedef struct {
    Object super;
    unsigned int frequency : 7;
    unsigned int state     : 1;
    unsigned int position  : 3;
    unsigned int portBit   : 3;
    unsigned int stashed   : 7;
} PulseGenerator;

#define initGen(pos, pb) { initObject(), 0, 0, pos, pb, 0 }

int output(PulseGenerator *self, __attribute__((unused)) int _x);
int stash(PulseGenerator *self, __attribute__((unused)) int _x);
int increment(PulseGenerator *self, __attribute__((unused)) int _x);
int decrement(PulseGenerator *self, __attribute__((unused)) int _x);

#endif
