#include <avr/io.h>
#include "timer.h"

// initialize timer
void initTimer0(){

// set mode of operation with WGM bits
// use CTC mode
// WGM2 = 0  WGM1 = 1  WGM0 = 0
TCCR0A &= ~(1 << WGM00);
TCCR0A &= ~(1 << WGM01);
TCCR0B &= ~(1 << WGM02);

}

void delayMs(int delay){

//set up a counter variable to compare with the delay value passed from function
int count=0; 

//turn on a clock using the CS bits and set the prescaler
//For prescaler=64, CS02=0, CS01=1, CS00=1
TCCR0B |= (1 << CS00) | (1 << CS01);
TCCR0B &= ~(1 << CS02);

while(count<delay){
    
    // set the flag down by writing logic one
    TIFR0 |= (1 <<TOV0);
    
    // set the counting register to start at 6;
    TCNT0 = 6;

    //while flag is 0, TCNT0<255, wait
    while (!(TIFR0  & (1 << TOV0)));
    
    //Now that the count has been have officially count 1ms
    //keep counting
    //increment the counter
    count++;
}
    // Once it has reached the delay number it will exit the while loop and turn off the clock
    TCCR0B &=  ~((1 << CS02) | (1 << CS01) | (1 << CS00));

}

