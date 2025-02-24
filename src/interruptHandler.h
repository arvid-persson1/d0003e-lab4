#ifndef _HANDLER_H
#define _HANDLER_H

#include "inputManager.h"

typedef struct {
    Object super;
    InputManager *manager;
} InterruptHandler;

#define initHandler(m) { initObject(), m }

int horizontal(InterruptHandler *self, __attribute__((unused)) int _x);
int vertical(InterruptHandler *self, __attribute__((unused)) int _x);

#endif
