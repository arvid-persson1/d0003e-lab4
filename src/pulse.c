#include <stdint.h>
#include "TinyTimber.h"
#include "pulse.h"

#define HALF_PERIOD MSEC(500)

int increment(PulseGenerator *const self, __attribute__((unused)) int _x) {
    if (self->frequency == 0)
        AFTER(HALF_PERIOD, self, output, 0);

    if (self->frequency <= FREQ_MAX)
        self->frequency++;

    return 0;
}

int decrement(PulseGenerator *const self, __attribute__((unused)) int _x) {
    if (self->frequency > 0)
        self->frequency--;

    // TODO: does 0 have to be tested here to write low?

    return 0;
}

int stash(PulseGenerator *const self, __attribute__((unused)) int _x) {
    if (self->frequency) {
        self->stashed = self->frequency;
        self->frequency = 0;
    } else {
        self->frequency = self->stashed;
    }

    return 0;
}

int output(PulseGenerator *const self, __attribute__((unused)) int _x) {
    if (self->frequency) {
        AFTER(HALF_PERIOD / self->frequency, self, output, 0);
        self->level ^= 1;
    } else {
        self->level = 0;
    }

    // TODO: can this be sync?
    ASYNC(self->writer, write, self->level);

    return 0;
}
