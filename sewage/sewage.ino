#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
const int trigPin1 = 4;   //D2
const int echoPin1 = 5;    //D1
#define redled 12   //D6
char auth[]="ZoOP7zbXLHurHC0712Se1jG10YtNUqLy";
char ssid[] = "redmi";
char pass[] = "12345678";
int duration1,distance1;
int count=0;
void setup()
{
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(A0, INPUT);
  digitalWrite(A0, OUTPUT);
  pinMode(redled, OUTPUT);
  digitalWrite(redled, LOW);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}
void loop()
{
  int float1=analogRead(A0);
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1 * 0.034 / 2;
  Serial.println("distance1");
  Serial.println(distance1);
  Serial.println("float1");
  Serial.println(float1);
   Blynk.virtualWrite(V3,distance1);
   if(distance1<=5)
   {
    Blynk.notify("Blockage Alert!");
    digitalWrite(redled, HIGH);
   }
   else if(float1<=800)
   {
    Blynk.notify("Overflow Alert !");
     digitalWrite(redled, HIGH);
   }
      else
   {
    digitalWrite(redled, LOW);
   }
    Blynk.run();
   }
