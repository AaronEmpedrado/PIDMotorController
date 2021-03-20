#include "NU32.h"          // config bits, constants, funcs for startup and UART
#include <stdio.h>

// include other header files here
#include "encoder.h"

#define BUF_SIZE 200

int main() 
{
    char buffer[BUF_SIZE];
    NU32_Startup(); // cache on, min flash wait, interrupts on, LED/button init, UART init
    NU32_LED1 = 1;  // turn off the LEDs
    NU32_LED2 = 1;        
    __builtin_disable_interrupts();
    // in future, initialize modules or peripherals here
    encoder_init();
    __builtin_enable_interrupts();

    while(1)
    {
        NU32_ReadUART3(buffer,BUF_SIZE); // we expect the next character to be a menu command
        NU32_LED2 = 1;                   // clear the error LED
        switch (buffer[0]) {
            /* Send Encoder count to client*/
            case 'c':
            {
                sprintf(buffer, "%d\r\n", encoder_counts());
                NU32_WriteUART3(buffer);    
                break;
            }
            /* Send encoder angle to client */
            case 'd':       
            {
                sprintf(buffer,"%d\r\n", encoder_angle()); 
                NU32_WriteUART3(buffer);
                break;
            }
            /* Reset the encoder count */
            case 'e':
            {
                encoder_reset();
                break;
            }
            case 'q':
            {
                // handle q for quit. Later you may want to return to IDLE mode here. 
                break;
            }
            default:
            {
                NU32_LED2 = 0;  // turn on LED2 to indicate an error
                break;
            }
        }
    }
    return 0;
}
