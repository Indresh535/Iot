int IR1 = 2;
int IR2 = 3;
int LED1 = 5;
int LED2 = 6;
int LDR = A3;

void setup() 
{
  Serial.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(LDR, INPUT);
   digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
}

void loop() {

  int LDRValue = analogRead(LDR);
  char Onoff=digitalRead(IR1);
  Serial.print("IR VALUE");
  Serial.print(Onoff);
  Serial.print("sensor = ");
  Serial.print(LDRValue);
  delay (500);

 
   digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  Serial.println("It's Bright Outside; Lights status: OFF");

  
  
  if (LDRValue < 50 && digitalRead(IR1) == LOW) 
    {
      digitalWrite(LED1, HIGH);
      Serial.println("It's Dark Outside; LED1 Lights status: ON");
    }
  
  if (LDRValue < 50 && digitalRead(IR2) == LOW) 
    {
      digitalWrite(LED2, HIGH);
      Serial.println("It's Dark Outside; LED2 Lights status: ON");
    }
   

}
