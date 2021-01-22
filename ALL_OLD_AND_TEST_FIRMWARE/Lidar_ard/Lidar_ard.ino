#include <SoftwareSerial.h>  
 
//SoftwareSerial port(TX, RX);
SoftwareSerial portOne(10, 10);
SoftwareSerial portTwo(11, 11);
SoftwareSerial portThree(12,12); 
SoftwareSerial portFour(13,13);
SoftwareSerial payLoad(14,15);

void getTFminiData(SoftwareSerial* port, int* distance, int* strength, boolean* complete) {
  static char i = 0;
  char j = 0;
  int checksum = 0; 
  static int rx[9];
 
  port->listen();
  if(port->available()) {  
    rx[i] = port->read();
    if(rx[0] != 0x59) {
      i = 0;
    } else if(i == 1 && rx[1] != 0x59) {
      i = 0;
    } else if(i == 8) {
      for(j = 0; j < 8; j++) {
        checksum += rx[j];
      }
      if(rx[8] == (checksum % 256)) {
        *distance = rx[2] + rx[3] * 256;
        *strength = rx[4] + rx[5] * 256;
        *complete = true;
      }
      i = 0;
    } else {
      i++;
    } 
  }  
}
 
void setup() {
  Serial.begin(115200);
  portOne.begin(115200);
  portTwo.begin(115200);
  portThree.begin(115200);
  portFour.begin(115200);
  payLoad.begin(57600);
  Serial.println("initializing");
}
 
void loop() {
  int distance1 = 0;
  int strength1 = 0;
  boolean receiveComplete1 = false;
 
  int distance2 = 0;
  int strength2 = 0;
  boolean receiveComplete2 = false;
 
  int distance3 = 0;
  int strength3 = 0;
  boolean receiveComplete3 = false;
 
  int distance4 = 0;
  int strength4 = 0;
  boolean receiveComplete4 = false;
 
  while(!receiveComplete1) {
    getTFminiData(&portOne, &distance1, &strength1, &receiveComplete1);
    if(receiveComplete1) {
      Serial.print("  TFmini1  "); Serial.print(distance1); Serial.print("cm  "); Serial.print("strength1: "); Serial.print(strength1); 
      payLoad.print("  TFmini1  "); payLoad.print(distance1); payLoad.print("cm  "); payLoad.print("strength1: "); payLoad.print(strength1); 
    }
  }
  
  receiveComplete1 = false;
  
  while(!receiveComplete2) {
    getTFminiData(&portTwo, &distance2, &strength2, &receiveComplete2);
 
    if(receiveComplete2) { 
 
      Serial.print("  TFmini2  "); Serial.print(distance2); Serial.print("cm  "); Serial.print("strength2: "); Serial.print(strength2);
    payLoad.print("  TFmini2  "); payLoad.print(distance2); payLoad.print("cm  "); payLoad.print("strength2: "); payLoad.print(strength2);
 
    }
  }
  receiveComplete2 = false;
 
  while(!receiveComplete3) {
    getTFminiData(&portThree, &distance3, &strength3, &receiveComplete3);
    if(receiveComplete3) {
      Serial.print("  TFmini3  "); Serial.print(distance3); Serial.print("cm  "); Serial.print("strength3: "); Serial.print(strength3);
    payLoad.print("  TFmini3  "); payLoad.print(distance3); payLoad.print("cm  "); payLoad.print("strength3: "); payLoad.print(strength3);
    }
  }
  
  receiveComplete3 = false;
 
  while(!receiveComplete4) {
    getTFminiData(&portFour, &distance4, &strength4, &receiveComplete4);
    if(receiveComplete4) {
      Serial.print("  TFmini4  "); Serial.print(distance4); Serial.print("cm  "); Serial.print("strength4: ");Serial.print(strength4);
    payLoad.print("  TFmini4  "); payLoad.print(distance4); payLoad.print("cm  "); payLoad.print("strength4: "); payLoad.print(strength4);
    }
  }
  
  receiveComplete4 = false;

  Serial.println();
  payLoad.println();
  delay(1);
}
