#include "timer.h"

// initialize timer,using timer1
//microsecond clock
void initTimer1(){

// set mode of operation with WGM bits
// use CTC mode
// WGM2 = 0  WGM1 = 1  WGM0 = 0
TCCR1A &= ~( (1 << WGM10) | ( 1<< WGM11));
TCCR1B |= ( 1 << WGM12);
TCCR1B &= ~ ( 1 << WGM13); 

}

// function delayMS1 (microsecond delay)
// function takes an int value called delay to delay the total time in microseconds
// this function is limited to delay = 2000 as the upper limit
void delayMs1(int delay_1){


//turn on a clock using the CS bits and set the prescaler
//For prescaler=0, CS02=0, CS01=0, CS00=1
TCCR1B |= (1 << CS10);
TCCR1B &= ~(1 << CS12)|(1 << CS11);


// set the count register to be 0;
TCNT1=0;

//set output compare value
//used the formular OCR0A=(Td*fclk)/PS
//using a Td=1μs, fclk=16Mhz, PS=1
//OCR0A=16
// if we want to pass a value called delay then we can set OCR1A = 62 * delay
// andthat should allow values in ms to be delayed by the right time up to at least 2000ms.
 OCR1A = 16 * delay_1; 
    
// set output compare flag down by writing a logic 1
TIFR1 |= (1 << OCF1A);

// poll the flag OCF1A bit to see when it is raised
// while the flag bit OCF1A is down , do nothing
while (( TIFR1 & ( 1 << OCF1A)) == 0) ;

 // Once it has reached the delay number it will exit the while loop and turn off the clock
TCCR1B &= ~( ( 1 << CS12) | ( 1 << CS11) | (1 << CS10));

}




// initialize timer,using timer 0
// millisecond clock
void initTimer0(){


// set mode of operation with WGM bits
// use CTC mode
// WGM2 = 0  WGM1 = 1  WGM0 = 0
TCCR0A &= ~(1 << WGM00);
TCCR0A &= ~(1 << WGM01);
TCCR0B &= ~(1 << WGM02);
}

// function delayMS0 (delay)
// function takes an int value called delay to delay the total time in milliseconds
void delayMs0(int delay_0){

//set up a counter variable to compare with the delay value passed from function
int count=0; 

//turn on a clock using the CS bits and set the prescaler
//For prescaler=64, CS02=0, CS01=1, CS00=1
TCCR0B |= (1 << CS00) | (1 << CS01);
TCCR0B &= ~(1 << CS02);


while(count<delay_0){
    
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