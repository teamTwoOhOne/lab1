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

#define PRESCALAR_256   3
#define PRESCALAR_8     1
#define PRESCALAR_1     0

void init_timer_1(){
    TMR1            = 0;                // Keeps Count
    T1CONbits.TCKPS = PRESCALAR_8;      // Configure ticking rate
    PR1             = 999;              // 1 MilliSec - Period Register
    T1CONbits.ON    = 0;                // Turn off Timer
    IFS0bits.T1IF   = 0;                // Put down the interrupt flag
    IEC0bits.T1IE   = 1;                // Enable interupt
    IPC1bits.T1IP   = 7;                // Timer 1 Priority
}

void init_timer_2()
{
    TMR2            = 0;                // CLEAR TIMER
    T2CONbits.TCKPS = PRESCALAR_8;      // SET PRE-SCALAR TO 8
    T2CONbits.TCS   = 0;                // SELECT INTERNAL OSCILLATOR
    IFS0bits.T2IF   = 0;                // PUT DOWN FLAG
}


void delay_us(unsigned int delay)
{
    TMR2                = 0;                // CLEAR TIMER
    PR2                 = delay - 1;        // CALCULATE WAIT COUNT
    IFS0bits.T2IF       = 0;                // PUT DOWN FLAG
    T2CONbits.ON        = 1;                // TURN ON TIMER
    while(
        IFS0bits.T2IF   == 0                // WAIT
    );
    T2CONbits.ON        = 0;                // TURN OFF TIMER
}

void delay_ms(unsigned int delay)
{
    TMR2                = 0;                // CLEAR TIMER
    PR2                 = delay * 1000 - 1; // CALCULATE WAIT COUNT
    IFS0bits.T2IF       = 0;                // PUT DOWN FLAG
    T2CONbits.ON        = 1;                // TURN ON TIMER
    while(
        IFS0bits.T2IF   == 0                // WAIT
    );
    T2CONbits.ON        = 0;                // TURN OFF TIMER
}
