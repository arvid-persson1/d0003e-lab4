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
    unsigned int active    : 1;
    unsigned int position  : 3;
} PulseGenerator;

#define initGen(disp, writ, pos, act) { initObject(), disp, writ, 0, 0, 0, act, pos }

int output(PulseGenerator *const, __attribute__((unused)) const int);
int stash(PulseGenerator *const, __attribute__((unused)) const int);
int increment(PulseGenerator *const, __attribute__((unused)) const int);
int decrement(PulseGenerator *const, __attribute__((unused)) const int);

#endif
