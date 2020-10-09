// This is a simple example to test communication with the motors
// It should make all motor led blink once per second
// Make sure to select the correct type of interface (hardware or serial, with or without tristate buffer)
// and baudrate depending of your configuration.
// Default baudrate is 1000000 (only hardware serial is capable of that speed)

#include <DynamixelMotor.h>

// direction pin, if you use tristate buffer
#define DIR_PIN 2

// software serial pins, if you use software serial
#define SOFT_RX_PIN 3
#define SOFT_TX_PIN 4

// Use this for hardware serial without tristate buffer
//HardwareDynamixelInterface interface(Serial);

// Use this for hardware serial with tristate buffer
HardwareDynamixelInterface interface(Serial, DIR_PIN);

// Use this for software serial without tristate buffer
//SoftwareDynamixelInterface interface(SOFT_RX_PIN, SOFT_TX_PIN);

// Use this for software serial with tristate buffer
//SoftwareDynamixelInterface interface(SOFT_RX_PIN, SOFT_TX_PIN, DIR_PIN);

const long unsigned int baudrate = 1000000;

// Use broadcast address to affect all connected motors
DynamixelDevice broadcast_device(interface, BROADCAST_ID);
DynamixelMotor motor(interface, BROADCAST_ID);

DynamixelMotor motor16(interface, 16);  //Master 
DynamixelMotor motor14(interface, 14);  //Slave
DynamixelMotor motor12(interface, 12);  //Slave Parallel to Master
DynamixelMotor motor13(interface, 13);  //Slave Parallel to Slave

uint8_t led_state = true;
//int16_t speedMotor = 1023;

void setup() 
{
  interface.begin(baudrate);
  delay(100);

  motor.enableTorque();  
  motor.wheelMode();
}

void loop() 
{
  broadcast_device.write(DYN_ADDRESS_LED, led_state);
  led_state=!led_state;
  delay(1000);
}

void linear(int motorSpeed)
{
  motor16.speed(motorSpeed);
  motor12.speed(motorSpeed); 
}
/*
void reverse()
{
  motor16.speed(-speedMotor);
  motor12.speed(-speedMotor);  
}*/

void horizontal(int motorSpeed)
{
  motor14.speed(motorSpeed);
  motor13.speed(motorSpeed);
}
/*
void rightStrafe()
{
  motor16.speed(speedMotor);
  motor12.speed(speedMotor); 
}
*/
void rotate(int motorSpeed)
{
  motor16.speed(motorSpeed);
  motor12.speed(motorSpeed); 
  motor13.speed(motorSpeed);
  motor14.speed(motorSpeed); 
}
/*
void motorsTEST()
{
  forward();
  delay(1000);

  reverse();
  delay(1000);

  leftStrafe();
  delay(1000);

  rightStrafe();
  delay(1000);

  coolSpin();
  delay(1000);
}
*/
