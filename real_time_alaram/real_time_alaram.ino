#include <DS3231.h>//Memanggil RTC3231 Library
#include <Wire.h>  // i2C Conection Library
#include <LiquidCrystal_I2C.h> //Libraries
#include <EEPROM.h>
#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "ZoOP7zbXLHurHC0712Se1jG10YtNUqLy";
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Naveen";
char pass[] = "naveen1234";
// Hardware Serial on Mega, Leonardo, Micro...
//#define EspSerial Serial1
// or Software Serial on Uno, Nano...
//#include <SoftwareSerial.h>
//SoftwareSerial EspSerial(2, 3); // RX, TX
// Your ESP8266 baud rate:
#define ESP8266_BAUD 9600
ESP8266 wifi(&Serial);


LiquidCrystal_I2C lcd(0x27, 16, 2); //Arduino pins to lcd

#define bt_time   A0
#define bt_up     A1
#define bt_down   A2
#define bt_alarm  A3

#define buzzer 8
#define led1 9
#define led2 10
#define led3 11

// Init DS3231
DS3231  rtc(SDA, SCL);

// Init a Time-data structure
Time  t; //pencacah string time()

int hh = 0, mm = 0, ss = 0, dd = 0, bb = 0, set_day;
int yy = 0;
String Day = "  ";

int AlarmHH  = 21, AlarmMM  = 22, AlarmSS  = 23, setMode = 0, setAlarm = 0, alarmMode=0;

int stop =0, mode=0, flag=0;

//Eeprom Store Variable
uint8_t HH;
uint8_t MM;

 byte bell_symbol[8] = {
        B00100,
        B01110,
        B01110,
        B01110,
        B01110,
        B11111,
        B01000,
        B00100};
byte thermometer_symbol[8] = {
        B00100,
        B01010,
        B01010,
        B01110,
        B01110,
        B11111,
        B11111,
        B01110};


void setup(){
  
  Serial.begin(9600);

  rtc.begin(); // memulai koneksi i2c dengan RTC

 pinMode(bt_time,  INPUT_PULLUP);
 pinMode(bt_up,    INPUT_PULLUP);
 pinMode(bt_down,  INPUT_PULLUP);
 pinMode(bt_alarm, INPUT_PULLUP);

 pinMode(buzzer, OUTPUT);
 pinMode(led1, OUTPUT);
 pinMode(led2, OUTPUT);
 pinMode(led3, OUTPUT);
 lcd.setCursor(0, 0);
 
  lcd.backlight();
  lcd.blink_on();
  lcd.createChar(1, thermometer_symbol);
  lcd.createChar(2, bell_symbol);
  
  lcd.begin(16, 2); // Configura lcd numero columnas y filas
  lcd.setCursor(0,0);  //Show "TIME" on the LCD

  lcd.setCursor (0,0);
  lcd.print(" Medicine Remainder ");
  lcd.setCursor (0,1);
  lcd.print("   With Alarm ");
  delay (2000);
  lcd.clear();

stop=EEPROM.read(50);
if(stop==0){  
}else{WriteEeprom ();}

EEPROM.write(50,0); 

ReadEeprom();

  delay(10);
 // Set ESP8266 baud rate
// Serial.begin(ESP8266_BAUD);
 //delay(10);
 //Blynk.begin(auth, wifi, ssid, pass);
// Setup Serial connection
//Set RTC Untuk Pertama kali
//rtc.setDOW(2);     // Set Day-of-Week to SUNDAY
//rtc.setTime (00, 9, 50); 
//rtc.setDate(12, 11, 2017);  
}

void loop(){  
  
t = rtc.getTime();
Day = rtc.getDOWStr(1);

if (setMode == 0){
hh = t.hour,DEC;
mm = t.min,DEC;
ss = t.sec,DEC;
dd = t.date,DEC;
bb = t.mon,DEC;
yy = t.year,DEC;
}  

  if(setAlarm==0){
  lcd.setCursor(0,0); 
  lcd.print((hh/10)%10);
  lcd.print(hh % 10); 
  lcd.print(":");
  lcd.print((mm/10)%10);
  lcd.print(mm % 10);
  lcd.print(":");
  lcd.print((ss/10)%10);
  lcd.print(ss % 10);
  lcd.print(" ");  
  if(mode==1){lcd.write(2);}
  else{lcd.print(" ");}   
  lcd.print(" "); 
  lcd.write(1); 
  lcd.print(rtc.getTemp(),0);
  lcd.write(223); 
  lcd.print("C");
  lcd.print("  "); 

  lcd.setCursor(1,1);
  lcd.print(Day);
  lcd.print(" ");
  lcd.print((dd/10)%10);
  lcd.print(dd % 10); 
  lcd.print("/");
  lcd.print((bb/10)%10);
  lcd.print(bb % 10);
  lcd.print("/"); 
  lcd.print((yy/1000)%10);
  lcd.print((yy/100)%10);
  lcd.print((yy/10)%10);
  lcd.print(yy % 10);
  }


setupClock();
setTimer();
delay (100);
blinking();

//Alarm
if (alarmMode==1 && mode==1 && hh==AlarmHH && mm==AlarmMM && ss>=AlarmSS) {
  lcd.clear();
  lcd.print("Tablet");
  Blynk.notify("Take Tablet");
digitalWrite(buzzer, HIGH);
digitalWrite(led1, HIGH);
delay (300);
digitalWrite(led1, LOW);
digitalWrite(buzzer, LOW);
}else{digitalWrite(buzzer, LOW);digitalWrite(led1, LOW);}


if (alarmMode==1 && mode==1 && hh==12 && mm==27 && ss>=20) {
  lcd.clear();
  lcd.print("Tablet 1");
 // Blynk.notify("Take Tablet 1");
digitalWrite(buzzer, HIGH);
digitalWrite(led2, HIGH);
delay (300);
digitalWrite(buzzer, LOW);
digitalWrite(led2, LOW);
}else{digitalWrite(buzzer, LOW);digitalWrite(led1, LOW);}

if (alarmMode==1 && mode==1 && hh==12 && mm==28 && ss>=30) {
  lcd.clear();
  lcd.print("Take Tablet 2");
 // Blynk.notify("Take Tablet 2");
digitalWrite(buzzer, HIGH);
digitalWrite(led3, HIGH);
delay (300);
digitalWrite(buzzer, LOW);
digitalWrite(led3, LOW);
}else{digitalWrite(buzzer, LOW);digitalWrite(led3, LOW);}

delay (100);

// Blynk.run();
}

void blinking (){
//BLINKING SCREEN
if (setAlarm <2 && setMode == 1){lcd.setCursor(0,0);  lcd.print("  ");}
if (setAlarm <2 && setMode == 2){lcd.setCursor(3,0);  lcd.print("  ");}
if (setAlarm <2 && setMode == 3){lcd.setCursor(6,0);  lcd.print("  ");}
if (setAlarm <2 && setMode == 4){lcd.setCursor(1,1);  lcd.print("   ");}
if (setAlarm <2 && setMode == 5){lcd.setCursor(5,1);  lcd.print("  ");}
if (setAlarm <2 && setMode == 6){lcd.setCursor(8,1);  lcd.print("  ");}
if (setAlarm <2 && setMode == 7){lcd.setCursor(11,1); lcd.print("    "); }
//Alarm
if (setMode == 0 && setAlarm == 1){lcd.setCursor(6,0); lcd.print("      "); }
if (setMode == 0 && setAlarm == 2){lcd.setCursor(4,1); lcd.print("  "); }
if (setMode == 0 && setAlarm == 3){lcd.setCursor(7,1); lcd.print("  "); }
if (setMode == 0 && setAlarm == 4){lcd.setCursor(10,1);lcd.print("  "); }
}

//Seting Jam ,Tanggal,Alarm/Timer
void setupClock (void) {
   
    if (setMode == 8){
    lcd.setCursor (0,0);
    lcd.print (F("Set Date Finish "));
    lcd.setCursor (0,1);
    lcd.print (F("Set Time Finish "));
    delay (1000);
    rtc.setTime (hh, mm, ss);
    rtc.setDate (dd, bb, yy);  
    lcd.clear();
    setMode = 0;
    }

    if (setAlarm == 5){
    lcd.setCursor (0,0);
    lcd.print (F("Set Alarm Finish"));
    lcd.setCursor (0,1);
    lcd.print (F("-EEPROM Updated-"));
    WriteEeprom();
    delay (2000); 
    lcd.clear();
    setAlarm=0;
    alarmMode=1;
    }
    
 if (setAlarm >0){ alarmMode=0;}
    
 if(digitalRead (bt_time) == 0 && flag==0) {flag=1;
 if(setAlarm>0){setAlarm=5;}
 else{setMode = setMode+1;}
 }
  
 if(digitalRead (bt_alarm) == 0 && flag==0){flag=1;
 if(setMode>0){setMode=8;}
  else{setAlarm = setAlarm+1;} 
  lcd.clear();} 

if(digitalRead (bt_time) == 1 && digitalRead (bt_alarm) == 1){flag=0;}
  
 if(digitalRead (bt_up) == 0){                          
            if (setAlarm<2 && setMode==1)hh=hh+1; 
            if (setAlarm<2 && setMode==2)mm=mm+1;
            if (setAlarm<2 && setMode==3)ss=ss+1;
            if (setAlarm<2 && setMode==4)set_day=set_day+1;
            if (setAlarm<2 && setMode==5)dd=dd+1;
            if (setAlarm<2 && setMode==6)bb=bb+1;
            if (setAlarm<2 && setMode==7)yy=yy+1;
            //Alarm
            if (setMode==0 && setAlarm==1)mode=1;
            if (setMode==0 && setAlarm==2 && AlarmHH<23)AlarmHH=AlarmHH+1;
            if (setMode==0 && setAlarm==3 && AlarmMM<59)AlarmMM=AlarmMM+1;
            if (setMode==0 && setAlarm==4 && AlarmSS<59)AlarmSS=AlarmSS+1;

if(hh>23)hh=0;
if(mm>59)mm=0;
if(ss>59)ss=0;
if(set_day>7)set_day=0;
if(dd>31)dd=0;
if(bb>12)bb=0;
if(yy>2030)yy=2000;
rtc.setDOW(set_day);
 }        

if(digitalRead (bt_down) == 0){                                      
            if (setAlarm<2 && setMode==1)hh=hh-1; 
            if (setAlarm<2 && setMode==2)mm=mm-1;
            if (setAlarm<2 && setMode==3)ss=ss-1;
            if (setAlarm<2 && setMode==4)set_day=set_day-1;
            if (setAlarm<2 && setMode==5)dd=dd-1;
            if (setAlarm<2 && setMode==6)bb=bb-1;
            if (setAlarm<2 && setMode==7)yy=yy-1;
            //Alarm
            if (setMode==0 && setAlarm==1 )mode=0;
            if (setMode==0 && setAlarm==2 && AlarmHH>0)AlarmHH=AlarmHH-1;
            if (setMode==0 && setAlarm==3 && AlarmMM>0)AlarmMM=AlarmMM-1;
            if (setMode==0 && setAlarm==4 && AlarmSS>0)AlarmSS=AlarmSS-1;
if(hh<0)hh=23;
if(mm<0)mm=59;
if(ss<0)ss=59;
if(set_day<0)set_day=7;
if(dd<0)dd=31;
if(bb<0)bb=12;
if(yy<0)yy=2030;
rtc.setDOW(set_day);
 }
 
}

void setTimer (){
  //Alarm
 if (setMode == 0 && setAlarm >0){
  lcd.setCursor (0,0);
  lcd.print("Alarm ");
 if(mode==0){lcd.print("Deactivate");}
        else{lcd.print("Activated ");}
        
  lcd.setCursor (4,1);
  lcd.print((AlarmHH/10)%10);
  lcd.print(AlarmHH % 10);
  lcd.print(":");
  lcd.print((AlarmMM/10)%10);
  lcd.print(AlarmMM % 10);
  lcd.print(":");
  lcd.print((AlarmSS/10)%10);
  lcd.print(AlarmSS % 10);
 }

}

void ReadEeprom () {
  AlarmHH=EEPROM.read(1);
  AlarmMM=EEPROM.read(2);
  AlarmSS=EEPROM.read(3);
  
  mode=EEPROM.read(4); 
}

void WriteEeprom () {
  EEPROM.write(1,AlarmHH);
  EEPROM.write(2,AlarmMM);
  EEPROM.write(3,AlarmSS);
  
  EEPROM.write(4,mode);
}



//#include <Wire.h>
//#include<EEPROM.h>
//#include <RTClib.h>
//#include <LiquidCrystal_I2C.h>
//
//LiquidCrystal_I2C lcd(0x27, 16, 2);
//RTC_DS1307 RTC;
//int temp, inc, hours1, minut, add = 11;
//
//int next = 10;
//int INC = 11;
//int set_mad = 12;
//
//#define buzzer 13
//
//int HOUR, MINUT, SECOND;
//
//
//void setup()
//{
//  Wire.begin();
//  RTC.begin();
//  lcd.begin(16, 2);
//  pinMode(INC, INPUT);
//  pinMode(next, INPUT);
//  pinMode(set_mad, INPUT);
//  pinMode(buzzer, OUTPUT);
//  digitalWrite(next, HIGH);
//  digitalWrite(set_mad, HIGH);
//  digitalWrite(INC, HIGH);
//  digitalWrite(buzzer, LOW);
//  lcd.setCursor(0, 0);
//  lcd.print("VTU PG CENTER MYSURU");
//  lcd.setCursor(0, 1);
//  lcd.print("       MCA");
//  lcd.backlight();
//  lcd.blink_on();
//  delay(2000);
//
//  if (!RTC.isrunning())
//  {
//    RTC.adjust(DateTime(__DATE__, __TIME__));
//  }
//}
//
//void loop()
//{
//  int temp = 0, val = 1, temp4;
//  DateTime now = RTC.now();
//  if (digitalRead(set_mad) == 0)
//  {
//    lcd.setCursor(0, 0);
//    lcd.print("  Set Alarm  ");
//    delay(2000);
//    defualt();
//    time();
//    delay(1000);
//    lcd.clear();
//    lcd.setCursor(0, 0);
//    lcd.print("  Alarm time ");
//    lcd.setCursor(0, 1);
//    lcd.print(" has been set  ");
//    delay(2000);
//  }
//  lcd.clear();
//  lcd.setCursor(0, 0);
//  lcd.print("Time:");
//  lcd.setCursor(6, 0);
//  lcd.print(HOUR = now.hour(), DEC);
//  lcd.print(":");
//  lcd.print(MINUT = now.minute(), DEC);
//  lcd.print(":");
//  lcd.print(SECOND = now.second(), DEC);
//  lcd.setCursor(0, 1);
//  lcd.print("Date: ");
//  lcd.print(now.day(), DEC);
//  lcd.print("/");
//  lcd.print(now.month(), DEC);
//  lcd.print("/");
//  lcd.print(now.year(), DEC);
//  match();
//  delay(200);
//}
//
//void defualt()
//{
//  lcd.setCursor(0, 1);
//  lcd.print(HOUR);
//  lcd.print(":");
//  lcd.print(MINUT);
//  lcd.print(":");
//  lcd.print(SECOND);
//}
//
//void time()
//{
//  int temp = 1, minuts = 0, hours = 0, seconds = 0;
//  while (temp == 1)
//  {
//    if (digitalRead(INC) == 0)
//    {
//      HOUR++;
//      if (HOUR == 24)
//      {
//        HOUR = 0;
//      }
//      while (digitalRead(INC) == 0);
//    }
//    lcd.clear();
//    lcd.setCursor(0, 0);
//    lcd.print("Set Alarm Time ");
//    //lcd.print(x);
//    lcd.setCursor(0, 1);
//    lcd.print(HOUR);
//    lcd.print(":");
//    lcd.print(MINUT);
//    lcd.print(":");
//    lcd.print(SECOND);
//    delay(100);
//    if (digitalRead(next) == 0)
//    {
//      hours1 = HOUR;
//      EEPROM.write(add++, hours1);
//      temp = 2;
//      while (digitalRead(next) == 0);
//    }
//  }
//
//  while (temp == 2)
//  {
//    if (digitalRead(INC) == 0)
//    {
//      MINUT++;
//      if (MINUT == 60)
//      {
//        MINUT = 0;
//      }
//      while (digitalRead(INC) == 0);
//    }
//    // lcd.clear();
//    lcd.setCursor(0, 1);
//    lcd.print(HOUR);
//    lcd.print(":");
//    lcd.print(MINUT);
//    lcd.print(":");
//    lcd.print(SECOND);
//    delay(100);
//    if (digitalRead(next) == 0)
//    {
//      minut = MINUT;
//      EEPROM.write(add++, minut);
//      temp = 0;
//      while (digitalRead(next) == 0);
//    }
//  }
//  delay(1000);
//}
//
//void match()
//{
//  int tem[17];
//  for (int i = 11; i < 17; i++)
//  {
//    tem[i] = EEPROM.read(i);
//  }
//  if (HOUR == tem[11] && MINUT == tem[12])
//  {
//    beep();
//    beep();
//    beep();
//    beep();
//    lcd.clear();
//    lcd.print("Wake Up....");
//    lcd.setCursor(0, 1);
//    lcd.print("Wake Up....");
//    beep();
//    beep();
//    beep();
//    beep();
//  }
//
//}
//void beep()
//{
//  digitalWrite(buzzer, HIGH);
//  delay(500);
//  digitalWrite(buzzer, LOW);
//  delay(500);
//}
