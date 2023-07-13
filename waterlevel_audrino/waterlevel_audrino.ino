
//// http://arduino.esp8266.com/stable/package_esp8266com_index.json



#define trig 13   // Trig pin
#define echo 11  // Echo Pin 
#define ledred 2   // ledReds Pin 
#define ledyellow 3 
#define ledgreen 4
long duration, inches, cm;


void setup()
{
  Serial.begin(9600);
 pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
   pinMode(ledred, OUTPUT);
    pinMode(ledyellow, OUTPUT);
     pinMode(ledgreen, OUTPUT);
     digitalWrite(ledyellow, LOW);
     digitalWrite(ledred, LOW);
     digitalWrite(ledgreen, LOW);
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
    Serial.println("waterlevel is Empty! Turn on the Switch");
    digitalWrite(ledgreen, LOW);
    digitalWrite(ledyellow, LOW);
    digitalWrite(ledred, HIGH);
     delay(1000);
   }else if(level>=14 ){
     Serial.println("waterlevel is full! Take action immediately");
     digitalWrite(ledred, LOW);
     digitalWrite(ledyellow, LOW);
     digitalWrite(ledgreen, HIGH);
     delay(1000);
  }else if(level==8){
    Serial.println("waterlevel is Half");
    digitalWrite(ledred, LOW);
    digitalWrite(ledgreen, LOW);
    digitalWrite(ledyellow, HIGH);
    }else{
      digitalWrite(ledred, LOW);
    digitalWrite(ledgreen, LOW);
    digitalWrite(ledyellow, LOW);
    }
  
  Serial.println("waterlevel");
  Serial.println(level);
}
