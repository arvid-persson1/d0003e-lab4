#ifndef _READER_H
#define _READER_H

#include "TinyTimber.h"
#include "handler.h"

typedef struct {
    Object super;
    Handler *handler;
} Reader;

#define initReader(h) { initObject(), h }

int horizontal(const Reader *const, int);
int vertical(const Reader *const, int);

#endif
