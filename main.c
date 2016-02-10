// ******************************************************************************************* //
//
// File:         lab1p1.c
// Date:         
// Authors:      
//
// Description: Part 1 for lab 1
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "leds.h"
#include "interrupt.h"
#include "switch.h"
#include "timer.h"


/* Please note that the configuration file has changed from lab 0.
 * the oscillator is now of a different frequency.
 */

typedef enum stateTypeEnum {
    led1, led2, wait//, debouncePress, debounceRelease, debounceRelease2
} stateType;

//TODO: Use volatile variables that change within interrupts
volatile stateType state;
int main(void)
{
    SYSTEMConfigPerformance(10000000);
    
    initTimer2();
    initTimer1();
    initSW2();
    initLEDs();
    while(1)
    {
        //TODO: Using a finite-state machine, define the behavior of the LEDs
        //Debounce the switch
        switch(state){
            case led1:
                TMR1 = 0;
                delayUs(20);
                turnOnLED(1);
                if(PORTDbits.RD6 == 1){
                    state = wait;
                }
                break;
            case led2:
                TMR1 = 0;
                delayUs(20);
                turnOnLED(2);
                if(PORTDbits.RD6 == 1){
                    state = wait;
                }
                break;
            case wait:
                if(PORTDbits.RD6 == 1){
                    state = wait;
                }
                else if(LATDbits.LATD0 == 1 && PORTDbits.RD6== 0){
                    state = led2;
                }
                else if (LATDbits.LATD1 == 1 && PORTDbits.RD6== 0 ){
                    state = led1;
                }
                break;
                
        }
        
        
    }
    
    return 0;
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL3SRS) _CNInterrupt(void){
    //TODO: Implement the interrupt to capture the press of the button

}