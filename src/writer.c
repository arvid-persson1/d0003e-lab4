#include <avr/io.h>
#include "writer.h"
#include "init.h"

int write(const Writer *const self, const int state) {
    if (state)
        PORTE |= SET(self->portBit);
    else
        PORTE &= ~SET(self->portBit);

    return 0;
}

