#include "encoder.h"
#include <xc.h>

////
// Sends a command to the encoder chip
    // 0 -> reset count to 32,768
    // 1 -> return the count
static int encoder_command(int read) {
    SPI4BUF = read;                                 // send the command
    while(!SPI4STATbits.SPIRBF) { ; }               // wait for the response
    SPI4BUF;                                        // garbage => ignore
    SPI4BUF = 5;                                    // write garbage, but read will have the data
    while (!SPI4STATbits.SPIRBF) { ; }
    return SPI4BUF;
}

////
// Reset the encoder counts (back to 32,768
void encoder_reset(void) {
    encoder_command(0);
}

////
// Get the encoder counts
int encoder_counts(void) {
    encoder_command(1);         // first call is garbage => laggs sometimes
    return encoder_command(1);
}

////
// Return the encoder angle in terms of degrees [-180, 180]
int encoder_angle(void) {
    // reduce to (-360, 360) first, then reduce to [-180, 180]
    int temp = (((encoder_counts() - ANGLE_RESET) % CYCLE_COUNTS) * 360 / CYCLE_COUNTS);
    if(temp > 0 && temp > 180) {
        return temp - 360;
    } else if(temp < 0 && temp < -180) {
        return temp + 360;
    } else {
       return temp; 
    }
}


////
// Inititalize the encoder registers
void encoder_init(void) {
    // SPI initialization for reading from the decoder chip
    SPI4CON = 0;                // stop and reset SPI4
    SPI4BUF;                    // read to clear the rx receive buffer
    SPI4BRG = 0x4;              // bit rate to 8 MHz, SPI4BRG = 80,000,000 / (2*desired)-1
    SPI4STATbits.SPIROV = 0;    // clear the overflow
    SPI4CONbits.MSTEN = 1;      // master mode
    SPI4CONbits.MSSEN = 1;      // slave select enable
    SPI4CONbits.MODE16 = 1;     // 16 bit mode
    SPI4CONbits.MODE32 = 0;
    SPI4CONbits.SMP = 1;        // sample at the end of the clock
    SPI4CONbits.ON = 1;         // turn SPI on
}
