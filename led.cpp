#include<avr/io.h>
#include"led.h"


void initLED(){
    //Configure PinA0(Pin22), PinA1(Pin23), PinA2(Pin24), PinA3(Pin25) to be output
    DDRA |=(1<<DDA0) |(1<<DDA1) |(1<<DDA2)|(1<<DDA3);
    PORTA |= (1 << PORTA0);
    
}


void turnOnLEDwithChar(unsigned char num_Of_Type){
    //Turn on four LEDS with one code
PORTA = PORTA & (0xF0)| (num_Of_Type & 0xF0);
}
