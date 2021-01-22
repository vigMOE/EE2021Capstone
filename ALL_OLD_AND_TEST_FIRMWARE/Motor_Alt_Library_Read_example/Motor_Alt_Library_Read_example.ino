/*
 * Example showing how to read internal register of AX-12A
 * Can be usefull for debugging purposes
 */

#include "Arduino.h"
#include "AX12A.h"

#define DirectionPin   (2u)
#define BaudRate      (115200)
#define ID        (17u)

int reg = 0;

void setup()
{
  Serial.begin(115200);
  ax12a.begin(BaudRate, DirectionPin, &Serial3);
  ax12a.setBD(254u, 115200);
}

void loop()
{
  reg = ax12a.readRegister(ID, AX_PRESENT_VOLTAGE, 1);
  Serial.println(reg);

  delay(1000);

  ax12a.ledStatus(254u, true);
  delay(500);
  ax12a.ledStatus(254u, false);
  delay(500);
}
