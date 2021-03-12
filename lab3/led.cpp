#include<avr/io.h>
#include"led.h"


void initLED(){
    // Set PD0(pin21),PD1(pin20),PD2(pin19),PD3(pin18) direction as output
    DDRD |=(1<<DDD0)|(1<<DDD1)|(1<<DDD2)|(1<<DDD3);    
}

// Turn on LEDs
void turnOnLEDwithChar(unsigned char num_of_Type){
    //set the first four bits to 0, and then set the top first 4 bits to 0
    PORTD= PORTD &(0xF0)|(num_of_Type & 0x0F);
}