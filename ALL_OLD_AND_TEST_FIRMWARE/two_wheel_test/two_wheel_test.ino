/*
 * Example showing how to use endless mode (wheel mode) on AX-12A
 * Be sure you removed all mechanical assemblies (hinges) before using this code !
 */
#include "Arduino.h"
#include "AX12A.h"

#define DirectionPin   (2u)
#define BaudRate      (115200)
#define ID        (2u)

void setup()
{
  Serial3.begin(115200);
  ax12a.begin(BaudRate, DirectionPin, &Serial3);
  ax12a.setEndless(ID, ON);
  ax12a.turn(ID, RIGHT, 500);
  delay(1000);
  ax12a.turn(ID, LEFT, 500);
  delay(1000);
  ax12a.turn(ID, LEFT, 0);
  ax12a.setEndless(ID, OFF);
  
}

void loop()
{

  ax12a.move(2, 1000);
  delay(1000);
  ax12a.move(2, 10);
  delay(1000);

}
