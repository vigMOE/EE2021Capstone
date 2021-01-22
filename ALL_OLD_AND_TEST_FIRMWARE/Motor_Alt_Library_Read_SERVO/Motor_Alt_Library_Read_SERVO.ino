/*
 * Example showing how to read internal register of AX-12A
 * Can be usefull for debugging purposes
 */

#include "Arduino.h"
#include "AX12A.h"

#define DirectionPin   (2u)
//ALL MOTORS ARE ON 115200
//8 == GRIPPER SERVO
//6 == 5th Servo
//18 = 4th Servo 
//12 = 3rd Servo
//6 = 2nd Servo
//11 = Base Servo
#define BaudRate      (115200)
//#define BaudRate      (1000000)
// 16 13 11 5

int reg = 0;

void setup()
{
  Serial.begin(115200);
  //Serial3.begin(1000000u);
  Serial3.begin(115200);
  delay(100);
  ax12a.begin(BaudRate, DirectionPin, &Serial3);
  //BAUD LEVEL CONTROL BLOCK
  //DO NOT CHANGE WITHOUT CONSULTING PM OR APM

  //////////////////////////////
  //CONFIG COMMANDS
  /////////////////////////////
  
  ax12a.setBD(254u, 115200);
  //ax12a.setBD(12u, 200000);

  //ax12a.setID(6u, 100u);
  
  //MAX TEMP SET TO MAX
  delay(100);
  ax12a.setTempLimit(254u, 99);
  //MAX VOLTAGE SET TO MAX
  delay(100);
  ax12a.setVoltageLimit(254u, 50, 160);
  delay(100);  
  ax12a.setMaxTorque(254u, 1000);
  delay(100);
  ax12a.setPunch(254u, 32);
  // RESPONSE DELAY TIME CONTROL BLOCK 
  ax12a.setRDT(254u, 0);
  delay(100);
  /*
  ax12a.setRDT(13u, 0);
  delay(100);
  ax12a.setRDT(11u, 0);
  delay(100);
  ax12a.setRDT(5u, 0);
  delay(100);
  */

  // STATUS RETURN LEVEL CONTROL BLOCK
  // 0 = NO STATUS RESPONSE
  // 1 = PING RESPONSE ONLY
  // 2 = PING & STATUS RESPONSE 
  /*
  ax12a.setSRL(16u, 2);
  delay(100);
  ax12a.setSRL(13u, 2);
  delay(100);
  ax12a.setSRL(11u, 2);
  delay(100);
  ax12a.setSRL(5u, 2);
  delay(100);
  */
}

int8_t test_1 = 5;  
int8_t test_2 = 3;
int return_i = 0;
void loop()
{
  //ax12a.setBD(254u, 115200);
  //////////////////////////////
  //READ VARIOUS REGISTERS
  //////////////////////////////

  
  //READ ID
  return_i = ax12a.readRegister(8u, 3u, 1u);
  Serial.println(return_i);

  //READ BAUD
   return_i = ax12a.readRegister(8u, 4u, 1u);
   Serial.println(return_i);
  
  read_all_IDs();
  
  ax12a.move(ID, 512);
	

  
  //READ ID
  //return_i = ax12a.readRegister(254u, 3u, 1u);
  //Serial.println(return_i);
  //READ BAUD
  //return_i = ax12a.readRegister(254u, 4u, 1u);
  //Serial.println(return_i);
  /*
  return_i = ax12a.readRegister(11u, 3u, 1u);
  Serial.println(return_i);
  return_i = ax12a.readRegister(13u, 3u, 1u);
  Serial.println(return_i);
  return_i = ax12a.readRegister(16u, 3u, 1u);
  Serial.println(return_i);
  //READ TEMP LIMIT
  return_i = ax12a.readRegister(5u, 11u, 1u);
  Serial.println(return_i);
  return_i = ax12a.readRegister(11u, 11u, 1u);
  Serial.println(return_i);
  return_i = ax12a.readRegister(13u, 11u, 1u);
  Serial.println(return_i);
  return_i = ax12a.readRegister(16u, 11u, 1u);
  Serial.println(return_i);
  //READ MAX TORQUE
  return_i = ax12a.readRegister(5u, 14u, 2u);
  Serial.println(return_i);
  return_i = ax12a.readRegister(11u, 14u, 2u);
  Serial.println(return_i);
  return_i = ax12a.readRegister(13u, 14u, 2u);
  Serial.println(return_i);
  return_i = ax12a.readRegister(16u, 14u, 2u);
  Serial.println(return_i);
  //READ PUNCH
  return_i = ax12a.readRegister(5u, 48u, 2u);
  Serial.println(return_i);
  return_i = ax12a.readRegister(11u, 48u, 2u);
  Serial.println(return_i);
  return_i = ax12a.readRegister(13u, 48u, 2u);
  Serial.println(return_i);
  return_i = ax12a.readRegister(16u, 48u, 2u);
  Serial.println(return_i);

  */

  
  ax12a.ledStatus(254u, true);
  delay(500);
  ax12a.ledStatus(254u, false);
  delay(500); 

  
}

void read_all_Registers(uint8_t motor_ID)
{
   for(int i =0; i<73; i++)
  {
  return_i = ax12a.readRegister(motor_ID, i, 1u);
  Serial.print("Register: "); Serial.print(i); Serial.print("   Register return: "); Serial.println(return_i);
  delay(100);
  }
  // ID -> Register -> Length of register

}

void read_all_IDs()
{
   for(int i =0; i<254; i++)
  {
  return_i = ax12a.readRegister(i, 3u, 1u);
  if(return_i != -1)
  {
  Serial.print("Register: "); Serial.print(i); Serial.print("   Register return: "); Serial.println(return_i);
  }
 // delay(2);
  }
  // ID -> Register -> Length of register

}
