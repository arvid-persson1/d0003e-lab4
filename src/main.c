#include <avr/io.h>
#include "TinyTimber.h"
#include "init.h"
#include "display.h"
#include "pulseGenerator.h"
#include "inputManager.h"
#include "interruptHandler.h"

int main(void) {
    init();

    Display d = initDisp();
    // XXX: TT is not started yet, no synchronization required.
    print(&d, PACK_PRINT(0, 0));
    print(&d, PACK_PRINT(0, 4));

    PulseGenerator p1 = initGen(&d, 0, 4);
    PulseGenerator p2 = initGen(&d, 4, 6);
    InputManager i = initManager(&p1, &p2);
    InterruptHandler h = initHandler(&i);

    INSTALL(&h, horizontal, IRQ_PCINT0);
    INSTALL(&h, vertical, IRQ_PCINT1);

    return TINYTIMBER(&p1, output, 0);
}
