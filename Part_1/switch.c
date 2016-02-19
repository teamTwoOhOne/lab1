/*
 * File:   switch.c
 * Author: Garrett
 *
 * Created on September 19, 2015, 10:46 AM
 */

#include <xc.h>
#include "switch.h"

void initSW2(){
    //TODO: Initialize the appropriate pins to work with the external switch using a
    //change notification interrupt.
    TRISGbits.TRISG13 = 1;//set switch to input.
    CNCONGbits.ON = 1;//ENABLE INTERRUPT
    CNENGbits.CNIEG13 = 1;//enable interrupt of sw1
    IEC1bits.CNGIE = 1;//enable allover interrupt
    IPC8bits.CNIP = 7;
    IFS1bits.CNGIF = 0;//put flag down
    //CNPUGbits.CNPUG13 = 1;//ENABLE PULL UP RESISTOR
}
