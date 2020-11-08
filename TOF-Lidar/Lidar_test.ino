#include <SoftwareSerial.h>   
#include <Wire.h> 

#include <Adafruit_VL6180X.h>


// address we will assign if dual sensor is present 

#define LOX1_ADDRESS 0x30 

#define LOX2_ADDRESS 0x31 

#define LOX3_ADDRESS 0x32 

#define LOX4_ADDRESS 0x33 

// set the pins to shutdown
#define SHT_LOX1 7
#define SHT_LOX2 6
#define SHT_LOX3 5
#define SHT_LOX4 52

// Optional define GPIO pins to check to see if complete
#define GPIO_LOX1 4
#define GPIO_LOX2 3
#define GPIO_LOX3 2
#define GPIO_LOX4 53

 

#define TIMING_PIN 9 

 

// objects for the VL6180X 

Adafruit_VL6180X lox1 = Adafruit_VL6180X(); 

Adafruit_VL6180X lox2 = Adafruit_VL6180X(); 

Adafruit_VL6180X lox3 = Adafruit_VL6180X(); 

Adafruit_VL6180X lox4 = Adafruit_VL6180X();

//Adafruit_VL6180X vl = Adafruit_VL6180X(); 
//SoftwareSerial port(TX, RX); 

SoftwareSerial portOne(10, 10); 

SoftwareSerial portTwo(11, 11); 

SoftwareSerial portThree(12,12);  

SoftwareSerial portFour(13,13); 

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

  
  while (!Serial) { 

    delay(1); 

  } 

  

  Serial.println("Sensor found!"); 

  portOne.begin(115200); 

  portTwo.begin(115200); 

  portThree.begin(115200); 

  portFour.begin(115200); 

  Serial.println("initializing"); 

  //TOF set up////////////////////////////////////////////////////////

  pinMode(SHT_LOX1, OUTPUT); 

  pinMode(SHT_LOX2, OUTPUT); 

  pinMode(SHT_LOX3, OUTPUT); 

  pinMode(SHT_LOX4, OUTPUT); 

 

  // Enable timing pin so easy to see when pass starts and ends 

  pinMode(TIMING_PIN, OUTPUT); 

 

#ifdef GPIO_LOX1 

  // If we defined GPIO pins, enable them as PULL UP 

  pinMode(GPIO_LOX1, INPUT_PULLUP); 

  pinMode(GPIO_LOX2, INPUT_PULLUP); 

  pinMode(GPIO_LOX3, INPUT_PULLUP); 

  pinMode(GPIO_LOX4, INPUT_PULLUP); 

#endif 

 

  Serial.println("Shutdown pins inited..."); 

 

  digitalWrite(SHT_LOX1, LOW); 

  digitalWrite(SHT_LOX2, LOW); 

  digitalWrite(SHT_LOX3, LOW); 

  digitalWrite(SHT_LOX4, LOW); 

  digitalWrite(TIMING_PIN, LOW); 

  Serial.println("All in reset mode...(pins are low)"); 

 

 

  Serial.println("Starting..."); 

  setID(); 


} 

  

void loop() { 

  read_sensors();

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

      Serial.println("TFmini 1"); 

      Serial.print(distance1); 

      Serial.print("cm\t"); 

      Serial.print("strength1: "); 

      Serial.print(strength1); 

      Serial.print("\n"); 

    } 

  } 

   

  receiveComplete1 = false; 

   

  while(!receiveComplete2) { 

    getTFminiData(&portTwo, &distance2, &strength2, &receiveComplete2); 

  

    if(receiveComplete2) {  

  

      Serial.println("TFmini 2"); 

      Serial.print(distance2); 

      Serial.print("cm\t"); 

      Serial.print("strength2: "); 

      Serial.println(strength2); 

  

    } 

  } 

  receiveComplete2 = false; 

  

  while(!receiveComplete3) { 

    getTFminiData(&portThree, &distance3, &strength3, &receiveComplete3); 

    if(receiveComplete3) { 

      Serial.println("TFmini 3"); 

      Serial.print(distance3); 

      Serial.print("cm\t"); 

      Serial.print("strength3: "); 

      Serial.print(strength3); 

      Serial.print("\n"); 

    } 

  } 

   

  receiveComplete3 = false; 

  

  while(!receiveComplete4) { 

    getTFminiData(&portFour, &distance4, &strength4, &receiveComplete4); 

    if(receiveComplete4) { 

      Serial.println("TFmini 4"); 

      Serial.print(distance4); 

      Serial.print("cm\t"); 

      Serial.print("strength4: "); 

      Serial.print(strength4); 

      Serial.print("\n"); 

    } 

  } 

   

  receiveComplete4 = false; 


  

} 

//TOF functions////////////////////////////////////////////////////////////////////////

void read_sensors() { 

  readSensor(lox1); 

  readSensor(lox2); 

  readSensor(lox3); 

  readSensor(lox4); 

  Serial.println(); 

}


void readSensor(Adafruit_VL6180X &vl) { 

  Serial.print(" Addr: "); 

  Serial.print(vl.getAddress(), HEX); 

 

  float lux = vl.readLux(VL6180X_ALS_GAIN_5); 

//  Serial.print(" Lux: "); Serial.print(lux); 

  uint8_t range = vl.readRange(); 

  uint8_t status = vl.readRangeStatus(); 

 

  if (status == VL6180X_ERROR_NONE) { 

    Serial.print(" Range: "); Serial.print(range); 

  } 

} 


void setID() { 

  // all reset 

  digitalWrite(SHT_LOX1, LOW); 

  digitalWrite(SHT_LOX2, LOW); 

  digitalWrite(SHT_LOX3, LOW); 

  digitalWrite(SHT_LOX4, LOW); 

  delay(10); 

 

  // all unreset 

  digitalWrite(SHT_LOX1, HIGH); 

  digitalWrite(SHT_LOX2, HIGH); 

  digitalWrite(SHT_LOX3, HIGH); 

  digitalWrite(SHT_LOX4, HIGH); 

  delay(10); 

 

  // activating LOX1 and reseting LOX2 

  digitalWrite(SHT_LOX1, HIGH); 

  digitalWrite(SHT_LOX2, LOW); 

  digitalWrite(SHT_LOX3, LOW); 

  digitalWrite(SHT_LOX4, LOW); 

 

  // initing LOX1 

  if (!lox1.begin()) { 

    Serial.println(F("Failed to boot first VL6180X")); 

    while (1); 

  } 

  lox1.setAddress(LOX1_ADDRESS); 

  delay(10); 

 

  // activating LOX2 

  digitalWrite(SHT_LOX2, HIGH); 

  delay(10); 

 

  //initing LOX2 

  if (!lox2.begin()) { 

    Serial.println(F("Failed to boot second VL6180X")); 

    while (1); 

  } 

  lox2.setAddress(LOX2_ADDRESS); 

 

  // activating LOX3 

  digitalWrite(SHT_LOX3, HIGH); 

  delay(10); 

 

  //initing LOX3 

  if (!lox3.begin()) { 

    Serial.println(F("Failed to boot third VL6180X")); 

    while (1); 

  } 

  lox3.setAddress(LOX3_ADDRESS); 

 

  // activating LOX3 

  digitalWrite(SHT_LOX3, HIGH); 

  delay(10); 

 

  // activating LOX4 

  digitalWrite(SHT_LOX4, HIGH); 

  delay(10); 

 

  //initing LOX4 

  if (!lox4.begin()) { 

    Serial.println(F("Failed to boot fourth VL6180X")); 

    while (1); 

  } 

  lox4.setAddress(LOX4_ADDRESS); 

 

  // activating LOX4 

  digitalWrite(SHT_LOX4, HIGH); 

  delay(10); 

} 
