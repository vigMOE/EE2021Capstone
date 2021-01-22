/*
 * Example showing how to read internal register of AX-12A
 * Can be usefull for debugging purposes
 */

#include "Arduino.h"
#include "AX12A.h"

#define DirectionPin   (2u)
//ALL MOTORS ARE ON 115200
//2 == GRIPPER SERVO
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
  
  ax12a.setBD(254u, 115200);
  //ax12a.setBD(12u, 200000);

  //ax12a.setID(6u, 100u);

  //ANGLE LIMIT BROADCAST
  ax12a.setAngleLimit(254u, 0, 1023);
  delay(100);
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
  //ax12a.torqueStatus(2, true);
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
  
  //Verify motor comms
  read_ID(5); //wheel 
  read_ID(11); //wheel
  read_ID(16); //wheel
  read_ID(13); //wheel
  read_ID(100); //servo arm
  read_ID(90); //servo arm
  read_ID(12); //servo arm
  read_ID(18); //servo arm
  read_ID(6); //servo arm
  read_ID(2); //servo arm
/*
Serial.println("MOTOR 6 REGISTERS");
Serial.println("------------------");
//read_all_registers(6);
delay(1000);
Serial.println("MOTOR 2 REGISTERS");
Serial.println("------------------");
//read_all_registers(2);
delay(1000);
*/

 Serial.println("LOCKING ARMS");
  Serial.println("----------------------------");
  Serial.println("WHEELS");
  ax12a.readPosition(5); //wheel 
  ax12a.readPosition(11); //wheel
  ax12a.readPosition(16); //wheel
  ax12a.readPosition(13); //wheel
  //We'll write servo positions to what we read so that the arm locks automatically
  Serial.println("SERVOs");
  lock = ax12a.readPosition(100); //servo arm
  ax12a.move(100, lock);
  lock = ax12a.readPosition(90); //servo arm
  ax12a.move(90, lock);
  lock = ax12a.readPosition(12); //servo arm
  ax12a.move(12, lock);
  lock = ax12a.readPosition(18); //servo arm
  ax12a.move(18, lock);
  lock = ax12a.readPosition(6); //servo arm
  ax12a.move(6, lock);
  lock = ax12a.readPosition(2); //servo arm
  ax12a.move(2, lock);
  Serial.println("-----------------------------");
  
}

int8_t test_1 = 5;  
int8_t test_2 = 3;
int return_i = 0;
void loop()
{
  //////////////////////////////
  //TEST INPUT
  /////////////////////////////

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
  ax12a.moveSpeed(id_input, position_input, 100);

delay(2000);
  
  //////////////////////////////
  //READ VARIOUS REGISTERS
  //////////////////////////////

  Serial.println("----------------------------");
  ax12a.readPosition(5); //wheel 
  ax12a.readPosition(11); //wheel
  ax12a.readPosition(16); //wheel
  ax12a.readPosition(13); //wheel
  //We'll write servo positions to what we read so that the arm locks automatically
  lock = ax12a.readPosition(100); //servo arm
 // ax12a.move(100, lock);
  lock = ax12a.readPosition(90); //servo arm
 // ax12a.move(90, lock);
  lock = ax12a.readPosition(12); //servo arm
 // ax12a.move(12, lock);
  lock = ax12a.readPosition(18); //servo arm
 // ax12a.move(18, lock);
  lock = ax12a.readPosition(6); //servo arm
 // ax12a.move(6, lock);
  lock = ax12a.readPosition(2); //servo arm
 // ax12a.move(2, lock);
  Serial.println("-----------------------------");
  
  ax12a.ledStatus(254u, true);
  delay(500);
  ax12a.ledStatus(254u, false);
  delay(500); 
  
  //ax12a.move(2u, 0);
  id_input = 0;
  position_input = 0;

  
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
/*
void id_Search()
{
   for(int i =0; i<254; i++)
  {
  return_i = ax12a.readRegister(motor_ID, 3u, 1u);
  if(return_i != -1)
  {
  Serial.print("Register: "); Serial.print(motor_ID); Serial.print("   Register return: "); Serial.println(return_i);
  }
  delay(2);
}
  // ID -> Register -> Length of register
}
*/
