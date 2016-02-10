/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include <xc.h>

//Uses timer 2
void initTimer1(){
    //TODO: Initialize Timer 1 to have a period of
    // 1 second. Enable its interrupt
    T1CONbits.TCKPS = 3;//initial prescalar to 256
    T1CONbits.TCS = 0;//setting the oscillator
    TMR1 = 0;//clear timer 1
    PR1 = 4882;//initial 1 second PR1 
    IFS0bits.T1IF = 0;//put flag down
    IPC1bits.T1IP = 3;
    IPC1bits.T1IS = 3;
    IEC0bits.T1IE = 1;//enable interrupt 
    T1CONbits.TON = 1;//turn the timer on
}

void initTimer2(){
    //TODO: Initialize Timer 2.
    TMR2 = 0;//clear timer 2
    T2CONbits.TCKPS = 0;//initial prescalar to 1
    T2CONbits.TCS = 0;//setting the oscillator
    
    IFS0bits.T2IF = 0;//put flag down
    
    
    
}
void delayUs(unsigned int delay){
    //TODO: Create a delay using timer 2 for "delay" microseconds.
    TMR2 = 0;//clear timer 2
    PR2 = (delay*624);
    IFS0bits.T2IF = 0;//put flag down
    T2CONbits.ON = 1;//turn on timer 2
    while(IFS0bits.T2IF = 0){
    };
    T2CONbits.ON = 0;//stop timer 2 yep
}