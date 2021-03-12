#include "lcd.h"
#include "timer.h"
#include <util/delay.h>


// All required pins are set to output
void initLCDPins(){

// Set the direction for data pins
// Set PA0(pin22),PA1(pin23),PA2(pin24),PA3(pin25) direction as output   
DDRA |=(1<<DDA0)|(1<<DDA1)|(1<<DDA2)|(1<<DDA3);

// Set the direction for Rs and EN
// Set PB4(pin10), PB6(pin12) direction as output
DDRB |=(1<<DDB4)|(1<<DDB6);
}

// LCD Software Initialization
void initLCDProcedure(){

    // step1: delay 50 ms
    delayMs0(50);
    // 4 bit command
    // set data to 0011; wait for 4.1ms, that is 4100μs
    fourBitCommandWithDelay(0b0011,4100);  //1
    //set data to 0011; wait for 100μs
    fourBitCommandWithDelay(0b0011,100);   //2
    //set data to 0011; wait for 0μs
    fourBitCommandWithDelay(0b0011,100);   //3
    //set data to 0010; wait for 0μs
    fourBitCommandWithDelay(0b0010,100);
   
    /////////////////////////////////////////////////////////
    // /////////////Four Bit Mode has set ! ! //////////////
    
    //Fuction set
    eightBitCommandWithDelay(0x28,53);
    // Display off
    eightBitCommandWithDelay(0x08,53);
    //Clear display
    eightBitCommandWithDelay(0x01,3000);
    //Entry mode set
    eightBitCommandWithDelay(0x06,53);
    //Display on
    eightBitCommandWithDelay(0b00001100,53);
}

void initLCD(){
    initLCDPins();
    initLCDProcedure();
}

// Four bit mode setting procedure
void fourBitCommandWithDelay(unsigned char data, unsigned int delay){
     //set the first four bits to 0, and then set the top first 4 bits to 0
    PORTA= data& 0x0F;
     // set Rs to be low for command
    // Do not need to manipulate R/W as it connects to the grd
    PORTB &= ~(1<<PORTB6);
    // set En to high      



    PORTB |=(1<<PORTB4);
    //delay 1 microsencond
    delayMs1(1);
    // set En to low
    PORTB &=~(1<<PORTB4);
    // delay required time
    delayMs1(delay);
}


void eightBitCommandWithDelay(unsigned char command, unsigned int delay){
    //Send the top four bits data
    //upper bit 
    PORTA=command>>4;
    // set Rs to be low for command
    // Do not need to manipulate R/W as it connects to the grd
    PORTB &= ~(1<<PORTB6);
    // set En to high
    PORTB |=(1<<PORTB4);
    //delay 1 microsencond
    delayMs1(1);
    // set En to low
    PORTB &=~(1<<PORTB4);

    PORTA=command & 0x0F;
    // set En to high
    PORTB |=(1<<PORTB4);
    //delay 1 microsencond
    delayMs1(1);
    // set En to low
    PORTB &=~(1<<PORTB4);
    // delay required time
    delayMs0(delay);
    
}

void writeCharacter(unsigned char character){
    //send upper four bits
    PORTA= character>>4;
    // RS high, EN high
	PORTB |= (1<<PORTB6);
    PORTB |= (1<<PORTB4);
    //delay 1 microsencond
    delayMs1(1);
    // set En to low
    PORTB &=~(1<<PORTB4);
    
    /////////////////////
    //send lower four bits
    PORTA= character & 0x0F;
    // RS high, EN high
	PORTB |= (1<<PORTB6);
    PORTB |= (1<<PORTB4);
    //delay 1 microsencond
    delayMs1(1);
    // set En to low
    PORTB &=~(1<<PORTB4);
    //delay the execution time
    delayMs1(46);
}

void writeString(const char *string){
      while (*string != '\0')
	{
		writeCharacter(*string);
		++string;
	}
}

//Use the command for changing the DD RAM address to put the cursor somewhere.
void moveCursor(unsigned char x, unsigned char y){
    unsigned char address= 0x80;
    address |= ( (x << 6) & 0xF0) | (y & 0x0F);
	eightBitCommandWithDelay(address,40);
    
}
