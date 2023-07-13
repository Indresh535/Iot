
//// http://arduino.esp8266.com/stable/package_esp8266com_index.json



#define trig 13   // Trig pin
#define echo 11  // Echo Pin 
#define buzzer 12   // Buzzer Pin 
long duration, inches, cm;


void setup()
{
  Serial.begin(9600);
 pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
   pinMode(buzzer, OUTPUT);
   digitalWrite(buzzer, LOW);
}
void loop()
{
 
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long t = pulseIn(echo, HIGH);
  long cm = t / 29 / 2;
   Serial.println("cm");
  Serial.println(cm);
  

  long level= 18-cm; // Change 15 according to your tank depth
  if (level<=2 ){
    digitalWrite(buzzer, HIGH);
    Serial.println("waterlevel is full!");
     delay(1000);
   }else if(level>=16 ){
     Serial.println("waterlevel is Empty!");
    digitalWrite(buzzer, HIGH);
     delay(1000);
  }else{
    digitalWrite(buzzer, LOW);
    }
  
  Serial.println("waterlevel");
  Serial.println(level);
}
