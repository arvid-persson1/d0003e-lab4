#include <avr/io.h>
#include "TinyTimber.h"
#include "gui.h"
#include "init.h"
#include "pulseGenerator.h"
#include "inputManager.h"
#include "interruptHandler.h"

int main(void) {
    init();
    printAt(0, 0);
    printAt(0, 4);

    PulseGenerator p1 = initGen(0, 4);
    PulseGenerator p2 = initGen(4, 6);
    InputManager i = initManager(&p1, &p2);
    InterruptHandler h = initHandler(&i);

    INSTALL(&h, horizontal, IRQ_PCINT0);
    INSTALL(&h, vertical, IRQ_PCINT1);

    return TINYTIMBER(&p1, output, 0);
}
