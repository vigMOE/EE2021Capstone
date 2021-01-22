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

int n = 512; // for incoming serial data
int reg = 0;
String readString;
String id_string;
String position_string;
int id_input = 0;
int position_input = 0;
int lock = 0;

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
  
  ax12a.setBD(2, 115200);
  //ax12a.setBD(12u, 200000);

  //ax12a.setID(6u, 100u);

  
  // RESPONSE DELAY TIME CONTROL BLOCK 
  ax12a.setRDT(254u, 0);
  delay(100);
 
}

int8_t test_1 = 5;  
int8_t test_2 = 3;
int return_i = 0;
void loop()
{
  //////////////////////////////
  //TEST INPUT
  /////////////////////////////
 // id_Search();

  while (Serial.available()) {
     id_string = Serial.readStringUntil(':');  //gets one byte from serial buffer
     //Serial.read();
     //delay(2);
     position_string = Serial.readStringUntil('\n');
     Serial.println(id_string);
     Serial.println(position_string);
    //readString += c; //makes the String readString
   // delay(2);  //slow looping to allow buffer to fill with next character
  }

  if (id_string.length() >0 && position_string.length() >= 0) {
    //Serial.println(readString);  //so you can see the captured String
      id_input = id_string.toInt();  //convert readString into a number
      position_input = position_string.toInt();  //convert readString into a number
    Serial.println(id_input); //so you can see the integer
    Serial.println(position_input);
    //myservo.write(n);
    id_string="";
    position_string="";
  }
  ax12a.move(id_input, position_input);
  ax12a.move(2, 500);
  delay(1000);
  ax12a.move(2, 1000);
  
  
  
  ax12a.ledStatus(254u, true);
  delay(500);
  ax12a.ledStatus(254u, false);
  delay(500); 
  
 

  
}

void read_all_registers(uint8_t motor_ID)
{
   for(int i =0; i<75; i++)
  {
  return_i = ax12a.readRegister(motor_ID, i, 1u);
  Serial.print("Register: "); Serial.print(i); Serial.print("   Register return: "); Serial.println(return_i);
  delay(100);
  }
  // ID -> Register -> Length of register

}

void read_ID(uint8_t motor_ID)
{
  /// for(int i =0; i<254; i++)
 // {
  return_i = ax12a.readRegister(motor_ID, 3u, 1u);
 // if(return_i != -1)
 // {
  Serial.print("Register: "); Serial.print(motor_ID); Serial.print("   Register return: "); Serial.println(return_i);
 // }
 // delay(2);
//}
  // ID -> Register -> Length of register

}

void id_Search()
{
  Serial.println("Searching for motors...");
   for(int i =0; i<254; i++)
  {
  return_i = ax12a.readRegister(i, 3u, 1u);
  if(return_i != -1)
  {
  Serial.print("Register: "); Serial.print(i); Serial.print("   Register return: "); Serial.println(return_i);
  }
  delay(2);
}
  // ID -> Register -> Length of register
}
