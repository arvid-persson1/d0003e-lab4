#include <avr/io.h>
#include "pulseGenerator.h"
#include "init.h"
#include "gui.h"

void write(PulseGenerator *self, int state) {
    if (state)
        PORTE |= SET(self->portBit);
    else
        PORTE &= ~SET(self->portBit);
}

int output(PulseGenerator *self, __attribute__((unused)) int _x) {
    if (self->frequency) {
        // TODO: make TT call
        write(self, self->state);
        self->state ^= 1;

        AFTER(MSEC(500) / self->frequency, self, output, 0);
    } else {
        // TODO: make TT call
        write(self, 0);
        self->state = 1;
    }

    return 0;
}

#define PRINT() printAt(self->frequency, self->position)

int stash(PulseGenerator *self, __attribute__((unused)) int _x) {
    if (self->frequency) {
        self->stashed = self->frequency;
        self->frequency = 0;
    } else {
        self->frequency = self->stashed;
        AFTER(MSEC(500) / self->frequency, self, output, 0);
    }

    PRINT();
    return 0;
}

#define MAX_FREQUENCY 99

int increment(PulseGenerator *self, __attribute__((unused)) int _x) {
    if (self->frequency == 0)
        AFTER(MSEC(500), self, output, 0);

    if (self->frequency < MAX_FREQUENCY)
        self->frequency++;

    PRINT();
    return 0;
}

int decrement(PulseGenerator *self, __attribute__((unused)) int _x) {
    if (self->frequency > 0)
        self->frequency--;

    PRINT();
    return 0;
}
