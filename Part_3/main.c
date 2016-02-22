//-----------------------------------------//
// ECE 372A Spring 2016
// Lab Group 201:
// Zachary Finsterwald
// Zakir Mukhida
// Jimmy Lacey
// Raun Rongguo
//-----------------------------------------//


#include <xc.h>
#include <sys/attribs.h>
#include "leds.h"
#include "lcd.h"
#include "interrupt.h"
#include "switch.h"
#include "timer.h"
#include "config.h"

#define press 0
#define release 1

typedef enum stateTypeEnum {
    run, stop, reset_1, reset_2, debounce_1, debounce_2
} stateType;

volatile stateType state;
volatile unsigned int ms_count;

int main(void)
{
    // * INITIALIZE * //
    SYSTEMConfigPerformance(10000000);
    init_timer_1();
    init_timer_2();
    init_sw1();
    init_sw2();
    init_leds();
    init_lcd();
    clear_lcd();
    enableInterrupts();
    state = stop;
    ms_count = 0;
    //----------------//

    unsigned int min, sec, ms = 0;

    while(1)
    {
        min     =   ms_count / 60000;
        sec     = ( ms_count % 60000) / 1000;
        ms      = ((ms_count % 60000) % 1000) / 10;

        switch(state){
            case run:
                turn_on_led(1);
                move_cursor_lcd(0,1);
                print_string_lcd("Running:");
                T1CONbits.ON    = 1;
                display_time_lcd(min, sec, ms);
                break;
            case stop:
                turn_on_led(2);
                move_cursor_lcd(0,1);
                T1CONbits.ON    = 0;
                print_string_lcd("Stopped:");
                move_cursor_lcd(0,2);
                display_time_lcd(min, sec, ms);
                break;
            case reset_1:
                clear_lcd();
                state = reset_2;
                break;
            case reset_2:
                move_cursor_lcd(1,1);
                print_string_lcd("RESET");
                ms_count = 0;
                state = stop;
                break;
            case debounce_1:
                T1CONbits.ON    = 0;
                delay_us(1000);
				break;
            case debounce_2:
                T1CONbits.ON    = 0;
                delay_us(1000);
                break;
        }
    }

    return 0;
}

// Button Interrupt
void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt(void)
{
    IFS1bits.CNGIF = 0;
    IFS1bits.CNDIF = 0;
    PORTG;
    PORTD;
    if(PORTDbits.RD6 == 0) {
      state = reset_1;
    }
    else if(state == run && PORTGbits.RG13 == press) {
      state = debounce_1;
    }
    else if (state == stop && PORTGbits.RG13 == press) {
      state = debounce_2;
    }
    else if(state == debounce_1 && PORTGbits.RG13 == release) {
      state = stop;
    }
    else if(state == debounce_2 && PORTGbits.RG13 == release) {
      state = run;
    }
}

// Timer Interrupt
void __ISR(_TIMER_1_VECTOR, IPL7SRS) _T1Interupt(){
    IFS0bits.T1IF = 0;    // PUT DOWN FLAG
    ms_count++;
}
