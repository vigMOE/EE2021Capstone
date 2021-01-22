
#include <Wire.h> 

#include <Adafruit_VL6180X.h>

 //TOF defines/////////////////////
 // address we will assign if dual sensor is present
 //LOX1-3 are arms
#define LOX1_ADDRESS 0x30  //30 is an arm TOF
#define LOX2_ADDRESS 0x31  //31 is an arm TOF
#define LOX3_ADDRESS 0x32  //32 is an arm TOF
  //LOX4-7 are body
#define LOX4_ADDRESS 0x33 //33 is under where arm folds 
#define LOX5_ADDRESS 0x34 
#define LOX6_ADDRESS 0x35
#define LOX7_ADDRESS 0x36

// set the pins to shutdown
#define SHT_LOX1 4
#define SHT_LOX2 6
#define SHT_LOX3 8
#define SHT_LOX4 10
#define SHT_LOX5 14
#define SHT_LOX6 18
#define SHT_LOX7 20

// Optional define GPIO pins to check to see if complete
#define GPIO_LOX1 5
#define GPIO_LOX2 7
#define GPIO_LOX3 9
#define GPIO_LOX4 16
#define GPIO_LOX5 15
#define GPIO_LOX6 19
#define GPIO_LOX7 21

#define TIMING_PIN 1





//TOF objects
 Adafruit_VL6180X lox1 = Adafruit_VL6180X();
Adafruit_VL6180X lox2 = Adafruit_VL6180X();
Adafruit_VL6180X lox3 = Adafruit_VL6180X();
Adafruit_VL6180X lox4 = Adafruit_VL6180X();
Adafruit_VL6180X lox5 = Adafruit_VL6180X();
Adafruit_VL6180X lox6 = Adafruit_VL6180X();
Adafruit_VL6180X lox7 = Adafruit_VL6180X();



 

  

void setup() { 

Serial.begin(115200);


  //TOF setup/////////////////////////////////////////////////////////////////
   // wait for serial port to open on native usb devices 

  while (!Serial) { 

    delay(1); 

  } 

   

pinMode(SHT_LOX1, OUTPUT);
  pinMode(SHT_LOX2, OUTPUT);
  pinMode(SHT_LOX3, OUTPUT);
  pinMode(SHT_LOX4, OUTPUT);
  pinMode(SHT_LOX5, OUTPUT);
  pinMode(SHT_LOX6, OUTPUT);
  pinMode(SHT_LOX7, OUTPUT);

  // Enable timing pin so easy to see when pass starts and ends
  pinMode(TIMING_PIN, OUTPUT);

#ifdef GPIO_LOX1
  // If we defined GPIO pins, enable them as PULL UP
  pinMode(GPIO_LOX1, INPUT_PULLUP);
  pinMode(GPIO_LOX2, INPUT_PULLUP);
  pinMode(GPIO_LOX3, INPUT_PULLUP);
  pinMode(GPIO_LOX4, INPUT_PULLUP);
  pinMode(GPIO_LOX5, INPUT_PULLUP);
  pinMode(GPIO_LOX6, INPUT_PULLUP);
  pinMode(GPIO_LOX7, INPUT_PULLUP);
#endif

  Serial.println("Shutdown pins inited...");

  digitalWrite(SHT_LOX1, LOW);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);
  digitalWrite(SHT_LOX4, LOW);
  digitalWrite(SHT_LOX5, LOW);
  digitalWrite(SHT_LOX6, LOW);
  digitalWrite(SHT_LOX7, LOW);
  
//  digitalWrite(TIMING_PIN, LOW);
  Serial.println("All in reset mode...(pins are low)");


  Serial.println("Starting...");
  setID();

 
} 

  

void loop() { 
  
read_sensors();
  

} 

//TOF functions/////////////////////////////////////////////
void setID() {
  // all reset
  digitalWrite(SHT_LOX1, LOW);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);
  digitalWrite(SHT_LOX4, LOW);
  digitalWrite(SHT_LOX5, LOW);
  digitalWrite(SHT_LOX6, LOW);
  digitalWrite(SHT_LOX7, LOW);
  delay(10);

  // all unreset
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, HIGH);
  digitalWrite(SHT_LOX3, HIGH);
  digitalWrite(SHT_LOX4, HIGH);
  digitalWrite(SHT_LOX5, HIGH);
  digitalWrite(SHT_LOX6, HIGH);
  digitalWrite(SHT_LOX7, HIGH);
  delay(10);

  // activating LOX1 and reseting LOX2
   digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);
  digitalWrite(SHT_LOX4, LOW);
  digitalWrite(SHT_LOX5, LOW);
  digitalWrite(SHT_LOX6, LOW);
  digitalWrite(SHT_LOX7, LOW);

   delay(1000);
 Serial.println("Init stage 1");
  
  digitalWrite(SHT_LOX1, HIGH);

  // initing LOX1
  if (!lox1.begin()) {
    Serial.println(F("Failed to boot first VL6180X"));
    while (1);
  }
  lox1.setAddress(LOX1_ADDRESS);
  delay(10);

 delay(1000);
 Serial.println("Init stage 2");

  // activating LOX2
  digitalWrite(SHT_LOX2, HIGH);
  delay(10);

  //initing LOX2
  if (!lox2.begin()) {
    Serial.println(F("Failed to boot second VL6180X"));
    while (1);
  }
  lox2.setAddress(LOX2_ADDRESS);

   delay(1000);
 Serial.println("Init stage 3");

  // activating LOX3
  digitalWrite(SHT_LOX3, HIGH);
  delay(10);

  //initing LOX3
  if (!lox3.begin()) {
    Serial.println(F("Failed to boot third VL6180X"));
    while (1);
  }
  lox3.setAddress(LOX3_ADDRESS);

 delay(1000);
 Serial.println("Init stage 4");

  // activating LOX4
  digitalWrite(SHT_LOX4, HIGH);
  delay(10);

  //initing LOX4
  if (!lox4.begin()) {
    Serial.println(F("Failed to boot fourth VL6180X"));
    while (1);
  }
  lox4.setAddress(LOX4_ADDRESS);
  
delay(1000);
 Serial.println("Init stage 5");


  // activating LOX5
  digitalWrite(SHT_LOX5, HIGH);
  delay(10);

  //initing LOX5
  if (!lox5.begin()) {
    Serial.println(F("Failed to boot fifth VL6180X"));
    while (1);
  }
  lox5.setAddress(LOX5_ADDRESS);

delay(1000);
 Serial.println("Init stage 6");

  // activating LOX6
 // digitalWrite(SHT_LOX6, HIGH);
 // delay(10);
 // digitalWrite(SHT_LOX6, LOW);
 // delay(10);
  digitalWrite(SHT_LOX6, HIGH);
  delay(10);

 // initing LOX6
 // if (!lox6.begin()) {
 //   Serial.println(F("Failed to boot sixth VL6180X"));
 //   while (1);
 // }
  lox6.begin();
  lox6.setAddress(LOX6_ADDRESS);

 delay(1000);
 Serial.println("Init stage 7");

  // activating LOX7
  digitalWrite(SHT_LOX7, HIGH);
  delay(10);

  //initing LOX7
  if (!lox7.begin()) {
    Serial.println(F("Failed to boot seventh VL6180X"));
    while (1);
  }
  lox7.setAddress(LOX7_ADDRESS);


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

void read_sensors() {
  readSensor(lox1);
  readSensor(lox2);
  readSensor(lox3);
  readSensor(lox4);
  readSensor(lox5);
  readSensor(lox6);
  readSensor(lox7);
  Serial.println();
}
