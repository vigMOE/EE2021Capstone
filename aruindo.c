void setup() {
   Serial.begin(9600);  
}

//TODO switch this to TLV processing instead of string literals
void loop() {
   if (Serial.available()) { 
      String command = Serial.readString();
      if (command == "led_on") {
         digitalWrite(LED_BUILTIN, HIGH);
      } else if (command == "led_off") {
         digitalWrite(LED_BUILTIN, LOW);
      } else if (command == "read_a0") {
         Serial.println(analogRead(A0));
      }
   }
}
