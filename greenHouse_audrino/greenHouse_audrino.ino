const int ldrledPin = 5; // digital pin 5 
const int ldrPin = A2; // analog pin 0

const int raincapteur_D = 7;
const int raincapteur_A = A3;

#include <Servo.h> 
// Declare the Servo pin 
int servoPin = 8; 
// Create a servo object 
Servo Servo1; 

#include "DHT.h"
#define DHTPIN 4 //D5
#define DHTTYPE DHT11 // DHT 22 (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);

#define MQ2pin (A1)
const int smokeLedPin = 6;

#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement


void setup() { // The setup() function will only run once, after each powerup or reset of the Arduino board.
  Serial.begin(9600);
  pinMode(ldrledPin, OUTPUT); // Here LED is determined as an output or an indicator.
  pinMode(ldrPin, INPUT); // Here LDR sensor is determined as input.
   pinMode(raincapteur_D, INPUT);
  pinMode(raincapteur_A, INPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Servo1.attach(servoPin); 
   dht.begin();
   Servo1.write(0);
}


void loop() { // Void loop is ran again and again and contains main code.
int ldrStatus = analogRead(ldrPin);
if (ldrStatus <= 370) {
  digitalWrite(ldrledPin, HIGH); // If LDR senses darkness led pin high that means led will glow.
Serial.print("Darkness over here,turn on the LED :");
Serial.println(ldrStatus);
} else {
digitalWrite(ldrledPin, LOW); // If LDR senses light led pin low that means led will stop glowing.
Serial.print("There is sufficient light , turn off the LED : ");
Serial.println(ldrStatus);
}


float h = dht.readHumidity();
float t = dht.readTemperature();
float f =  dht.readTemperature(true);

if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println("Failed to read from DHT sensor!");
}

float hif = dht.computeHeatIndex(f, h);
   // Compute heat index in Celsius (isFahreheit = false)
   float hic = dht.computeHeatIndex(t, h, false);
   delay(2000);
   Serial.print ("Humidity: ");
   Serial.print (h);
   Serial.print (" %\t");
   Serial.print ("Temperature: ");
   Serial.print (t);
   Serial.print (" *C ");
   Serial.print (f);
   Serial.print (" *F\t");
   Serial.print ("Heat index: ");
   Serial.print (hic);
   Serial.print (" *C ");
   Serial.print (hif);
   Serial.println (" *F");

   

float   SmokesensorValue = analogRead(MQ2pin); // read analog input pin 0
  
  Serial.print("Smoke Sensor Value: ");
  Serial.print(SmokesensorValue);
  
  if(SmokesensorValue > 200)
  {
    Serial.print(" | Smoke detected!");
    digitalWrite(smokeLedPin,HIGH);
  }else{    
    Serial.print(" No Smoke, everything is normal");
    digitalWrite(smokeLedPin,LOW);
  }
  
  Serial.println("");
  delay(1000); // wait 2s for next reading

//*****
  if(digitalRead(raincapteur_D) == LOW) 
  {
    Servo1.write(0); 
    Serial.println("Digital value : wet"); 
    delay(10); 
  }
else
  {
    Servo1.write(180); 
    Serial.println("Digital value : dry");
    delay(10); 
  }
int val_analogique=analogRead(raincapteur_A); 
 Serial.print("Analog value : ");
 Serial.println(val_analogique); 
 Serial.println("");
  delay(1000);

  //***************
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance <10){
     Servo1.write(180); 
  }
    Servo1.write(180);
}
