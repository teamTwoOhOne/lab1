//-----------------------------------------//
// ECE 372A Spring 2016
// Lab Group 201:
// Zachary Finsterwald
// Zakir Mukhida
// Jimmy Lacey
// Raun Rongguo
//-----------------------------------------//

#include <xc.h>
#include "timer.h"

void initTimer2()
{
    TMR2            = 0;    // CLEAR TIMER
    T2CONbits.TCKPS = 1;    // SET PRE-SCALAR TO 8
    T2CONbits.TCS   = 0;    // SELECT INTERNAL OSCILLATOR
    IFS0bits.T2IF   = 0;    // PUT DOWN FLAG
}

void delay_us(unsigned int delay)
{
    TMR2                = 0;            // CLEAR TIMER
    PR2                 = delay;   // CALCULATE WAIT COUNT
    IFS0bits.T2IF       = 0;            // PUT DOWN FLAG
    T2CONbits.ON        = 1;            // TURN ON TIMER
    while(
        IFS0bits.T2IF   == 0            // WAIT
    );
    T2CONbits.ON        = 0;            // TURN OFF TIMER
}

void delay_ms(unsigned int delay)
{
    TMR2                = 0;            // CLEAR TIMER
    PR2                 = delay * 1000; // CALCULATE WAIT COUNT
    IFS0bits.T2IF       = 0;            // PUT DOWN FLAG
    T2CONbits.ON        = 1;            // TURN ON TIMER
    while(
        IFS0bits.T2IF   == 0            // WAIT
    );
    T2CONbits.ON        = 0;            // TURN OFF TIMER
}