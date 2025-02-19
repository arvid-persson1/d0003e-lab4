#ifndef _DISPLAY_H
#define _DISPLAY_H

#include "TinyTimber.h"

typedef struct {
    Object super;
    unsigned int position : 3;
} Display;

#define initDisplay(pos) { initObject(), pos }

int print(const Display *const, const int);

#endif
