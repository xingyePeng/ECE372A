// Author:   Xingye Peng
// Net ID:   23568657
// Date:    4/1/2021
// Assignment: Lab 4

#ifndef PWM_H
#define PWM_H

#include <avr/io.h>

void initPWM();

int changeDutyCycle(int dutycycle);
void SetMOTORspeed(int result);


#endif