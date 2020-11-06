#include <AX12A.h>
#define DirectionPin  (2u)
#define BaudRate    (115200)
#define Right   (16u)
#define Left    (13u)
#define Front    (11u)
#define Back   (5u)
int maxSpeed = 800;
int current = 0;
int previous = 0; 

void motorInitialize() {

//SETS UP OVERALL UNIVERSAL AX-12 COMMS	
 ax12a.begin(BaudRate, DirectionPin, &Serial3);
 
//SETS AX-12s INTO WHEEL MODE
 ax12a.setEndless(Front, ON);
 ax12a.setEndless(Back, ON);
 ax12a.setEndless(Left, ON);
 ax12a.setEndless(Right, ON);
 
//TURNS LEDs ON ALL AX-12s ON
 ax12a.ledStatus(Front, ON);
 ax12a.ledStatus(Back, ON);
 ax12a.ledStatus(Left, ON);
 ax12a.ledStatus(Right, ON);
}


void yeet() {
  //254 is broadcast ID
  ax12a.turn(254u, RIGHT, velocity);
}

void testDrive(){
	drive(800, 0, 0);
	delay(1000);
	drive(0, 800, 0);
	delay(1000);
	drive(0, 0, 0);
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
	ax12a.turn(Front, (FL>0?RIGHT:LEFT), FL);
	ax12a.turn(Back, (RR>0?RIGHT:LEFT), RR);
	ax12a.turn(Left, (RL>0?RIGHT:LEFT), RL);
	ax12a.turn(Right, (FR>0?RIGHT:LEFT), FR);
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



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Setup
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  // put your setup code here, to run once:
  motorInitialize();
  Serial3.begin(115200); // You can switch this to whataver you want. I am just using 9600 as a proof of consept
  Serial.begin(9600); // This is setting up the Serial connection to print to the serial monitor
  
   // put your main code here, to run repeatedly:
  int data; // The data reveived will be stored here   
  if (Serial3.available() > 0) { // This statement is used to read the data and print it
    data = Serial3.read();
    current = data;
    Serial.print("data: ");
    Serial.println(data);
    // compares Serial3 previous data points so that we dont ping motors over and over
    if (current != previous){
      driveDir(current);
      previous = current;
    }
  
  }
	testDrive();
	//init connection to RPI
	
}

void loop() {
	//listen for command from RPI
	//drive
}
