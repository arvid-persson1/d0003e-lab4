#ifndef _WRITER_H
#define _WRITER_H

#include "TinyTimber.h"

typedef struct {
    Object super;
    unsigned int position : 3;
} Writer;

#define initWriter(pos) { initObject(), pos }

int write(const Writer *const, int);

#endif
