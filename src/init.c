#include <avr/io.h>
#include "init.h"

void init(void) {
    // Clock
    CLKPR  = SET(CLKPCE);
    CLKPR  = 0;

    // LCD
    LCDCRA = SET(LCDEN)   | SET(LCDAB);
    LCDCRB = SET(LCDCS)
           | SET(LCDMUX1) | SET(LCDMUX0)
           | SET(LCDPM2)  | SET(LCDPM1)  | SET(LCDPM0);
    LCDFRR = SET(LCDCD2)  | SET(LCDCD1)  | SET(LCDCD0);
    LCDCCR = SET(LCDCC3)  | SET(LCDCC2)  | SET(LCDCC1)  | SET(LCDCC0);

    // Joystick
    PORTB  = SET(PB7)     | SET(PB6)     | SET(PB4);
    PORTE  = SET(PE3)     | SET(PE2);
    EIMSK  = SET(PCIE1)   | SET(PCIE0);
    PCMSK0 = SET(PCINT3)  | SET(PCINT2);
    PCMSK1 = SET(PCINT15) | SET(PCINT14) | SET(PCINT12);
}
