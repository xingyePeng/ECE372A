// Description: This file implements the initialization of an external
// switch.
//----------------------------------------------------------------------//

#include "switch.h"
#include <avr/io.h>

//Setup pin D0 as input 
//Set pull up resistance 
//Setup external interupt with any edge change 

void initSwitchPD0()
{
 //Setup pin D0(hearder 21) as input 
  DDRD &= ~(1 << DDD0);
  PORTD |= (1 << PORTD0); // enable pull-up for PORTD0
// enable the external interrupt INT0 so that any edge of the signal generates asynchronously an interrupt
// to do that we have to enable the EICRA register and bits ISC00 = 1 and ISC01 = 0
  EICRA |=(1<<ISC00);
  EICRA &= ~(1<<ISC01);

// enable the external interrupt mask register so that INT0 bit is enabled for interrupts
  EIMSK |=(1<<INT0);
}