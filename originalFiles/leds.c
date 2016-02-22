/*
* File:   leds.c
* Author: 
*
* Created on December 27, 2014, 1:31 PM
*/

#include <xc.h>


void initLEDs(){
    //TODO: Initialize the appropriate pins to work with the LEDs
    TRISDbits.TRISD0 = 0; // Run LED
    TRISDbits.TRISD1 = 0; // Stop LED 
}

void turnOnLED(int led){
    
    //TODO: You may choose to write this function
    // as a matter of convenience 
    if(led == 1)
    {
        LATDbits.LATD0 = 1;//turn on led 1
        LATDbits.LATD1 = 0;      
    }
    
    else if(led==2)
    {
        LATDbits.LATD0 = 0;
        LATDbits.LATD1 = 1;
    }

    
}