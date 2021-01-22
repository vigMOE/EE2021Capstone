// This is a simple example to test communication with the motors
// It should make all motor led blink once per second
// Make sure to select the correct type of interface (hardware or serial, with or without tristate buffer)
// and baudrate depending of your configuration.
// Default baudrate is 1000000 (only hardware serial is capable of that speed)

#include <Dynamixel.h>
#include <DynamixelInterface.h>
#include <DynamixelMotor.h>
#include <SoftwareSerial.h>     
#include <DynamixelConsole.h>

// direction pin, if you use tristate buffer
#define DIR_PIN 2

// software serial pins, if you use software serial
//#define SOFT_RX_PIN 3
//#define SOFT_TX_PIN 4

// Use this for hardware serial without tristate buffer
//HardwareDynamixelInterface interface(Serial);

// Use this for hardware serial with tristate buffer
HardwareDynamixelInterface interface(Serial3, DIR_PIN);

// Use this for software serial without tristate buffer
//SoftwareDynamixelInterface interface(SOFT_RX_PIN, SOFT_TX_PIN);

// Use this for software serial with tristate buffer
//SoftwareDynamixelInterface interface(SOFT_RX_PIN, SOFT_TX_PIN, DIR_PIN);

const long unsigned int baudrate = 1000000;

const unsigned long DELAY_TIME = 3000;
//millisDelay motorDelay; //delay object

// Use broadcast address to affect all connected motors
DynamixelDevice broadcast_device(interface, BROADCAST_ID);
DynamixelMotor motor(interface, BROADCAST_ID);

DynamixelMotor motor16(interface, 16);  
DynamixelMotor motor13(interface, 13);  
DynamixelMotor motor11(interface, 11);  
DynamixelMotor motor5(interface, 5);  

uint8_t led_state = true;
int16_t motorSpeed = 1000;     //THIS IS MAX SPEED UNTIL MOTOR MALFUNCTION

void setup() 
{
  Serial.begin(115200);
  interface.begin(baudrate);
  delay(100);


  broadcast_device.write(5 , 0);            //RESPONSE DELAY = 0
    delay(100);
//  motor.write(5 , 0);            //RESPONSE DELAY = 0
//    delay(100);

  broadcast_device.write(48 , 0x3FF);   //CURRENT LIMIT
    delay(100);  
//  motor.write(48 , 0x3FF);   //CURRENT LIMIT
//    delay(100);     
    
  broadcast_device.write(13 , 180);   //VOLTAGE LIMIT
    delay(100);
//  motor.write(13 , 180);   //VOLTAGE LIMIT
//    delay(100);
    
  broadcast_device.write(11 , 99);   //temperature limit = MAX
    delay(100);
//  motor.write(11 , 99);   //temperature limit = MAX
//    delay(100);

  motor.enableTorque();  
    delay(100);

  motor.wheelMode();
    delay(100);

 // for(int i = 0; i<10; i++)
 // {
 //   motorsTEST();
 //   delay(1000);
 // }
  
  //motorsUnitTEST();
  motorsTEST();  //16 13 11 5
  delay(1000);
  uint8_t test_b;
  motor16.read(3, test_b);
  Serial.println(test_b);
  delay(1000);
  motor13.read(3, test_b);
  Serial.println(test_b);
  delay(1000);
  motor11.read(3, test_b);
  Serial.println(test_b);
  delay(1000);
  motor5.read(3, test_b);
  Serial.println(test_b);
  delay(1000);

//  Serial.println(test_c);


  //motor16.speed(1000);
  //motor16.speed(-1000);
  //motor16.speed(1000);
  //motor16.speed(-1000);
  //motor16.speed(1000);


  //forward();
  //reverse();
  //stopMotor();

}

void loop() 
{
  /*
  motor.write(0x19, 0);  //LED Address us 0x25
  delay(1000);
  motor.write(0x19, 1);  //LED Address us 0x25
  delay(1000);

  motor.write(0x05 , 250);
  */
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
