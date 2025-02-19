#ifndef _HANDLER_H
#define _HANDLER_H

#include "TinyTimber.h"
#include "pulse.h"

typedef struct {
    Object super;
    PulseGenerator *p;
} Handler;

#define initHandler(p) { initObject(), p }

int switchGen(Handler *const, int);
int changeFreq(const Handler *const, int);

#endif
