//-----------------------------------------//
// ECE 372A Spring 2016
// Lab Group 201:
// Zachary Finsterwald
// Zakir Mukhida
// Jimmy Lacey
// Raun Rongguo
//-----------------------------------------//

#include <xc.h>
#include "switch.h"

void init_sw1()
{
    TRISDbits.TRISD6    = 1;    // Enable input for switch
    CNCONDbits.ON       = 1;    // Turn on CN device
    CNENDbits.CNIED6    = 1;    // Enable CN interrupt for pin
    IEC1bits.CNDIE      = 1;    // Enable overall CN Interrupt
    IFS1bits.CNDIF      = 0;    // Put Interrupt flag down
    CNPUDbits.CNPUD6    = 1;    // Enable Internal Pull-up resistor
}
void init_sw2()
{
    TRISGbits.TRISG13   = 1;    //set switch to input.
    CNCONGbits.ON       = 1;    //ENABLE INTERRUPT
    CNENGbits.CNIEG13   = 1;    //enable interrupt of sw1
    IEC1bits.CNGIE      = 1;    //enable allover interrupt
    IPC8bits.CNIP       = 7;
    IFS1bits.CNGIF      = 0;    //put flag down
}
