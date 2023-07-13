
// Example testing sketch for various DHT humidity/temperature sensors

// what digital pin we're connected to
// Uncomment whatever type you're using!
//#define DHTTYPE DHT11 // DHT 11

//#define DHTTYPE DHT21 // DHT 21 (AM2301)
// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor
// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors. This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.int sensorPin = A0; 

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;

char auth[] = "zJeH2JDZ0j3UPE2-UGlcnCcVw8DC1PGz";

char ssid[] = "Nikola369";  // Type your wifi name
char pass[] = "nikolatesla";  // Type your wifi password



#include "DHT.h"
#define DHTPIN 14 //D5
#define DHTTYPE DHT11 // DHT 22 (AM2302), AM2321
#define SensorPin A0 
float sensorValue = 0; 
int relay = 16; //D0
int limit = 800;
DHT dht(DHTPIN, DHTTYPE);

BLYNK_WRITE(V0)
{
  if(param.asInt()==1){
    digitalWrite(relay, LOW);
  }
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  Blynk.syncVirtual(V5);  
}


void setup() {
   Serial.begin(9600);
    Blynk.begin(auth, ssid, pass);
   Serial.println("DHTxx test!");
   pinMode(relay, OUTPUT);
   dht.begin();
}

void loop() {

   delay(2000); // Wait a few seconds between measurements
   float h = random(24.1,26.3);//dht.readHumidity();
   // Reading temperature or humidity takes about 250 milliseconds!
   float t = random(24.1,26.2);//dht.readTemperature();
   // Read temperature as Celsius (the default)
   float f = random(80.1,80.5);//dht.readTemperature(true);
   // Read temperature as Fahrenheit (isFahrenheit = true)
   // Check if any reads failed and exit early (to try again).
   if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println("Failed to read from DHT sensor!");
   }
   Blynk.virtualWrite(V5,sensorValue); //V5 is for Humidity
Blynk.virtualWrite(V6, t); //V6 is for Temperature
Blynk.virtualWrite(V7, f);

   // Compute heat index in Fahrenheit (the default)
   float hif = dht.computeHeatIndex(f, h);
   // Compute heat index in Celsius (isFahreheit = false)
   float hic = dht.computeHeatIndex(t, h, false);
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
   int sensor=0;
int output=(145-map(sensor,0,1023,0,100)); //in place 145 there is 100(it change with the change in sensor)
 Serial.println("output "); 
  Serial.println(output); 
for (int i = 0; i<= 100; i++) 
 { 
 sensorValue = sensorValue + analogRead(SensorPin); 
   delay(1); 
 } 
 sensorValue = sensorValue/100.0;
 Serial.println("moisture:= "); 
 Serial.println(sensorValue);
 if (sensorValue>limit) {
digitalWrite(relay, HIGH); 
}else
  {
    digitalWrite(relay, LOW);
  }
  

 delay(1000); 
 Blynk.run();
timer.run();
}
 










////code is written by Md iqbal
////website:-techiqbal.com
////Youtube:-Techiqbal
//#define BLYNK_PRINT Serial
//#include <OneWire.h>
//#include <SPI.h>
//#include <BlynkSimpleEsp8266.h>
//#include <DHT.h>
//#include <DallasTemperature.h>
//#define ONE_WIRE_BUS 14 // D5
//OneWire oneWire(ONE_WIRE_BUS);
//DallasTemperature sensors(&oneWire);
//char auth[] ="BOsoqmyvsdJSenk51n6EplHN0jqela_aajwi";
//char ssid[] = "Iqbal";
//char pass[] = "Password";
////code written by Md iqbal
////website:-techiqbal.com
////Youtube:-Techiqbal
//#define DHTPIN 2
//#define DHTTYPE DHT11
//DHT dht(DHTPIN, DHTTYPE);
//SimpleTimer timer;
//void sendSensor()
//{
//float h = dht.readHumidity();
//float t = dht.readTemperature();
//float f = dht.readTemperature(true);
//   // Read temperature as Fahrenheit (isFahrenheit = true)
//   // Check if any reads failed and exit early (to try again).
//   if (isnan(h) || isnan(t) || isnan(f)) {
//Serial.println("Failed to read from DHT sensor!");
//return;
//}
//// Compute heat index in Fahrenheit (the default)
//   float hif = dht.computeHeatIndex(f, h);
//   // Compute heat index in Celsius (isFahreheit = false)
//   float hic = dht.computeHeatIndex(t, h, false);
//   Serial.print ("Humidity: ");
//   Serial.print (h);
//   Serial.print (" %\t");
//   Serial.print ("Temperature: ");
//   Serial.print (t);
//   Serial.print (" *C ");
//   Serial.print (f);
//   Serial.print (" *F\t");
//   Serial.print ("Heat index: ");
//   Serial.print (hic);
//   Serial.print (" *C ");
//   Serial.print (hif);
//   Serial.println (" *F");
//Blynk.virtualWrite(V5, h); //V5 is for Humidity
//Blynk.virtualWrite(V6, t); //V6 is for Temperature
//}
//void setup()
//{
//Serial.begin(9600);
//dht.begin();
//
//timer.setInterval(1000L, sendSensor);
//Blynk.begin(auth, ssid, pass);
//sensors.begin();
//}
//int sensor=0;
//int output=0;
//void sendTemps()
//{
//sensor=analogRead(A0);
//output=(145-map(sensor,0,1023,0,100)); //in place 145 there is 100(it change with the change in sensor)
//delay(1000);
//sensors.requestTemperatures();
//float temp = sensors.getTempCByIndex(0);
//Serial.println(temp);
//Serial.print("moisture = ");
//Serial.print(output);
//Serial.println("%");
//Blynk.virtualWrite(V1, temp);
//Blynk.virtualWrite(V2,output);
//delay(1000);
//}
//void loop()
//{
//Blynk.run();
//timer.run();
//sendTemps();
//}
