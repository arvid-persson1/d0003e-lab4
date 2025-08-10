#ifndef _INPUT_H
#define _INPUT_H

#include "TinyTimber.h"
#include "pulseGenerator.h"

typedef struct {
    Object super;
    PulseGenerator *p1, *p2;
    Msg holdHandle;
} InputManager;

#define initManager(p1, p2) { initObject(), p1, p2, NULL }

int switchGen(InputManager *const, const int);
int changeOrStash(InputManager *const, const int);
int start(const InputManager *const, __attribute__((unused)) const int);

#endif
