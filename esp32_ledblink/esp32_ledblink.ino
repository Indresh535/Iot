#include <ESP8266WiFi.h>
int LED,led=4;
int Flame_sensor = 5;   //D1
int Flame_detected;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  pinMode(Flame_sensor, INPUT_PULLUP);
  }

void loop() {
  // put your main code here, to run repeatedly
Flame_detected = digitalRead(Flame_sensor);
  Serial.println(Flame_detected);
  digitalWrite(LED, HIGH);
  //delay(100);
  if (Flame_detected == 0) {
    Serial.println("Flame detected...! take action immediately.*****************************************************");
    digitalWrite(LED, HIGH);
    delay(500);
  }
  else
  {
    Serial.println("No Fire detected. stay cool");
    digitalWrite(LED, LOW);
  }
}
