#ifndef _INPUT_H
#define _INPUT_H

#include "TinyTimber.h"
#include "pulseGenerator.h"

typedef struct {
    Object super;
    PulseGenerator *p1, *p2;
    Msg holdHandle;
    unsigned int current : 1;
} InputManager;

#define initManager(p1, p2) { initObject(), p1, p2, NULL, 0 }

int switchGen(InputManager *self, int pine);
int changeOrStash(InputManager *self, int pinb);

#endif
