////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Slave Code
// VMI ECE 1-9 
// Writen by: Brian Hill, David Hair
// Assited by: Drake Singh, Gerold Hempt
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <AX12A.h>
#define two Serial3 // Setting up Serial3 as TWO
#define DirectionPin  (2u)
#define BaudRate    (1000000ul)
#define Right   (16u)
#define Left    (13u)
#define Front    (11u)
#define Back   (5u)
int velocity = 800;
int current = 0;
int previous = 0; 

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Motor Stuff
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


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

void halt() {
 ax12a.turn(Front, RIGHT, 0);
 ax12a.turn(Back, RIGHT, 0);
 ax12a.turn(Left, RIGHT, 0);
 ax12a.turn(Right, RIGHT, 0);
}

void moveForward() {
 ax12a.turn(Front, RIGHT, 0);
 ax12a.turn(Back, RIGHT, 0);
 ax12a.turn(Left, LEFT, velocity);
 ax12a.turn(Right, RIGHT, velocity);
}

void adjFR() {
 ax12a.turn(Front, RIGHT, 0);
 ax12a.turn(Back, RIGHT, 0);
 ax12a.turn(Left, LEFT, velocity + 200);
 ax12a.turn(Right, RIGHT, velocity);
}

void adjFL() {
 ax12a.turn(Front, RIGHT, 0);
 ax12a.turn(Back, RIGHT, 0);
 ax12a.turn(Left, LEFT, velocity);
 ax12a.turn(Right, RIGHT, velocity + 200);
}

void moveBackward() {
 ax12a.turn(Front, RIGHT, 0);
 ax12a.turn(Back, RIGHT, 0);
 ax12a.turn(Left, RIGHT, velocity/1.5);
 ax12a.turn(Right, LEFT, (velocity/1.5));
}

void adjBL() {
 ax12a.turn(Front, RIGHT, 0);
 ax12a.turn(Back, RIGHT, 0);
 ax12a.turn(Left, RIGHT, velocity);
 ax12a.turn(Right, LEFT, (velocity) + 200);
}

void adjBR() {
 ax12a.turn(Front, RIGHT, 0);
 ax12a.turn(Back, RIGHT, 0);
 ax12a.turn(Left, RIGHT, (velocity) + 200);
 ax12a.turn(Right, LEFT, (velocity));
}
void moveLeft() {
 ax12a.turn(Front, RIGHT, velocity + 100);
 ax12a.turn(Back, LEFT, (velocity + 100));
 ax12a.turn(Left, RIGHT, 0);
 ax12a.turn(Right, LEFT, 0);
}

void adjLF() {
 ax12a.turn(Front, RIGHT, velocity + 100);
 ax12a.turn(Back, LEFT, (velocity + 100) + 100);
 ax12a.turn(Left, RIGHT, 0);
 ax12a.turn(Right, LEFT, 0);
}

void adjLB() {
 ax12a.turn(Front, RIGHT, (velocity +100) + 100);
 ax12a.turn(Back, LEFT, (velocity + 100));
 ax12a.turn(Left, RIGHT, 0);
  ax12a.turn(Right, LEFT, 0);
}

void moveRight() {
  ax12a.turn(Front, LEFT, velocity);
  ax12a.turn(Back, RIGHT, velocity);
  ax12a.turn(Left, RIGHT, 0);
  ax12a.turn(Right, LEFT, 0);
}

void adjRF() {
  ax12a.turn(Front, LEFT, velocity);
  ax12a.turn(Back, RIGHT, velocity + 200);
  ax12a.turn(Left, RIGHT, 0);
  ax12a.turn(Right, LEFT, 0);
}

void adjRB() {
  ax12a.turn(Front, LEFT, velocity + 200);
  ax12a.turn(Back, RIGHT, velocity);
  ax12a.turn(Left, RIGHT, 0);
  ax12a.turn(Right, LEFT, 0);
}


void moveForwardDist(int dist) {
  dist = ((dist / 5) * 3);
  for (int i = 0; i < dist; i++) {
    ax12a.turn(Front, RIGHT, 0);
    ax12a.turn(Back, RIGHT, 0);
    ax12a.turn(Left, LEFT, velocity);
    ax12a.turn(Right, RIGHT, velocity);
  }
  ax12a.turn(Front, RIGHT, 0);
  ax12a.turn(Back, RIGHT, 0);
  ax12a.turn(Left, RIGHT, 0);
  ax12a.turn(Right, RIGHT, 0);
}

void moveBackwardDist(int dist) {
  dist = ((dist / 5) * 3);
  for (int i = 0; i < dist; i++) {
    ax12a.turn(Front, RIGHT, 0);
    ax12a.turn(Back, RIGHT, 0);
    ax12a.turn(Left, RIGHT, velocity);
    ax12a.turn(Right, LEFT, velocity);
  }
  ax12a.turn(Front, RIGHT, 0);
  ax12a.turn(Back, RIGHT, 0);
  ax12a.turn(Left, RIGHT, 0);
  ax12a.turn(Right, RIGHT, 0);
}

void moveLeftDist(int dist) {
  dist = ((dist / 5) * 3);
  for (int i = 0; i < dist; i++) {
    ax12a.turn(Front, RIGHT, velocity);
    ax12a.turn(Back, LEFT, velocity);
    ax12a.turn(Left, RIGHT, 0);
    ax12a.turn(Right, LEFT, 0);
  }
  ax12a.turn(Front, RIGHT, 0);
  ax12a.turn(Back, RIGHT, 0);
  ax12a.turn(Left, RIGHT, 0);
  ax12a.turn(Right, RIGHT, 0);
}

void moveRightDist(int dist) {
  dist = ((dist / 5) * 3);
  for (int i = 0; i < dist; i++) {
    ax12a.turn(Front, LEFT, velocity);
    ax12a.turn(Back, RIGHT, velocity);
    ax12a.turn(Left, RIGHT, 0);
    ax12a.turn(Right, LEFT, 0);
  }
  ax12a.turn(Front, RIGHT, 0);
  ax12a.turn(Back, RIGHT, 0);
  ax12a.turn(Left, RIGHT, 0);
  ax12a.turn(Right, RIGHT, 0);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Direction Decode
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// for parsing through serial information
// Allows robot to move and adjust
void driveDir(int dir){
  switch(dir){
    case 1:
      halt();
      break;
    case 2:
      moveForward();
      break;
    case 3:
      adjFL();
      break;
    case 4:
      adjFR();
      break;
    case 5: 
      moveBackward();
    case 6: 
      adjBL();
      break;
    case 7:
      adjBR();
      break;
    case 8:
      moveLeft();
    case 9:
      adjLF();
      break;
    case 10:
      adjLB();
      break;
    case 11:
      moveRight();
    case 12:
      adjRF();
      break;
    case 13:
      adjRB();
      break;
    default:
      // do nothing
      break;
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Setup
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  // put your setup code here, to run once:
  motorInitialize();
  two.begin(1000000); // You can switch this to whataver you want. I am just using 9600 as a proof of consept
  Serial.begin(9600); // This is setting up the Serial connection to print to the serial monitor
  pinMode(13,OUTPUT); // This is just to make sure that the board is powered on
  digitalWrite(13,HIGH); // ^^
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Main Loop
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  // put your main code here, to run repeatedly:
  int data; // The data reveived will be stored here   
  if (two.available() > 0) { // This statement is used to read the data and print it
    data = two.read();
    current = data;
    Serial.print("data: ");
    Serial.println(data);
    // compares two previous data points so that we dont ping motors over and over
    if (current != previous){
      driveDir(current);
      previous = current;
    }
  
  }
//    TEST
  driveDir(2);
  delay(1000);
  driveDir(1);
  delay(100);
  driveDir(5);
  delay(1000);
  driveDir(1);
  delay(100);
  driveDir(8);
  delay(1000);
  driveDir(1);
  delay(100);
  driveDir(11);
  delay(1000);
  driveDir(1);
  delay(100);
}
