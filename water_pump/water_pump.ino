//Tech Trends Shameer
//Control Water Pump Using Blynk 2.0


#define BLYNK_AUTH_TOKEN "AtkX80ZOBD-QYPHJqfSpSfUWHiDcpF8N"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h> 
 
#include <BlynkSimpleEsp8266.h>
 

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "Redmi Note 10";  // Enter your wifi name
char pass[] = "q62gen83rrzrg87";  // Enter your wifi password

int motor = 5;


BLYNK_WRITE(V0)
{
  if(param.asInt()==1){
    digitalWrite(motor, LOW);
  }
  else{
    digitalWrite(motor, HIGH);
  }
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  Blynk.syncVirtual(V0);  
}


void setup()
{
  // Debug console
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);
  pinMode(motor, OUTPUT);
  pinMode(motor, HIGH);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
}

void loop()
{
  Blynk.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}
