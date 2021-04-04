
#include <avr/io.h>
#include <avr/interrupt.h>
#include "ADC.h"
#include "timer.h"
#include "PWM.h"
//#include <Arduino.h> // only for debugging.  Not on final submission
#include "switch.h"



//Create statemachine for button debouncing
//When system is on motor will rotate based on potentiometer location 
//System turns off when button is pushed

typedef enum stateEnum {
wait_press,
debounce_press,
wait_release,
debounce_release
}statetype;

// Initialize the state to wait press
volatile statetype state=wait_press;
//define a global variable to toggle the mode of the switch (1 is free mode and 2 is press mode)
volatile unsigned int press_button=2;

int main()
{
  //Serial.begin(9600);

   int low=0;
    initTimer0();
    initADC();
    initPWM();
    initSwitchPD0();
    
    sei();

    while(1)
    {
      // if press the switch
      if(press_button==2){
        // Pin5 and 6 are set to low
        SetMOTORspeed(512);
      }

      // if free the switch
else{
      // read the value from ADCL and ADCH register
      low=ADCL;
      low+= ((unsigned int)ADCH)<<8;// low 
      //Serial.println(low);
      //Serial.flush();
      SetMOTORspeed(low);
      }


      //Determine response to the state
      switch(state){
        case wait_press:
        break;

        case debounce_press:
        delayMs(1);
        state=wait_release;
        break;
        case wait_release:  
        break;

        case debounce_release:
        delayMs(1);
        state=wait_press;

      }
    
    }

    return 0;
}

// Establish ISR using external interput on PORTD
ISR(INT0_vect){

    if (state==wait_press){
        state=debounce_press;
      }
      else if (state==wait_release){
        if(press_button==2){ // if the system is in active, switch to inactive mode
          press_button=1;
        }
        else{
          press_button=2;
        }
        state=debounce_release;
      }
  
} 
