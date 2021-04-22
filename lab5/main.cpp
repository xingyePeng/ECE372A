//Group Members:

#include "i2c.h"
#include <avr/io.h>
#include "Arduino.h"


#define SLA 0x68  // MPU_6050 address with PIN AD0 grounded
#define PWR_MGMT  0x6B // found on page 41 of RM-MPU-6000A_register map document
#define WAKEUP 0x00 //page 254 in ATmega2560 datasheet
#define SL_MEMA_XAX_HIGH  0x3B // found on page 30 of RM-MPU-6000A_register map document
#define SL_MEMA_XAX_LOW   0x3C // found on page 30 of RM-MPU-6000A_register map document
#define SL_MEMA_YAX_HIGH  0x3D // found on page 30 of RM-MPU-6000A_register map document
#define SL_MEMA_YAX_LOW   0x3E // found on page 30 of RM-MPU-6000A_register map document
#define SL_MEMA_ZAX_HIGH  0x3F // found on page 30 of RM-MPU-6000A_register map document
#define SL_MEMA_ZAX_LOW   0x40 // found on page 30 of RM-MPU-6000A_register map document
#define SL_TEMP_HIGH      0x41 // found on page 31 of RM-MPU-6000A_register map document
#define SL_TEMP_LOW       0x42 // found on page 31 of RM-MPU-6000A_register map document

int main() {

Serial.begin(9600); // using serial port to print values from I2C bus
sei(); 
initI2C();  // initialize I2C and set bit rate

signed int x_val = 0;
float x_C = 0;	
signed int y_val = 0;
float y_C = 0;	
signed int z_val = 0;
float z_C = 0;	
//char status;

StartI2C_Trans(SLA);
//status = TWSR & 0xF8;
write(PWR_MGMT);// address on SLA for Power Management
write(WAKEUP); // send data to Wake up from sleep mode

StopI2C_Trans(); // stop tranmission

	
while (1) {

  _delay_ms(1000);
  Read_from(SLA,SL_MEMA_XAX_HIGH);
 // status = TWSR & 0xF8;
  x_val= Read_data(); // read upper value
  Read_from(SLA,SL_MEMA_XAX_LOW);
  x_val = (x_val << 8 )| Read_data(); // append lower value
  //x_C = (float(x_val)/340) + 36.53; 
  Serial.print("X =  ");
  Serial.println(x_val);

   Read_from(SLA,SL_MEMA_YAX_HIGH);
 // status = TWSR & 0xF8;
  y_val= Read_data(); // read upper value
  Read_from(SLA,SL_MEMA_YAX_LOW);
  y_val = (y_val << 8 )| Read_data(); // append lower value
  //y_C = (float(y_val)/340) + 36.53;
  Serial.print("Y =  ");
  Serial.println(y_val);
  
   Read_from(SLA,SL_MEMA_ZAX_HIGH);
 // status = TWSR & 0xF8;
  z_val= Read_data(); // read upper value
  Read_from(SLA,SL_MEMA_ZAX_LOW);
  z_val = (z_val << 8 )| Read_data(); // append lower value
  //Temperature in degrees C = (TEMP_OUT Register Value as a signed quantity)/340 + 36.53
  //z_C = (float(z_val)/340) + 36.53;
  Serial.print("Z =  ");
  Serial.println(z_val);
  
  Serial.println(" ");
  StopI2C_Trans();
}
return 0;

}