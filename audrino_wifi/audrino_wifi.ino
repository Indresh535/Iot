/*************************************************************
  WARNING!
    It's very tricky to get it working. Please read this article:
    http://help.blynk.cc/hardware-and-libraries/arduino/esp8266-with-at-firmware

  Simple push notification example

  App project setup:
    Push widget

  Connect a button to pin 2 and GND...
  Pressing this button will also push a message! ;)
 *************************************************************/

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID           "TMPL-RXxENsa"
#define BLYNK_DEVICE_NAME           "ardino"
#define BLYNK_AUTH_TOKEN            "VA4Vv_kubBnPi9TjSpvdNI_XIkDBMP_C"


// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial


#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "xiaomi";
char pass[] = "12345678";

// Hardware Serial on Mega, Leonardo, Micro...
#define EspSerial Serial

// or Software Serial on Uno, Nano...
#include <SoftwareSerial.h>
//SoftwareSerial EspSerial(2, 3); // RX, TX

// Your ESP8266 baud rate:
#define ESP8266_BAUD 38400

ESP8266 wifi(&EspSerial);

BlynkTimer timer;

void notifyUptime()
{
  long uptime = millis() / 60000L;

  // Actually send the message.
  // Note:
  //   We allow 1 notification per 5 seconds for now.
  Blynk.notify(String("Running for ") + uptime + " minutes.");

  // You can also use {DEVICE_NAME} placeholder for device name,
  // that will be replaced by your device name on the server side.
  // Blynk.notify(String("{DEVICE_NAME} running for ") + uptime + " minutes.");
}

void setup()
{
  // Debug console
  Serial.begin(115200);

  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, wifi, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, wifi, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Notify immediately on startup
  Blynk.notify("Device started");

  // Setup a function to be called every minute
  timer.setInterval(60000L, notifyUptime);
}

void loop()
{
  Blynk.run();
  timer.run();
}
