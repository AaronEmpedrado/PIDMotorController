#include "utilities.h"
#include <stdio.h>
#include "NU32.h"           // for config bits, constants, funcs for startup and UART

////
// Changes our current mode to the new mode
void set_mode(mode new_mode) {
    MODE = new_mode;
}

////
// Returns our current mode in the form of the enum we defined
mode get_mode(void) {
    return MODE;
}
