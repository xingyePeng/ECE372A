// Student Name: Xingye Peng
// Due Date: 3/11/2021
// Assignment: Lab3
//
//Header file of Timer
//


#ifndef TIMER_H
#define TIMER_H


#include <avr/io.h>


// Initialize microsecond timer, using timer 1
void initTimer1();

// Microsecond timer delay
void delayMs1(int delay);

// Initialize millisecond timer, using timer 0
void initTimer0();

// Millisecond timer delay
void delayMs0(int delay);

#endif