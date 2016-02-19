/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include <xc.h>
#include "timer.h"

//Uses timer 2
void delayUs(unsigned int delay){
    //TODO: Create a delay using timer 2 for "delay" microseconds.
    TMR1 = 0;//clear timer 2
    PR1 = (delay*10) - 1;
    IFS0bits.T1IF = 0;//put flag down
    T1CONbits.ON = 1;//turn on timer 2
    while(IFS0bits.T1IF == 0){
    };
    T1CONbits.ON = 0;//stop timer 2
}

void initTimer1(){
    //TODO: Initialize Timer 2.
    TMR1 = 0;//clear timer 2
    T1CONbits.TCKPS = 0;//initial prescalar to 1
    T1CONbits.TCS = 0;//setting the oscillator

    IFS0bits.T1IF = 0;//put flag down

}
