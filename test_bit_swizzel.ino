void setup() {
  // put your setup code here, to run once:
 Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  double opcode = 4;
  int pulse[8];

  //Serial.print(opcode >> 1);


  
//     double dickms = (4.0 & pow(2,2));
//     Serial.print(dickms);
//     delay(1000);
 

  for(float i = 0; i <= 7; i++)
  {
     double bubble = (opcode & (pow(2,i));
     pulse[i] = (int)bubble;
     Serial.print(pulse[i]);
     delay(1000);
  }

//  Serial.println(opcode & ((2^(2))-((2^(1)))));
  Serial.println("newline");
  for(;;)
  {
    
  }
}
