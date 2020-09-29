void setup() {
   Serial.begin(9600);  
}

//TODO switch this to TLV processing instead of string literals
void loop() {
	if (Serial.available()) { 
		String command = Serial.readString();
		if (command == "read_a0") {
			//Return data to the RPI
			//work this into a TLV instead of string/bytestring
			Serial.println(analogRead(A0));
		}
   	}
}
