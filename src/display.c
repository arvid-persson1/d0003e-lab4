#include "display.h"
#include "gui.h"

int print(const Display *const self, const int num) {
    printAt(num, self->position);
    return 0;
}
