#ifndef _PULSE_H
#define _PULSE_H

#include "TinyTimber.h"
#include "writer.h"
#include "display.h"

#define FREQ_MAX 99

typedef struct {
    Object super;
    Writer *writer;
    Display *display;
    unsigned int frequency : 7,
                 stashed : 7,
                 level : 1;
} PulseGenerator;

#define initPulseGen(writer, disp, freq) { initObject(), writer, disp, freq, 0, 0 }

int increment(PulseGenerator *const, int);
int decrement(PulseGenerator *const, int);
int stash(PulseGenerator *const, int);
int output(PulseGenerator *const, int);

#endif
