#ifndef _HANDLER_H
#define _HANDLER_H

#include "inputManager.h"

typedef struct {
    Object super;
    InputManager *manager;
} InterruptHandler;

#define initHandler(m) { initObject(), m }

int horizontal(const InterruptHandler *const, __attribute__((unused)) const int);
int vertical(const InterruptHandler *const, __attribute__((unused)) const int);

#endif
