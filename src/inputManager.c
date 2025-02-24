#include "inputManager.h"
#include "init.h"

#define CHECK(x, y) !(x & SET(y))
#define LEFT(x)  CHECK(x, 2)
#define RIGHT(x) CHECK(x, 3)
#define PRESS(x) CHECK(x, 4)
#define UP(x)    CHECK(x, 6)
#define DOWN(x)  CHECK(x, 7)

int switchGen(InputManager *self, int pine) {
    if (LEFT(pine) || RIGHT(pine)) {
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

    if (PRESS(pinb)) {
        ASYNC(p, stash, 0);
    } else if (UP(pinb)) {
        holdInc(self, (int)p);
    } else if (DOWN(pinb)) {
        holdDec(self, (int)p);
    }

    return 0;
}
