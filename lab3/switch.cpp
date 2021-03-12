#include<avr/io.h>
#include "switch.h"

void initSwitchPB3(){
    
// set PortB3 as direction for input（Pin 50)
 DDRB&= ~(1 << DDB3);

// enable the pullup resistor for stable input on PortB3
PORTB|= (1 << PORTB3);

// enable the Group PCINT for 7:0
PCICR |=(1<<PCIE0);

//enable the Local PCINT3
PCMSK0 |=(1<<PCINT3);
}