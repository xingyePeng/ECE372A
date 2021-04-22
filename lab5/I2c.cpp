#include "i2c.h"
#include <avr/io.h>
#include "Arduino.h"


#define wait_for_completion while(!(TWCR & (1<<TWINT))); //line 2 on page 246 in ATmega2560 datasheet

void initI2C() {

// wake up from power reduction:   if the I2C is in power reduction mode (PRTWI document bit is 1) 
//then it needs to be restored by writing a zero to PRTWI.  
PRR0 &= ~(1 << PRTWI);  //On pg. 236 of ATmega2560 Datasheet 
//Set prescaler TWPS to 1 
// Page 262 in ATmega 2560 datasheet
TWSR |= (1 << TWPS0);
TWSR &= ~(1 << TWPS1);
// generate a 100kHz clock rate
// SCL freq = 16Mhz/(16 + 2(TWBR)*4)
// Set two wire bit rate interface register TWBR
TWBR = 0x12; // bit rate generator = 100k  (TWBR = 18)

TWCR |= (1 << TWINT | 1 << TWEN); // enable two wire interface // line 5 on page 246 in ATmega2560 datasheet

}

 
void StartI2C_Trans(unsigned char SLA) {

//line 1 on page 246 in ATmega2560 datasheet
TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); // clear TWINT, intiate a start condition and enable

while (!(TWCR & (1<<TWINT)));  // wait while flag is low //line 2 on page 246 in ATmega2560 datasheet

TWDR = (SLA << 1)& (0xFE); // slave address + write bit '0'

//page 246 in ATmega2560 datasheet
TWCR = (1<<TWINT)|(1<<TWEN);  // trigger action:clear flag and enable TWI

while (!(TWCR & (1<<TWINT)));  // wait while flag is low //line 2 on page 246 in ATmega2560 datasheet

}

void StopI2C_Trans() {
  
TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO); //stop condition //line 7 on page 246 in ATmega2560 datasheet

}

void write(unsigned char data){
  // this function loads the data passed into the I2C data register and transmits
  TWDR = data; //load data into TWDR register

  TWCR = (1<<TWINT)|(1<<TWEN);  // trigger action:  clear flag and enable TWI //line 3 on page 246 in ATmega2560 datasheet

  while(!(TWCR & (1 << TWINT))); //line 2 on page 246 in ATmega2560 datasheet

}


void Read_from(unsigned char SLA, unsigned char MEMADDRESS){
  StartI2C_Trans(SLA);

  write(MEMADDRESS);
  TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); // restart to switch to read mode //line 1 on page 246 in ATmega2560 datasheet
  wait_for_completion;
  TWDR = (SLA<<1) | 0X01; // 7 bit address for slave plus to read bit
  TWCR = (1<<TWINT)|(1<<TWEN) | (1<<TWEA); // trigger with ack
  wait_for_completion;
  TWCR = (1<<TWINT)|(1<<TWEN); // master in ack mode //line 3 on page 246 in ATmega2560 datasheet
  wait_for_completion;
  TWCR = (1<<TWINT)|(1<<TWEN) | (1<<TWSTO); // stop condition //line 7 on page 246 in ATmega2560 datasheet

}

  
unsigned char Read_data() 
{
    return TWDR; //
}
  