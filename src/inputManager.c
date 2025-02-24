#include "inputManager.h"
#include "init.h"

#define CHECK(x, y) !(x & SET(y))
#define LEFT(x)  CHECK(x, 2)
#define RIGHT(x) CHECK(x, 3)
#define PRESS(x) CHECK(x, 4)
#define UP(x)    CHECK(x, 6)
#define DOWN(x)  CHECK(x, 7)

#define HOLD_SPEED MSEC(200)

int switchGen(InputManager *const self, const int pine) {
    if (LEFT(pine) || RIGHT(pine)) {
        self->current ^= 1;
    }

    return 0;
}

int holdInc(InputManager *const self, const int arg) {
    // SAFETY: `sizeof(int) >= sizeof(T*)`.
    // Source and target type are identical.
    PulseGenerator *p = (PulseGenerator*)arg;
    SYNC(p, increment, 0);

    self->holdHandle = AFTER(HOLD_SPEED, self, holdInc, arg);

    return 0;
}

int holdDec(InputManager *const self, const int arg) {
    // SAFETY: `sizeof(int) >= sizeof(T*)`.
    // Source and target type are identical.
    PulseGenerator *p = (PulseGenerator*)arg;
    SYNC(p, decrement, 0);

    self->holdHandle = AFTER(HOLD_SPEED, self, holdDec, arg);

    return 0;
}

int changeOrStash(InputManager *const self, const int pinb) {
    if (self->holdHandle != NULL) {
        ABORT(self->holdHandle);
        self->holdHandle = NULL;
    }

    PulseGenerator *p = self->current ? self->p2 : self->p1;

    if (PRESS(pinb)) {
        SYNC(p, stash, 0);
    } else if (UP(pinb)) {
        holdInc(self, (int)p);
    } else if (DOWN(pinb)) {
        holdDec(self, (int)p);
    }

    return 0;
}
