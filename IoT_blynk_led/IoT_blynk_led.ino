/*************************************************************

  //This is a simple demo of sending and receiving some data.
 // Be sure to check out other examples!
 *************************************************************/

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPLsMGKOUxi"
#define BLYNK_DEVICE_NAME "LED Switch"
#define BLYNK_AUTH_TOKEN "5vW8fh0oXanz6nBV9NJZ1D7959YDWCLL"


// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

int led=32;

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "DESKTOP-095VUTS 0173";
char pass[] = "4767o%V4";



// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  if(param.asInt()==1){
    digitalWrite(32, HIGH);
  }
  else{
    digitalWrite(32, LOW);
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
  pinMode(led, OUTPUT);
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
