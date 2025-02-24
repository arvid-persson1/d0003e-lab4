#include "pulseGenerator.h"

#define HALF_PERIOD (MSEC(500) / self->frequency)
#define PRINT() SYNC(self->display, print, PACK_PRINT(self->frequency, self->position))

int output(PulseGenerator *const self, __attribute__((unused)) const int _x) {
    if (self->frequency) {
        SYNC(self->writer, write, self->state);
        self->state ^= 1;

        AFTER(HALF_PERIOD, self, output, 0);
    } else {
        SYNC(self->writer, write, 0);
        self->state = 1;
    }

    return 0;
}

int stash(PulseGenerator *const self, __attribute__((unused)) const int _x) {
    if (self->frequency) {
        self->stashed = self->frequency;
        self->frequency = 0;
    } else {
        self->frequency = self->stashed;
        AFTER(HALF_PERIOD, self, output, 0);
    }

    PRINT();
    return 0;
}

#define MAX_FREQUENCY 99

int increment(PulseGenerator *const self, __attribute__((unused)) const int _x) {
    if (self->frequency < MAX_FREQUENCY)
        self->frequency++;

    // Output chain needs to be restarted after 0.
    if (self->frequency == 1)
        AFTER(HALF_PERIOD, self, output, 0);

    PRINT();
    return 0;
}

int decrement(PulseGenerator *const self, __attribute__((unused)) const int _x) {
    if (self->frequency > 0)
        self->frequency--;

    PRINT();
    return 0;
}
