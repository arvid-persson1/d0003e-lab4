#include "handler.h"

#define UP (1 << 6)
#define DOWN (1 << 7)
#define PRESS (1 << 4)

int switchGen(Handler *const self, __attribute__((unused)) int _x) {
    // TODO: 
    return 0;
}

// TODO: handle hold
int changeFreq(const Handler *const self, const int pinb) {
    PulseGenerator *current = self->p;

    // TODO: do these calls need to be async?
    // Error cases should be impossible, the loops
    // are to detect deviations. Test if an error
    // state is reachable by for example spamming.
    // Also, is the "default" case necessary?
    if (pinb & PRESS) {
        if (SYNC(current, stash, 0) == -1)
            while(1);
    } else if (pinb & UP) {
        if (SYNC(current, increment, 0) == -1)
            while (1);
    } else if (pinb & DOWN) {
        if (SYNC(current, decrement, 0) == -1)
            while(1);
    } else {
        while (1);
    }

    if (SYNC(current->display, print, current->frequency) == -1)
        while (1);

    return 0;
}
