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
#include "config.h"


/* Please note that the configuration file has changed from lab 0.
 * the oscillator is now of a different frequency.
 */
#define press 0
#define release 1

typedef int bool;
#define true    1
#define false   0


typedef enum stateTypeEnum {
    led1, led2, deBounce1, deBounce2
} stateType;

volatile stateType state, stateNext;
//volatile bool dbCount = false;

int main(void)
{
    SYSTEMConfigPerformance(10000000);
    initTimer1();
    initSW2();
    initLEDs();
    enableInterrupts();
    state = led1;

    while(1)
    {
        //TODO: Using a finite-state machine, define the behavior of the LEDs
        //Debounce the switch
        switch(state){
            case led1:
                turnOnLED(1);
				stateNext = led2;
                break;

            case led2:
                turnOnLED(2);
				stateNext = led1;
                break;

            case deBounce1:
                delayUs(10000);
				break;
            case deBounce2:
                delayUs(10000);
                break;
        }
    }

    return 0;
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt(void){
    //TODO: Implement the interrupt to capture the press of the button
    IFS1bits.CNGIF = 0;
    PORTG;
	if(state == led1 && PORTGbits.RG13 == press) {
        state = deBounce1;
    }
    else if (state == led2 && PORTGbits.RG13 == press) {
        state = deBounce2;
    }
    else if(state == deBounce1 && PORTGbits.RG13 == release) {
        state = led2;
    }
    else if(state == deBounce2 && PORTGbits.RG13 == release) {
        state = led1;
    }
}
