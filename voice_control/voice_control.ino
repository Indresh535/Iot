#define LedRed 11
#define LedGreen 12

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LedRed, OUTPUT);
  pinMode(LedGreen, OUTPUT);
  digitalWrite(LedRed, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() == 1)
  {
    String val = Serial.readString();
    Serial.println(val);
    if(val == "hello" || "hello" )
    {
      digitalWrite(LedRed, HIGH);
    }
    if(val == "LedRed off" || "bye" )
    {
      digitalWrite(LedRed, LOW);
    }
    if(val == "hello" || "hello" )
    {
      digitalWrite(LedGreen, HIGH);
    }
    if(val == "LedGreen off" || "bye")
    {
      digitalWrite(LedGreen, LOW);
    }
    if(val == "all on" )
    {
      digitalWrite(LedRed, HIGH);
      digitalWrite(LedGreen, HIGH);
    }
    if(val == "all off")
    {
      digitalWrite(LedGreen, LOW);
      digitalWrite(LedRed, LOW);
    }
  }
}
