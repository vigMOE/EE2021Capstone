#include <Dynamixel.h>
#include <DynamixelInterface.h>
#include <DynamixelMotor.h>
#include <SoftwareSerial.h>     
#include <DynamixelConsole.h>

// direction pin, if you use tristate buffer
#define DIR_PIN 2

// Use this for hardware serial with tristate buffer
const long unsigned int baudrate = 115200;
HardwareDynamixelInterface interface(Serial3, DIR_PIN);

// Use broadcast address to affect all connected motors
DynamixelDevice broadcast_device(interface, BROADCAST_ID);
DynamixelDevice device_16(interface, 16);
DynamixelDevice device_13(interface, 13);
DynamixelDevice device_11(interface, 11);
DynamixelDevice device_5(interface, 5);

DynamixelMotor motor(interface, BROADCAST_ID);

DynamixelMotor motor16(interface, 16);  
DynamixelMotor motor13(interface, 13);  
DynamixelMotor motor11(interface, 11);  
DynamixelMotor motor5(interface, 5);  

uint8_t led_state = true;
int16_t motorSpeed = 1000;    

void setup() 
{
  Serial.begin(115200);
  interface.begin(baudrate);
  Serial3.begin(115200);
  delay(1000);
  motor.regWrite(BROADCAST_ID, 5, 4);
}


void loop() 
{
   for(int i =0; i<73; i++)
  {
  //return_i = ax12a.readRegister(5u, i, 1u);
  Serial.print("Register: "); Serial.print(i); Serial.print("   Register return: "); Serial.println(device_5.read(5, i, 1));
  delay(100);
    
  }
}

void stopMotor()
{
  motor16.speed(0);
  motor11.speed(0); 
  motor5.speed(0);
  motor13.speed(0); 
}

void forward()
{  
  motor5.speed(motorSpeed);
  motor13.speed(-motorSpeed); 

  delay(3000);

  motor5.speed(0);
  motor13.speed(0); 
}

void reverse()
{
  motor5.speed(-motorSpeed);
  motor13.speed(motorSpeed);  

  delay(3000);

  motor5.speed(0);
  motor13.speed(0); 
}

void leftStrafe()
{
  motor11.speed(motorSpeed);
  motor16.speed(-motorSpeed);

  delay(3000);

  motor11.speed(0);
  motor16.speed(0); 
}

void rightStrafe()
{
  motor16.speed(motorSpeed);
  motor11.speed(-motorSpeed); 

  delay(3000);

  motor11.speed(0);
  motor16.speed(0); 
}

void rotate()
{
  motor16.speed(motorSpeed);
  motor11.speed(motorSpeed); 
  motor5.speed(motorSpeed);
  motor13.speed(motorSpeed); 

  delay(3000);

  motor16.speed(0);
  motor11.speed(0); 
  motor5.speed(0);
  motor13.speed(0); 

  motor16.speed(-motorSpeed);
  motor11.speed(-motorSpeed); 
  motor5.speed(-motorSpeed);
  motor13.speed(-motorSpeed); 

  delay(3000);

  motor16.speed(0);
  motor11.speed(0); 
  motor5.speed(0);
  motor13.speed(0); 
}

void motorsTEST()
{
  forward();
  
  reverse();
  
  leftStrafe();

  rightStrafe();

  rotate();

  stopMotor();
}

void motorsUnitTEST()
{
  motor11TEST();
  delay(1000);
  
  motor5TEST();
  delay(1000);
  
  motor13TEST();
  delay(1000);
  
  motor16TEST();
  delay(1000);
}

void motor11TEST()
{
  motor11.speed(motorSpeed);
  delay(3000);
  
  motor11.speed(0);
  
  motor11.speed(-motorSpeed);
  delay(3000);
  
  motor11.speed(0);
}

void motor5TEST()
{
  motor5.speed(motorSpeed);
  delay(3000);
  
  motor5.speed(0);
 
  motor5.speed(-motorSpeed);
  delay(3000);
  
  motor5.speed(0);
}

void motor13TEST()
{
  motor13.speed(motorSpeed);
  delay(3000);
  
  motor13.speed(0);

  motor13.speed(-motorSpeed);
  delay(3000);
  
  motor13.speed(0);
}

void motor16TEST()
{
  motor16.speed(motorSpeed);
  delay(3000);
  
  motor16.speed(0);

  motor16.speed(-motorSpeed);
  delay(3000);
  
  motor16.speed(0);
}
