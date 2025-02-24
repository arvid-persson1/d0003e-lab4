#include "inputManager.h"
#include "init.h"

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
