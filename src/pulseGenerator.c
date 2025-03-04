#include "pulseGenerator.h"

#define ZERO_PERIOD MSEC(500)
#define HALF_PERIOD (MSEC(500) / self->frequency)

#define PRINT() SYNC(self->display, print, PACK_PRINT(self->frequency, self->position))

int output(PulseGenerator *const self, __attribute__((unused)) const int _x) {
    Time period;
    int out;

    if (self->frequency) {
        out = self->state;
        self->state ^= 1;
        period = HALF_PERIOD;
    } else {
        out = 0;
        self->state = 1;
        period = ZERO_PERIOD;
    }

    if (self->active)
        SYNC(self->writer, write, out);

    AFTER(period, self, output, 0);

    return 0;
}

int stash(PulseGenerator *const self, __attribute__((unused)) const int _x) {
    if (self->frequency) {
        self->stashed = self->frequency;
        self->frequency = 0;
    } else {
        self->frequency = self->stashed;
    }

    PRINT();
    return 0;
}

#define MAX_FREQUENCY 99

int increment(PulseGenerator *const self, __attribute__((unused)) const int _x) {
    if (self->frequency < MAX_FREQUENCY)
        self->frequency++;

    PRINT();
    return 0;
}

int decrement(PulseGenerator *const self, __attribute__((unused)) const int _x) {
    if (self->frequency > 0)
        self->frequency--;

    PRINT();
    return 0;
}
