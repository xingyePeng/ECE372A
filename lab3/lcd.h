// Student Name: Xingye Peng
// Due Date: 3/11/2021
// Assignment: Lab3
//
// Description: LCD header file
//


#ifndef LCD_H
#define LCD_H

#include <avr/io.h>


// Initialize pins direction of the all pins used by LCD to output
void initLCDPins();

// LCD Software Initialization
void initLCDProcedure();

// Include initLCDPins & initLCDProcedure
void initLCD();

// Four bit mode setting procedure
void fourBitCommandWithDelay(unsigned char data, unsigned int delay);

void eightBitCommandWithDelay(unsigned char command, unsigned int delay);

// To send LCD command: 4 bit command
void writeCharacter(unsigned char character);


void writeString(const char *string);

void moveCursor(unsigned char x, unsigned char y);



#endif