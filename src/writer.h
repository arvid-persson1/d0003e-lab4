#ifndef _WRITER_H
#define _WRITER_H

#include "TinyTimber.h"

typedef struct {
    Object super;
    unsigned int portBit : 3;
} Writer;

#define initWriter(pb) { initObject(), pb }

int write(const Writer *const, const int);

#endif
