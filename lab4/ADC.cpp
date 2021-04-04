
#include "ADC.h"  
void initADC()
{

// set reference voltage set to AVCC = 5V output.  
  ADMUX |= (1 << REFS0);
  ADMUX &= ~(1 << REFS1);

//RIGHT JUSTIFIED
//ADLAR=0
ADMUX &= ~(1 << ADLAR);

// set Auto Trigger Source Selection
// Configured in ADCSRB
// Free Running Mode:ADTS2=0,ADTS1=0,ADTS0=0
ADCSRB &= ~((1 << ADTS2) | (1 << ADTS1) | (1 << ADTS0));

// enable ADC and enable auto-triggering
ADCSRA|= (1 << ADEN) | (1 << ADATE);

//Prescaler=128
//ADC clock frequency=16MHz/128=125Khz
//Conversion time: 13*125KHz=104μs
//Maximum sample rate: 1/104μs=9615 sample/s
ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

// disable ADC0 pin digital input - pin A0(ADC0) on board
  DIDR0 |= (1 << ADC0D);

// start the first ADC conversion
  ADCSRA |= ( 1 << ADSC);


}

