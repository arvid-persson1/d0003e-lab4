#include "TinyTimber.h"
#include "gui.h"
#include "init.h"
#include <avr/io.h>

typedef struct {
    Object super;
    unsigned int frequency : 7;
    unsigned int state     : 1;
    unsigned int position  : 3;
    unsigned int portBit   : 3;
    unsigned int stashed   : 7;
} PulseGenerator;

#define initGen(pos, pb) { initObject(), 0, 0, pos, pb, 0 }

#define SET(x) (1 << x)

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

typedef struct {
    Object super;
    PulseGenerator *p1, *p2;
    Msg holdHandle;
    unsigned int current : 1;
} InputManager;

#define initManager(p1, p2) { initObject(), p1, p2, NULL, 0 }

#define LEFT SET(2)
#define RIGHT SET(3)
#define UP SET(6)
#define DOWN SET(7)
#define PRESS SET(4)

int switchGen(InputManager *self, int pine) {
    if (!(pine & LEFT) || !(pine & RIGHT)) {
        self->current ^= 1;
    }

    return 0;
}

int holdInc(InputManager *self, int arg) {
    // SAFETY: sizeof(int) >= sizeof(T*).
    // Source and target type are identical.
    PulseGenerator *p = (PulseGenerator*)arg;
    BEFORE(SEC(1), p, increment, 0);

    self->holdHandle = AFTER(SEC(1), self, holdInc, arg);

    return 0;
}

int holdDec(InputManager *self, int arg) {
    // SAFETY: sizeof(int) >= sizeof(T*).
    // Source and target type are identical.
    PulseGenerator *p = (PulseGenerator*)arg;
    BEFORE(SEC(1), p, decrement, 0);

    self->holdHandle = AFTER(SEC(1), self, holdDec, arg);

    return 0;
}

int changeOrStash(InputManager *self, int pinb) {
    if (self->holdHandle != NULL) {
        ABORT(self->holdHandle);
        self->holdHandle = NULL;
    }

    PulseGenerator *p = self->current ? self->p2 : self->p1;

    if (!(pinb & PRESS)) {
        ASYNC(p, stash, 0);
    } else if (!(pinb & UP)) {
        holdInc(self, (int)p);
    } else if (!(pinb & DOWN)) {
        holdDec(self, (int)p);
    }

    return 0;
}

typedef struct {
    Object super;
    InputManager *manager;
} InterruptHandler;

#define initHandler(m) { initObject(), m }

int horizontal(InterruptHandler *self, __attribute__((unused)) int _x) {
    ASYNC(self->manager, switchGen, PINE);
    return 0;
}

int vertical(InterruptHandler *self, __attribute__((unused)) int _x) {
    ASYNC(self->manager, changeOrStash, PINB);
    return 0;
}

int main(void) {
    init();

    PulseGenerator p1 = initGen(0, 4);
    printAt(0, 0);

    PulseGenerator p2 = initGen(4, 6);
    printAt(0, 4);

    InputManager i = initManager(&p1, &p2);
    InterruptHandler h = initHandler(&i);
    INSTALL(&h, horizontal, IRQ_PCINT0);
    INSTALL(&h, vertical, IRQ_PCINT1);

    return TINYTIMBER(&p1, output, 0);
}
