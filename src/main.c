#include "init.h"
#include "writer.h"
#include "display.h"
#include "pulse.h"
#include "gui.h"
#include "handler.h"
#include "reader.h"

int main() {
    init();

    Writer w1 = initWriter(4);
    Display d1 = initDisplay(0);
    PulseGenerator p1 = initPulseGen(&w1, &d1, 0);
    printAt(p1.frequency, p1.display->position);

    Writer w2 = initWriter(6);
    Display d2 = initDisplay(4);
    PulseGenerator p2 = initPulseGen(&w2, &d2, 0);
    printAt(p2.frequency, p2.display->position);

    Handler h = initHandler(&p1, &p2);
    Reader r = initReader(&h);
    INSTALL(&r, horizontal, IRQ_PCINT0);
    INSTALL(&r, vertical, IRQ_PCINT1);

    return TINYTIMBER(&p1, output, 0);
}
