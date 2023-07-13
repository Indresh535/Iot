#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 2);

#define trigPin 12

#define echoPin 13
int buzzer=7;

long duration, distance;
void setup()
{

mySerial.begin(9600); // Setting the baud rate of GSM Module 
Serial.begin(9600);
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT);
pinMode(buzzer, OUTPUT);
delay(1000);
}




void loop()
{
  delay(150);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2;
  String disp = String(distance);
  Serial.println("distance :");
  Serial.println(disp);  
  Serial.println(" cm");
  if(distance<=5){
    mySerial.println("AT+CMGF=1");
    delay(1000);		
    mySerial.println("AT+CMGS=\"+917676695276\"\r");
    delay(1000); 
    mySerial.println("Garbage Bin is Full.");
    delay(1000);
    mySerial.println((char)26);
    delay(1000);
        digitalWrite(buzzer, HIGH);
    
  }else{
    Serial.print("Still Garbage Bin is not Full "); 
    digitalWrite(buzzer, LOW);
      }
 delay(500);
}
