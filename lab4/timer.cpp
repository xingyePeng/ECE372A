
#include "timer.h"

/* Initialize timer 0, you should not turn the timer on here.
* You will need to use CTC mode */
void initTimer0()
{
// set mode of operation with WGM bits
// use CTC mode
// WGM2 = 0  WGM1 = 1  WGM0 = 0
TCCR0A &= ~( (1 << WGM00));
TCCR0A |= ( 1 << WGM01);
TCCR0B &= ~ ( 1 << WGM02); 

}


/* This delays the program an amount specified by unsigned int delay.
* Use timer 0. Keep in mind that you need to choose your prescalar wisely
* such that your timer is precise to 1 millisecond and can be used for
* 100-200 milliseconds
*/

//Prescaler=64
//
void delayMs(unsigned int delay)
{

//turn on a clock using the CS bits and set the prescaler
//For prescaler=64
//02=0,01=1,00=0
TCCR0B |= (1 << CS01);
TCCR0B &= ~((1 << CS02)|(1 << CS00));


// count register should start from 0
TCNT0=0;

//set output comparison register
OCR0A = 249; 
    
// set output compare flag down by writing a logic 1
TIFR0 |= (1 << OCF0A);

// poll the flag OCF0A bit to see when it is raised
// while the flag bit OCF0A is down , do nothing
while (( TIFR0 & ( 1 << OCF0A)) == 0) ;

 // Once it has reached the delay number it will exit the while loop and turn off the clock
TCCR0B &= ~( ( 1 << CS02) | ( 1 << CS01) | (1 << CS00));

}