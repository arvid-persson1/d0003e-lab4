#ifndef _DISPLAY_H
#define _DISPLAY_H

#include "TinyTimber.h"

// To "lock" the LCD, `Display` has to be a singleton.
// As such, instance parameters cannot be used.
// `position`, used only as argument to `print`,
// is instead stored in `PulseGenerator`.
typedef struct {
    Object super;
} Display;

#define initDisp() { initObject() }

// Pack `num` and `pos` into an `int`.
// Sound as long as `sizeof(Packed) == sizeof(int)`.

struct Packed {
    unsigned int num  : 7;
    unsigned int pos  : 3;
    // Ensure struct is 16 bits size.
    unsigned int _pad : 6;
};

union PrintPun {
    struct Packed args;
    int map;
};

#define PACK_PRINT(num, pos) ((union PrintPun){ .args = { num, pos } }).map

int print(Display *self, int map);

#endif
