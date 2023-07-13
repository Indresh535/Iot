
/* This code for the Arduino Distance meter with LCD output
 * Install the LicuidCrystal I2c.h & LicuidCrystal I2c LCD library to your IDE
 *  *  * Upload this code to the Arduino UNO, NANO, Pro mini (5V,16MHz)
 * Connect a SR
 * 
 * |04 module to it:
 *  SR04// Arduino UNO,NANO
 *      GND      ->        GND
 *          VCC     ->       +5 VOLT                                        
 *             Trig      ->      D8                                              
 *                ECO    ->      D9                                                    
 *   
*  Connect a I2c LCD module to it
 *     module// Arduino NANO,UNO
 *     GND     ->    GND
 *         VCC     ->     +5volt
 *            SDA     ->      A4
 *               SCL    ->       A5                                                                                                      
 *                                                                                                                          Please, like share and subscribe :
 *       https://youtube.com/channel/UCzrmgye4ZI2oZ7VJeAoeaeg
 */                                                                                                                   





#include <Wire.h>

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
#define echoPin 9
#define trigPin 8
int led=12;

long duration, distance;

void setup()

{

  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
   
     lcd.begin(16, 2);
       lcd.setCursor(0, 1);
  lcd.backlight();
 
  lcd.blink_on();
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
  lcd.clear();
  lcd.print("distance :");
  lcd.setCursor(0, 1);  
  lcd.print(disp);
  Serial.println(disp);  
  lcd.print(" cm");
  if(distance<=5){
    digitalWrite(led, HIGH);
    lcd.print("Danger! Stop");
  }
   digitalWrite(led, LOW);
}
