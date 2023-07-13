////Welcome to The IoT Projects
////IoT Based Fire Alarm Notification and control system using ESP8266
//#define BLYNK_PRINT Serial
//#include <ESP8266WiFi.h>
//#include <BlynkSimpleEsp8266.h>
//
//int LED = 14;    //D5
//int RELAY = 16;  //D0
//int Flame_sensor = 5; //D1
//int Flame_detected;
//
//BlynkTimer timer;
//#define BLYNK_TEMPLATE_ID "TMPLsMGKOUxi"
//#define BLYNK_DEVICE_NAME "LED Switch"
//#define BLYNK_AUTH_TOKEN "6ULamcnt84SqMHpGgdS4y-S3OjmiPZzO"
//char auth[] = BLYNK_AUTH_TOKEN; //Auth code sent via Email
//char ssid[] = "DESKTOP-095VUTS 0173";
//char pass[] = "4767o%V4";
//
//
//void setup()
//{
//  Serial.begin(115200);
//  Blynk.begin(auth, ssid, pass);
//  pinMode(LED, OUTPUT);
//  pinMode(RELAY, OUTPUT);
//  digitalWrite(RELAY, HIGH);
//  pinMode(Flame_sensor, INPUT_PULLUP);  
//}
//void loop()
//{
//  Flame_detected = digitalRead(Flame_sensor);
//  Serial.println(Flame_detected);
//  //delay(100);
//  if (Flame_detected == 0) {    
//    digitalWrite(RELAY, LOW);
//    digitalWrite(LED, HIGH);
//    delay(500);
//    Serial.println("Flame detected...! take action immediately.******************************************************************");
//    Blynk.notify("Alert : Fire detected...! take action immediately.");
//  }
//  else
//  {
//    Serial.println("No Fire detected. stay cool");
//    digitalWrite(LED, LOW);
//    digitalWrite(RELAY, HIGH);
//  }
//  Blynk.run();
//  timer.run();
//}




























































//Welcome to The IoT Projects
//IoT Based Fire Alarm Notification and control system using ESP8266

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;

char auth[] = "ZoOP7zbXLHurHC0712Se1jG10YtNUqLy";

char ssid[] = "redmi";  // Type your wifi name
char pass[] = "12345678";  // Type your wifi password


int LED = 14;    //D5
int RELAY = 16;  //D0
int Flame_sensor = 5; //D1
int Flame_detected;


void setup()
{
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  pinMode(RELAY, OUTPUT);
  digitalWrite(LED, LOW);
  digitalWrite(RELAY, HIGH);
  pinMode(Flame_sensor, INPUT_PULLUP);  
  Blynk.begin(auth, ssid, pass);
}
void loop()
{
  Flame_detected = digitalRead(Flame_sensor);
  Serial.println(Flame_detected);
  //delay(100);
  if (Flame_detected == 0) {    
    digitalWrite(RELAY, LOW);
    digitalWrite(LED, HIGH);
    delay(500);
    Blynk.notify("Flame detected...! take action immediately");
    Serial.println("Flame detected...! take action immediately.******************************************************************");
  }
  else
  {
    Serial.println("No Fire detected. stay cool");
    digitalWrite(LED, LOW);
    digitalWrite(RELAY, HIGH);
  }
   Blynk.run();
  timer.run();
}
