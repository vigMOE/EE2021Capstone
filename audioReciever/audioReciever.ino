void setup() {
  Serial.begin(115200);
  pinMode(2,INPUT);

}

void loop() {
  int opcode = getOpcode();
  Serial.print(opcode);
}


  
int getOpcode()
{
  int audioSignal;
  int i;
  int readVal;
  int opcode = 0;
  //Serial.println(digitalRead(2));
  //delay(1000);
  do
  {
    audioSignal = 0;
      for (i = 0; i < 9; i++)
    {
      audioSignal += digitalRead(2); 
      //Serial.println(audioSignal); 
      delay(20);
    }
  } while (audioSignal == 0);

  do
  {
    audioSignal = 0;
      for (i = 0; i < 9; i++)
    {
      audioSignal += digitalRead(2); 
      //Serial.println(audioSignal); 
      delay(20);
    }
  } while (audioSignal > 0);

  delay(3750);

  //Serial.println("work big good");


  for(int j = 0; j <= 5; j++){
    readVal = 0;
    for (int k = 0; k < 9; k++)
    {
      readVal += digitalRead(2); 
      //Serial.print(readVal); 
      //Serial.print("  digit number :");
      //Serial.println(j);
      delay(200);
    }
    
    if (readVal > 0)
    {
      opcode = (1 << j) | opcode;
      //Serial.println(1 << j);
    }
    

    delay(3000);
    
  }
  //Serial.println(opcode); 
  return opcode;
}
