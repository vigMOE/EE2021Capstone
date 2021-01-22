/*
 * Example showing how to send position commands to AX-12A
 */

#include "Arduino.h"
#include "AX12A.h"

#define DirectionPin   (1)
#define BaudRate      (115200)
#define ID        (8)

int initial_pos = 512;
int max = initial_pos + 100;
int min = initial_pos - 100;

int pos = initial_pos;
int delta = 5;

void setup()
{
  ax12a.begin(BaudRate, DirectionPin, &Serial);
}

void loop()
{
  pos = pos + delta;

  if (pos > max)
  {
    pos = max;
    delta *= -1;
  }

  if (pos < min)
  {
    pos = min;
    delta *= -1;
  }

  ax12a.move(ID, pos);
  delay(20);
}
