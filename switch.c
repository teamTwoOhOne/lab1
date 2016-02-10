/*
 * File:   switch.c
 * Author: Garrett
 *
 * Created on September 19, 2015, 10:46 AM
 */

void initSW2(){
    //TODO: Initialize the appropriate pins to work with the external switch using a
    //change notification interrupt.
    void initSwitch1(){
    //TODO: Initialize switch 1
    TRISDbits.TRISD6 = 1;//set switch to input.
        
    CNCONDbits.ON = 1;//ENABLE INTERRUPT
    CNENDbits.CNIED6 = 1;//enable interrupt of sw1
    IEC1bits.CNDIE = 1;//enable allover interrupt
//    
    IFS1bits.CNDIF = 0;//put flag down
//    
    CNPUDbits.CNPUD6 = 1;//ENABLE PULL UP RESISTOR
}
}
