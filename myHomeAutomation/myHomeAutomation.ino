/*************************************************************

  //This is a simple demo of sending and receiving some data.
 // Be sure to check out other examples!
 *************************************************************/

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings

#define BLYNK_AUTH_TOKEN "ZoOP7zbXLHurHC0712Se1jG10YtNUqLy"


// Comment this out to disable prints and save space


#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp32.h>
BlynkTimer timer;

int led=13;//D13    
int led2=25;      //D25                                                                                           
int pirSensor=34;//D34
int Flame_sensor=33;//D33
int buzzer=12;//D12
int Flame_detected;

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "redmi";
char pass[] = "12345678";



// This function is called every time the Virtual Pin 0 state changes

BLYNK_WRITE(V0)
{
  if(param.asInt()==1){
    digitalWrite(led, HIGH);
  }
  else{
    digitalWrite(led, LOW);
  }
}



BLYNK_WRITE(V1)
{
  if(param.asInt()==1){
    digitalWrite(led2, HIGH);
  }
  else{
    digitalWrite(led2, LOW);
  }
}
// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  Blynk.syncVirtual(V0);  
  Blynk.syncVirtual(V1);
}


void setup()
{
  // Debug console
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(pirSensor, INPUT);
  pinMode(Flame_sensor, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  digitalWrite(led, LOW);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
}

void loop()
{
  int pirSensorValue=digitalRead(pirSensor);
  Serial.println("PirSensorValue");
  Serial.println(pirSensorValue);
  Flame_detected = digitalRead(Flame_sensor);
  Serial.println("Flame_detected");
  Serial.println(Flame_detected);

  if(pirSensorValue==1){
    digitalWrite(led,HIGH);  
  }
  
  if(Flame_detected==0){
    digitalWrite(buzzer,HIGH);
    Blynk.notify("Flame detected...! take action immediately");
    Serial.println("Flame detected...! take action immediately.");
  }else{
    digitalWrite(buzzer,LOW);
     Serial.println("Flame Not detected. Stay cool.");
  }

  Blynk.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}
