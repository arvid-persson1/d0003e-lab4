#include <stdlib.h>
#include <stdint.h>
#include <avr/io.h>
#include "display.h"

static const uint16_t sccTable[] = {
    0x1551, // 0
    0x0110, // 1
    0x1E11, // 2 
    0x1B11, // 3
    0x0B50, // 4
    0x1B41, // 5
    0x1F41, // 6
    0x0111, // 7
    0x1F51, // 8
    0x0B51  // 9
};

void clear(const uint_fast8_t pos) {
    div_t qr = div(pos, 2);

    volatile uint8_t *lcd = &LCDDR0 + qr.quot;
    uint8_t mask = qr.rem ? 0x0F : 0xF0;

    for (uint_fast8_t i = 0; i < 4; i++) {
        *lcd &= mask;
        lcd += 0x5;
    }
}

void writeDigit(const uint_fast8_t digit, const uint_fast8_t pos) {
    if (pos > 5)
        return;

    if (digit > 9) {
        clear(pos);
        return;
    }

    div_t qr = div(pos, 2);

    uint16_t scc = sccTable[digit];
    volatile uint8_t *lcd = &LCDDR0 + qr.quot;
    uint8_t mask = qr.rem ? 0x0F : 0xF0;

    for (uint_fast8_t i = 0; i < 4; i++) {
        uint8_t nib = scc & 0xF;
        if (qr.rem)
            nib <<= 4;

        *lcd = (*lcd & mask) | nib;
        lcd += 0x5;

        scc >>= 4;
    }
}

int print(__attribute__((unused)) const Display *const self, const int map) {
    struct Packed p = ((union PrintPun){ .map = map }).args;

    writeDigit(p.num % 100 / 10, p.pos);
    writeDigit(p.num % 10, p.pos + 1);

    return 0;
}
