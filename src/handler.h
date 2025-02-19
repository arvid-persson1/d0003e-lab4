#ifndef _HANDLER_H
#define _HANDLER_H

#include "TinyTimber.h"
#include "pulse.h"

typedef struct {
    Object super;
    PulseGenerator *p1, *p2;
    unsigned int current : 1;
} Handler;

#define initHandler(p1, p2) { initObject(), p1, p1, 0 }

int switchGen(Handler *const, int);
int changeFreq(const Handler *const, int);

#endif
