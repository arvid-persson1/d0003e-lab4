#ifndef _DISPLAY_H
#define _DISPLAY_H

#include "TinyTimber.h"

typedef struct {
    Object super;
} Display;

#define initDisp() { initObject() }

// Pack num and pos into an int.
// Sound as long as sizeof(Packed) == sizeof(int).

struct Packed {
    unsigned int num  : 7;
    unsigned int pos  : 3;
    // Ensure struct is 16 bits size.
    unsigned int _pad : 6;
};

union Pun {
    struct Packed args;
    int map;
};

#define PACK(num, pos) ((union Pun){ .args = { num, pos } }).map

int print(Display *self, int map);

#endif
