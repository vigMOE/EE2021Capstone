// This is a simple example to test communication with the motors
// It should make all motor led blink once per second
// Make sure to select the correct type of interface (hardware or serial, with or without tristate buffer)
// and baudrate depending of your configuration.
// Default baudrate is 1000000 (only hardware serial is capable of that speed)

#include <DynamixelMotor.h>

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

// Use broadcast address to affect all connected motors
DynamixelDevice broadcast_device(interface, BROADCAST_ID);
DynamixelMotor motor(interface, BROADCAST_ID);

DynamixelMotor motor16(interface, 16);  //Master 
DynamixelMotor motor14(interface, 13);  //Slave
DynamixelMotor motor12(interface, 11);  //Slave Parallel to Master
DynamixelMotor motor13(interface, 5);  //Slave Parallel to Slave

uint8_t led_state = true;
int16_t maxSpeed = 485;

void setup() 
{
	interface.begin(baudrate);
	delay(100);

	motor.enableTorque();  
	motor.wheelMode();

	Serial.begin(9600);
}

void loop() 
{
	broadcast_device.write(DYN_ADDRESS_LED, led_state);
	led_state=!led_state;
	delay(1000);
	/*// Need to swap this from strings to tlv (maybe)
        if (Serial.available()) {
           String command = Serial.readString();
            if (command == "drive") {
                //Return data to the RPI
                //work this into a TLV instead of string/bytestring
             	//
			}
        }*/
}

//speeds must be values between (-1023)-(1023)
//fl=x+z
//fr=y+z
//rr=x-z
//rl=y-z
//x=linear_speed
//y=horizontal_speed
//x=angular_speed
void drive(int linear_speed, int horizontal_speed, int angular_speed){
	
	//motor speed calculations with bound checking, see above
	int FL = (linear_speed + angular_speed > maxSpeed)? maxSpeed: ((linear_speed + angular_speed < -maxSpeed)? -maxSpeed: linear_speed + angular_speed);
	int FR = (horizontal_speed + angular_speed > maxSpeed)? maxSpeed: ((horizontal_speed + angular_speed < -maxSpeed)? -maxSpeed: horizontal_speed + angular_speed);

	int RR = (linear_speed - angular_speed > maxSpeed)? maxSpeed: ((linear_speed - angular_speed < -maxSpeed)? -maxSpeed: linear_speed - angular_speed);
	int RL = (horizontal - angular_speed > maxSpeed)? maxSpeed: ((horizontal - angular_speed < -maxSpeed)? -maxSpeed: horizontal_speed - angular_speed);

	//needs to be checked against hardware (cant really determine which var goes to which motor until we get the board)
	motor16.speed(FL);
	motor14.speed(FR);
	motor12.speed(RR); 
	motor13.speed(RL);
}

/*
+Z is clockwise
-Z is counter-clockwise
			+X

			  FR	
			 -__+ 
	 FL +|  	 
-Y		-|   	 		+Y
				|+ RR
				|-
		 -__+ 
		  RL
		  
		  -X
*/

