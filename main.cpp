#include<avr/io.h>
#include <avr/interrupt.h>
#include"led.h"
#include"switch.h"
#include"timer.h"

#define SHORT_DELAY 100
#define LONG_DELAY 200

//create four states for switch do debounce
typedef enum stateEnum {
wait_press,
debounce_press,
wait_release,
debounce_release
}statetype;

//define state control variable
volatile statetype state=wait_press;

volatile int mydelay=2; // long delay
volatile unsigned int binary=0;

int main(){
  sei(); // Global interrupt 
  initswitchPB3();//initialize swtich
  initTimer0();//initialize timer
  initLED();//initialize LED


  while(1){

      // define unsigned variable char


    //Determine global control variable mydelay's value
      if(mydelay==2){
        turnOnLEDwithChar(binary);
        delayMs(LONG_DELAY);

      }
      else{
        turnOnLEDwithChar(binary);
        // The delay function is in timer1
        delayMs(SHORT_DELAY);

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
      
      binary++;
      if(binary==16){
        binary=0;
      }
  }
  

return (0);

}


//ISR for PCINT
ISR(PCINT0_vect){      
  // if the PCINTwas triggered for press
        if (state==wait_press){
        state=debounce_press;
      }
      else if(state==wait_release){
        if (mydelay==2){
          mydelay=1;
        }
        else{
          mydelay=2;
        }  
        state=debounce_release;
      }
  }

