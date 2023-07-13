#include <LiquidCrystal_I2C.h>       
LiquidCrystal_I2C lcd(0x27,16,2);
#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 10);

 
#define DT A0
#define SCK A1
#define sw 9
 
long sample=0;
float val=0;
long count=0;
 
unsigned long readCount(void)
{
unsigned long Count;
unsigned char i;
pinMode(DT, OUTPUT);
digitalWrite(DT,HIGH);
digitalWrite(SCK,LOW);
Count=0;
pinMode(DT, INPUT);
while(digitalRead(DT));
for (i=0;i<24;i++)
{
digitalWrite(SCK,HIGH);
Count=Count<<1;
digitalWrite(SCK,LOW);
if(digitalRead(DT))
Count++;
}
digitalWrite(SCK,HIGH);
Count=Count^0x800000;
digitalWrite(SCK,LOW);
return(Count);
}
 
void setup()
{
pinMode(SCK, OUTPUT);
pinMode(sw, INPUT_PULLUP);
 lcd.init();                       // initialize the lcd
 lcd.init();
 lcd.backlight(); 

lcd.setCursor(3,0);
lcd.print(" Weight ");
lcd.setCursor(1,1);
lcd.print(" Measurement ");
delay(1000);
lcd.clear();
calibrate();
}
 
void loop()
{
count= readCount();
int w=(((count-sample)/val)-2*((count-sample)/val));
lcd.setCursor(0,0);
lcd.print("Measured Weight");
lcd.setCursor(0,1);
lcd.print(w);
lcd.print("g ");
 
if(digitalRead(sw)==0)
{
val=0;
sample=0;
w=0;
count=0;
calibrate();
}
}
 
void calibrate()
{
lcd.clear();
lcd.print("Calibrating...");
lcd.setCursor(0,1);
lcd.print("Please Wait...");
for(int i=0;i<100;i++)
{
count=readCount();
sample+=count;
}
sample/=100;
lcd.clear();
lcd.print("Put 100g & wait");
count=0;
while(count<1000)
{
count=readCount();
count=sample-count;
}
lcd.clear();
lcd.print("Please Wait....");
delay(1000);
for(int i=0;i<100;i++)
{
count=readCount();
val+=sample-count;
}
val=val/100.0;
val=val/100.0; // put here your calibrating weight
lcd.clear();
}
  
   

void SendTextMessage()
{
  mySerial.println("AT+CMGF=1");    //To send SMS in Text Mode
  delay(1000);
  mySerial.println("AT+CMGS=\"+919380276073\"\r");  // change to the phone number you using
  delay(1000);
  mySerial.println("Gas Leaking!");//the content of the message
  delay(200);
  mySerial.println((char)26);//the stopping character
  delay(1000);
  
}
