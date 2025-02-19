#include <avr/io.h>
#include "writer.h"

#define SET(x) (1 << x)

int write(const Writer *const self, const int state) {
    if (state)
        PORTE |= SET(self->position);
    else
        PORTE &= ~SET(self->position);

    return 0;
}
