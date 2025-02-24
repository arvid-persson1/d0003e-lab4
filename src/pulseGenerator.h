#ifndef _PULSE_H
#define _PULSE_H

#include "TinyTimber.h"
#include "display.h"
#include "writer.h"

typedef struct {
    Object super;
    Display *display;
    Writer *writer;
    unsigned int frequency : 7;
    unsigned int state     : 1;
    unsigned int stashed   : 7;
    unsigned int position  : 3;
} PulseGenerator;

#define initGen(disp, pos, pb) { initObject(), disp, initWriter(pb), 0, 0, 0, pos }

int output(PulseGenerator *self, __attribute__((unused)) int _x);
int stash(PulseGenerator *self, __attribute__((unused)) int _x);
int increment(PulseGenerator *self, __attribute__((unused)) int _x);
int decrement(PulseGenerator *self, __attribute__((unused)) int _x);

#endif
