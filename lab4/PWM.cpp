
#include "PWM.h"
#include "ADC.h"
void initPWM()
{
// initalize pin5(PE3) as output 
DDRE |=(1<<DDE3);
// Using timer 3
// set Fast PWM 10-bit mode, non-inverting
// COMnA0 bit =1
// COMnA1 bit =0
TCCR3A |= (1 << COM3A1);
TCCR3A &= ~(1<<COM3A0);

//Use OCRnA register
// for fast PWM 10 bit mode, mode 7:
// WGMn0 =1
// WGMn1 =1
// WGMn2 = 1
// WGMn3 = 0
TCCR3A |=  (1 << WGM30);
TCCR3A |=  (1 << WGM31); 
TCCR3B |= (1 << WGM32);
TCCR3B &= ~(1 << WGM33); 

// Set the prescaler to be 1
TCCR3B |= (1 << CS30);
TCCR3B &= ~((1 << CS31)  | (1 << CS32));






/*****************************************/
// initalize pin6(PH3) as output 
DDRH |=(1<<DDH3);
// Using timer 4
// set Fast PWM 10-bit mode, inverting mode
// COMnA0 bit = 0
// COMnA1 bit =1
TCCR4A |= (1 << COM4A1);
TCCR4A |= (1<<COM4A0);


//Use OCRnA register
// for mode 7:
// WGMn0 =1
// WGMn1 =1
// WGMn2 = 1
// WGMn3 = 0
TCCR4A |=  (1 << WGM40);
TCCR4A |=  (1 << WGM41); 
TCCR4B |= (1 << WGM42);
TCCR4B &= ~(1 << WGM43);

// Set the prescaler to be 1
TCCR4B |= (1 << CS40);
TCCR4B &= ~((1 << CS41)  | (1 << CS42));


}


//Set motor speed and direction with count registers using information obtained by ADC 
//timer3, non-inverting maximum Duty cycle:0 
//timer4, inverted mode maximum duty cycle:1023

void SetMOTORspeed(int result) {
  
    
      if(result<512){//0-2.5V
          OCR4A = 2*result;// should see led1 in brightest mode at result =0, results increase, brightness decreases
          OCR3A=0;//no output
        }

        else if(result==512){//2.5V
          OCR3A=0;
          OCR4A=1023;
        }

        else{//>2.5
          OCR3A=  2*result-1023;// should see led2 in brightest mode at result =1024, results increase, brightness increases
          OCR4A = 1023;
        
          }
  

}
