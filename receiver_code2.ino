//Sensor Code
#define audioRec 7
#define audioRectemp 6
#define ledG 9
#define ledR 8

typedef struct    //define struct called counter
{
   unsigned int pwrPlt;
   unsigned int g1;
   unsigned int g2;
} goalX;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(audioRec, INPUT);
  pinMode(audioRectemp, INPUT);
  pinMode(ledG, INPUT);
  pinMode(ledR, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned int opcode = audioCmd();
  Serial.println(opcode);

  goalX coordinates = cypher(opcode);

}


unsigned int audioCmd()
{
  blinkyG();
  Serial.println("begin");

  int check;
  unsigned int opcode;
  
  check = checkRodge();

  

  blinkyR();
  Serial.println("1");

  opcode = (check << 7) | opcode;
  Serial.println(opcode);

  check = checkRodge();

  blinkyR();
  Serial.println("2");

  opcode = (check << 6) | opcode;
  Serial.println(opcode);

  check = checkRodge();

  blinkyR();
  Serial.println("3");

  opcode = (check << 5) | opcode;
  Serial.println(opcode);

  check = checkRodge();

  blinkyR();
  Serial.println("4");

  opcode = (check << 4) | opcode;
  Serial.println(opcode);

  check = checkRodge();

  blinkyR();
  Serial.println("5");

  opcode = (check << 3) | opcode;
  Serial.println(opcode);

  check = checkRodge();

  blinkyR();
  Serial.println("6");
  
  opcode = (check << 2) | opcode;
  Serial.println(opcode);

  check = checkRodge();

  blinkyR();
  Serial.println("7");

  opcode = (check << 1) | opcode;
  Serial.println(opcode);

  check = checkRodge();

  blinkyR();
  Serial.println("8");

  opcode = (check) | opcode;
  Serial.println(opcode);

  return opcode;
}


void blinkyG()   //Blink LED for visual feed back
{
  digitalWrite(ledG, HIGH);
  delay(500);
   
  digitalWrite(ledG, LOW);
  delay(100);
}

void blinkyR()   //Blink LED for visual feed back
{
  digitalWrite(ledR, HIGH);
  delay(500);
   
  digitalWrite(ledR, LOW);
  delay(100);
}

int checkRodge()
{
  int check = 0;
  int rodge = 0;

  do{
    check = digitalRead(7);
    rodge = digitalRead(6);
  }while ((check || rodge) == 0);

  return check;
}

goalX cypher(unsigned int opcode)
{
  
}
