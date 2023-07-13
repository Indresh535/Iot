
#define in1 9
#define in2 8
#define in3 7
#define in4 6
#define enA 10
#define enB 5

#define MQ2pin (A3)
#define MQ3pin (A4)



 int M1_Speed = 80; // speed of motor 1
 int M2_Speed = 80; // speed of motor 2
 int LeftRotationSpeed = 255;  // Left Rotation Speed
 int RightRotationSpeed = 255; // Right Rotation Speed

 
// const int D0 = 0;       //Raspberry pin 21    LSB
//const int D1 = 1;       //Raspberry pin 22
//const int D2 = 2;       //Raspberry pin 23
//const int D3 = 3;       //Raspberry pin 24    MSB

//#define D0 0
//#define D1 1
//#define D2 2
//#define D3 3

#define MQ3Fan 4

int a,b,c,d,data;
char value;
int L = 0;
int R = 0;
int L1 = 0;
int R1 = 0;


 void setup() {
  Serial.begin(9600);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(MQ3Fan,OUTPUT);

    pinMode(enA,OUTPUT);
    pinMode(enB,OUTPUT);



//pinMode(D0, INPUT_PULLUP);
//pinMode(D1, INPUT_PULLUP);
//pinMode(D2, INPUT_PULLUP);
//pinMode(D3, INPUT_PULLUP);


      pinMode(A0, INPUT); // initialize Left sensor as an input
      pinMode(A1, INPUT); // initialize Right sensor as an input

       pinMode(MQ2pin, INPUT);
       pinMode(MQ3pin, INPUT);

}





void loop() {
  
  int LEFT_SENSOR = digitalRead(A0);
  int RIGHT_SENSOR = digitalRead(A1);
//
//  
//Serial.println("IR Sensor");
//  Serial.println(LEFT_SENSOR);
//  Serial.println(RIGHT_SENSOR);
//  


 float MQ2Value = analogRead(MQ2pin);
  Serial.println(" MQ-2 Sensor Value: ");
  Serial.print(MQ2Value);
  
if (MQ2Value>200.0){
  Stop();
 }

 float MQ3Value = analogRead(MQ3pin);
 Serial.println(" MQ-3 Sensor Value: ");
 Serial.print(MQ3Value);
  if (MQ3Value>200.0){
  Stop();
  digitalWrite(MQ3Fan, HIGH);
 }else{
  digitalWrite(MQ3Fan, LOW);  
 }
     
if(RIGHT_SENSOR==1 && LEFT_SENSOR==1) {
    forward(); //FORWARD
}

  else if(RIGHT_SENSOR==0 && LEFT_SENSOR==1) {
     left();  //Move Left
 }

  else if(RIGHT_SENSOR==1 && LEFT_SENSOR==0) {
      right();   //Move Right
    
}

  else if(RIGHT_SENSOR==0 && LEFT_SENSOR==0) {
    Stop();  //STOP
 }

Bluetoothcontrol();
}




void forward()
{
            digitalWrite(in1, LOW);
            digitalWrite(in2, HIGH);
            digitalWrite(in3, HIGH);
            digitalWrite(in4, LOW);

                analogWrite(enA, 225);
                analogWrite(enB, 225);
}

void backward()
{
            digitalWrite(in1, LOW);
            digitalWrite(in2, HIGH);
            digitalWrite(in3, LOW);
            digitalWrite(in4, HIGH);

                analogWrite(enA, M1_Speed);
                analogWrite(enB, M2_Speed);
}

void right()
{
            digitalWrite(in1, LOW);
            digitalWrite(in2, HIGH);
            analogWrite(enA, 255);
            
            digitalWrite(in3, LOW);
            digitalWrite(in4, HIGH);                
            analogWrite(enB, 50);
}

void left()
{
            digitalWrite(in1, HIGH);
            digitalWrite(in2, LOW);
            analogWrite(enA, 50);
            
            digitalWrite(in3, HIGH);
            digitalWrite(in4, LOW);                
            analogWrite(enB, 255);
}

void Stop()
{
            digitalWrite(in1, LOW);
            digitalWrite(in2, LOW);
            digitalWrite(in3, LOW);
            digitalWrite(in4, LOW);
            analogWrite(enA, 0);
            analogWrite(enA, 0);
}
 
 
void Bluetoothcontrol() {
  if (Serial.available() > 0) {
 char value = Serial.read();
 Serial.println("BlueTooth control");
    Serial.println(value);
  
  if (value == 'U') {
    forward();
  } else if (value == 'D') {
    backward();
  } else if (value == 'L') {
    left();
  } else if (value == 'R') {
    right();
  } else if (value == 'S') {
    Stop();
  }
} 
}


void voicecontrol() {
  if (Serial.available() > 0) {
char value = Serial.read();
Serial.println("Voice control");
    Serial.print(value);
    if (value == '^') {
      forward();
    } else if (value == '-') {
      backward();
    } else if (value == '<') {
      if (L >= 10 ) {
        left();
        delay(500);
        Stop();
      } else if (L < 10) {
        Stop();
      }
    } else if (value == '>') {
      if (R >= 10 ) {
        right();
        delay(500);
        Stop();
      } else if (R < 10) {
        Stop();
      }
    } else if (value == '*') {
      Stop();
    }
  }
}


 //************************************************************************************************************  Raspberry Car
 /*
Code Name: Arduino Line Follower Robot Car
Code URI: https://circuitbest.com/category/arduino-projects/
Author: Make DIY
Author URI: https://circuitbest.com/author/admin/
Description: This program is used to make Arduino Line Follower Robot Car.
Note: You can use any value between 0 to 255 for M1_Speed, M2_Speed, LeftRotationSpeed, RightRotationSpeed.
Here 0 means Low Speed and 255 is for High Speed.
Version: 1.0
License: Remixing or Changing this Thing is allowed. Commercial use is not allowed.
*/

//#define in1 9
//#define in2 8
//#define in3 7
//#define in4 6
//#define enA 10
//#define enB 5
//
//#define MQ2pin (A3)
//#define MQ3pin (A4)
//
//
//
// int M1_Speed = 80; // speed of motor 1
// int M2_Speed = 80; // speed of motor 2
// int LeftRotationSpeed = 255;  // Left Rotation Speed
// int RightRotationSpeed = 255; // Right Rotation Speed
//
// 
//// const int D0 = 0;       //Raspberry pin 21    LSB
////const int D1 = 1;       //Raspberry pin 22
////const int D2 = 2;       //Raspberry pin 23
////const int D3 = 3;       //Raspberry pin 24    MSB
//
//#define D0 0
//#define D1 1
//#define D2 2
//#define D3 3
//
//int a,b,c,d,data;
//char value;
//int L = 0;
//int R = 0;
//int L1 = 0;
//int R1 = 0;
//
//
// void setup() {
//  Serial.begin(9600);
//  pinMode(in1,OUTPUT);
//  pinMode(in2,OUTPUT);
//  pinMode(in3,OUTPUT);
//  pinMode(in4,OUTPUT);
//
//    pinMode(enA,OUTPUT);
//    pinMode(enB,OUTPUT);
//
//
//
//pinMode(D0, INPUT_PULLUP);
//pinMode(D1, INPUT_PULLUP);
//pinMode(D2, INPUT_PULLUP);
//pinMode(D3, INPUT_PULLUP);
//
//
//      pinMode(A0, INPUT); // initialize Left sensor as an input
//      pinMode(A1, INPUT); // initialize Right sensor as an input
//
//       pinMode(MQ2pin, INPUT);
//       pinMode(MQ3pin, INPUT);
//
//}
//
//
//
//
//
//void Data()
//{
//   a = digitalRead(D0);
//   b = digitalRead(D1);
//   c = digitalRead(D2);
//   d = digitalRead(D3);
//
//   data = 8*d+4*c+2*b+a;
//}
//
//
//void loop() {
//
//  int LEFT_SENSOR = digitalRead(A0);
//  int RIGHT_SENSOR = digitalRead(A1);
//  int a = digitalRead(D0);
//   int b = digitalRead(D1);
//   int c = digitalRead(D2);
//   int d = digitalRead(D3);
//   data = 8*d+4*c+2*b+a;
//  
//Serial.println("IR Sensor");
//  Serial.println(LEFT_SENSOR);
//  Serial.println(RIGHT_SENSOR);
//  
// float MQ2Value = analogRead(MQ2pin);
//  Serial.println("MQ-2 Sensor Value: ");
//  Serial.print(MQ2Value);
//  
//  if (MQ2Value>200.0){
//   Stop();
//  }
//
//  float MQ3Value = analogRead(MQ3pin);
//  Serial.println("MQ-3 Sensor Value: ");
//  Serial.print(MQ3Value);
//  
//    if (MQ3Value>250.0){
//   Stop();
//  }
//      
//    
//
// 
//if(RIGHT_SENSOR==1 && LEFT_SENSOR==1) {
//    forward(); //FORWARD
//}
//
//  else if(RIGHT_SENSOR==0 && LEFT_SENSOR==1) {
//     left();  //Move Left
// }
//
//  else if(RIGHT_SENSOR==1 && LEFT_SENSOR==0) {
//      right();   //Move Right
//    
//}
//
//  else if(RIGHT_SENSOR==0 && LEFT_SENSOR==0) {
//    Stop();  //STOP
// }
//
//
//Serial.println("Raspberry Pi");
//Serial.print(a);
// Serial.print(b);
//  Serial.print(c);
//  Serial.println(d);
//   Serial.print("Data: ");
//   Serial.println(data);
//  if(data==11)
//   {
//    Serial.println("Traffic Light");
//     Stop();
//   }
//  else if (data==9)
//   {
//    Serial.println("Stop Sign");
//    Stop();
////      analogWrite(EnableL, 0);
////     ` analogWrite(EnableR, 0);
//      delay(4000);                      // stop sign detection
//    forward();
////      analogWrite(EnableL, 150);
////      analogWrite(EnableR, 150);
//      delay(1000);
//   }
// 
//  }
//
//
//
//
//void forward()
//{
//            digitalWrite(in1, LOW);
//            digitalWrite(in2, HIGH);
//            digitalWrite(in3, HIGH);
//            digitalWrite(in4, LOW);
//
//                analogWrite(enA, 180);
//                analogWrite(enB, 180);
//}
//
//void backward()
//{
//            digitalWrite(in1, LOW);
//            digitalWrite(in2, HIGH);
//            digitalWrite(in3, LOW);
//            digitalWrite(in4, HIGH);
//
//                analogWrite(enA, M1_Speed);
//                analogWrite(enB, M2_Speed);
//}
//
//void right()
//{
//            digitalWrite(in1, LOW);
//            digitalWrite(in2, HIGH);
//            analogWrite(enA, 255);
//            
//            digitalWrite(in3, LOW);
//            digitalWrite(in4, HIGH);                
//            analogWrite(enB, 50);
//}
//
//void left()
//{
//            digitalWrite(in1, HIGH);
//            digitalWrite(in2, LOW);
//            analogWrite(enA, 50);
//            
//            digitalWrite(in3, HIGH);
//            digitalWrite(in4, LOW);                
//            analogWrite(enB, 255);
//}
//
//void Stop()
//{
//            digitalWrite(in1, LOW);
//            digitalWrite(in2, LOW);
//            digitalWrite(in3, LOW);
//            digitalWrite(in4, LOW);
//            analogWrite(enA, 0);
//            analogWrite(enA, 0);
//}
// 
// 
//void Bluetoothcontrol() {
//  if (Serial.available() > 0) {
// char value = Serial.read();
// Serial.println("BlueTooth control");
//    Serial.println(value);
//  
//  if (value == 'U') {
//    forward();
//  } else if (value == 'D') {
//    backward();
//  } else if (value == 'L') {
//    left();
//  } else if (value == 'R') {
//    right();
//  } else if (value == 'S') {
//    Stop();
//  }
//} 
//}
//
//
//void voicecontrol() {
//  if (Serial.available() > 0) {
//char value = Serial.read();
//Serial.println("Voice control");
//    Serial.print(value);
//    if (value == '^') {
//      forward();
//    } else if (value == '-') {
//      backward();
//    } else if (value == '<') {
//      if (L >= 10 ) {
//        left();
//        delay(500);
//        Stop();
//      } else if (L < 10) {
//        Stop();
//      }
//    } else if (value == '>') {
//      if (R >= 10 ) {
//        right();
//        delay(500);
//        Stop();
//      } else if (R < 10) {
//        Stop();
//      }
//    } else if (value == '*') {
//      Stop();
//    }
//  }
//}
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 /* Forbiddenbit.com
 */



//
// const int EnableL = 5;
// const int HighL = 6;       // LEFT SIDE MOTOR
// const int LowL =7;
// 
// const int HighR = 8; 
// const int LowR =9;
// const int EnableR = 10;
// 
// int valuePWM1=120; // speed motor 1 
// int valuePWM2=150; // speed motor 2
// 
//void setup() {
//  Serial.begin(9600);
//  
//  pinMode(EnableL, OUTPUT);      
//  pinMode(HighL, OUTPUT);
//  pinMode(LowL, OUTPUT);
//
//  pinMode(EnableR, OUTPUT);
//  pinMode(HighR, OUTPUT);
//  pinMode(LowR, OUTPUT);
// 
//pinMode(A0, INPUT); // initialize Right sensor as an inut
//pinMode(A1, INPUT); // initialize Left sensor as as input
// 
//}
// 
//void loop() {
// 
//  int LEFT_SENSOR = analogRead(A0);
//  int RIGHT_SENSOR = analogRead(A1);
//  
//  Serial.println("right:");
//  Serial.println(RIGHT_SENSOR);
//  Serial.println("left:");
//  Serial.println(LEFT_SENSOR);
//  
//  delay(300);  
//  
//if(RIGHT_SENSOR<36 && LEFT_SENSOR<36) //FORWARD
//{
//            digitalWrite(HighL, LOW);
//            digitalWrite(LowL, HIGH);
//            digitalWrite(HighR, HIGH);
//            digitalWrite(LowR, LOW);
//            analogWrite(EnableL, valuePWM1);
//            analogWrite(EnableR, valuePWM1);
//}
// 
// else if(RIGHT_SENSOR>36 && LEFT_SENSOR<36) //LEFT
// {
//  
//            digitalWrite(HighL, LOW);
//            digitalWrite(LowL, HIGH);
//            digitalWrite(HighR, HIGH);
//            digitalWrite(LowR, LOW);
//            analogWrite(EnableL, valuePWM2);
//            analogWrite(EnableR, valuePWM2);
//}
// 
//else if(RIGHT_SENSOR<36 && LEFT_SENSOR>35) //RIGHT
// {
//  
//              digitalWrite(HighL, LOW);
//              digitalWrite(LowL, HIGH);            
//              digitalWrite(HighR, HIGH);
//              digitalWrite(LowR, LOW);
//              analogWrite(EnableL, valuePWM2);
//              analogWrite(EnableR, valuePWM2);
//}
// 
//else if(RIGHT_SENSOR>35 && LEFT_SENSOR>35) //BACK
//{
//  
//              digitalWrite(HighL, LOW);
//              digitalWrite(LowL, LOW);
//            
//              digitalWrite(HighR, LOW);
//              digitalWrite(LowR, LOW);
// }
//}















// ***********************************************************************************************
///*
// * Forbiddenbit.com
// */
// 
//void setup() {
//  Serial.begin(9600);
// 
//  pinMode(A0, INPUT); // initialize Right sensor as an inut
//  pinMode(A1, INPUT); // initialize Left sensor as as input
// 
//}
// 
//void loop() {
// 
//  int LEFT_SENSOR = analogRead(A0);
//  int RIGHT_SENSOR = analogRead(A1);
// 
//  Serial.println("right:");
//  Serial.println(RIGHT_SENSOR);
//  Serial.println("left:");
//  Serial.println(LEFT_SENSOR);
//  
//  delay(300);  
//}






//---------------------------------------------------------------------------------------------------------------------------------------------------------------

//uint32_t interval = 1000;
//    
//const int EnableL = 5;
//const int HighL = 6;       // LEFT SIDE MOTOR
//const int LowL =7;
//
//const int EnableR = 10;
//const int HighR = 8;       //RIGHT SIDE MOTOR
//const int LowR =9;
//
//const int D0 = 0;       //Raspberry pin 21    LSB
//const int D1 = 1;       //Raspberry pin 22
//const int D2 = 2;       //Raspberry pin 23
//const int D3 = 3;       //Raspberry pin 24    MSB
//
//int a,b,c,d,data;
//
//
//void setup() {
//
//  Serial.begin(9600);
//pinMode(EnableL, OUTPUT);      
//pinMode(HighL, OUTPUT);
//pinMode(LowL, OUTPUT);
//
//
//pinMode(EnableR, OUTPUT);
//pinMode(HighR, OUTPUT);
//pinMode(LowR, OUTPUT);
//
//
//pinMode(D0, INPUT_PULLUP);
//pinMode(D1, INPUT_PULLUP);
//pinMode(D2, INPUT_PULLUP);
//pinMode(D3, INPUT_PULLUP);
//
//
//
//  digitalWrite(HighL, LOW);
//  digitalWrite(LowL, HIGH);
//  analogWrite(EnableL,0);
//
//  digitalWrite(HighR, LOW);
//  digitalWrite(LowR, HIGH);
//  analogWrite(EnableR,0);
//
//  
//}
//
//void Data()
//{
//   a = digitalRead(D0);
//   b = digitalRead(D1);
//   c = digitalRead(D2);
//   d = digitalRead(D3);
//
//   data = 8*d+4*c+2*b+a;
//}
//
//void Forward()
//{
//  delay(800);
//  digitalWrite(HighL, LOW);
//  digitalWrite(LowL, HIGH);
//  analogWrite(EnableL,100);
//
//  digitalWrite(HighR, HIGH);
//  digitalWrite(LowR, LOW);
//  analogWrite(EnableR,100);
//  delay(200);
//}
//
//
//void Backward()
//{
//  digitalWrite(HighL, HIGH);
//  digitalWrite(LowL, LOW);
//  analogWrite(EnableL,255);
//
//  digitalWrite(HighR, LOW);
//  digitalWrite(LowR, HIGH);
//  analogWrite(EnableR,255);
//  
//}
//
//void Stop()
//{
//  digitalWrite(HighL, LOW);
//  digitalWrite(LowL, HIGH);
//  analogWrite(EnableL,0);
//
//  digitalWrite(HighR, LOW);
//  digitalWrite(LowR, HIGH);
//  analogWrite(EnableR,0);
//  
//}
//
//void Left1()
//{
//  digitalWrite(HighL, LOW);
//  digitalWrite(LowL, HIGH);
//  analogWrite(EnableL,160);
//
//  digitalWrite(HighR, HIGH);
//  digitalWrite(LowR, LOW);
//  analogWrite(EnableR,220);
//  delay(100);
//}
//
//void Left2()
//{
//  digitalWrite(HighL, LOW);
//  digitalWrite(LowL, HIGH);
//  analogWrite(EnableL,120);
//
//  digitalWrite(HighR, HIGH);
//  digitalWrite(LowR, LOW);
//  analogWrite(EnableR,200);
//  delay(100);
//  
//}
//
//
//void Left3()
//{
//  digitalWrite(HighL, LOW);
//  digitalWrite(LowL, HIGH);
//  analogWrite(EnableL,50);
//
//  digitalWrite(HighR, HIGH);
//  digitalWrite(LowR, LOW);
//  analogWrite(EnableR,250);
//  delay(100);
//  
//}
//
//void Right1()
//{
//  digitalWrite(HighL, LOW);
//  digitalWrite(LowL, HIGH);
//  analogWrite(EnableL,220);
//
//  digitalWrite(HighR, HIGH);
//  digitalWrite(LowR, LOW);
//  analogWrite(EnableR,160); 
//  delay(100); 
//  
//}
//void Right2()
//{
//  digitalWrite(HighL, LOW);
//  digitalWrite(LowL, HIGH);
//  analogWrite(EnableL,200);
//
//  digitalWrite(HighR, HIGH);
//  digitalWrite(LowR, LOW);
//  analogWrite(EnableR,120); 
//  delay(100);  
//  
//}
//
//void Right3()
//{
//  digitalWrite(HighL, LOW);
//  digitalWrite(LowL, HIGH);
//  analogWrite(EnableL,250);
//
//  digitalWrite(HighR, HIGH);
//  digitalWrite(LowR, LOW);
//  analogWrite(EnableR,50);
//  delay(100);   
//  
//}
//
//
//
//void UTurn()
//{
//  analogWrite(EnableL, 0);
//  analogWrite(EnableR, 0);
//  delay(400);
//
//  analogWrite(EnableL, 200);
//  analogWrite(EnableR, 200);    //forward
//  delay(1000);
//
//  analogWrite(EnableL, 0);
//  analogWrite(EnableR, 0);
//  delay(400);
//
//  digitalWrite(HighL, LOW);
//  digitalWrite(LowL, HIGH);
//  digitalWrite(HighR, HIGH);    //   left
//  digitalWrite(LowR, LOW);
//  analogWrite(EnableL, 200);
//  analogWrite(EnableR, 200);
//  delay(700);
//
//  analogWrite(EnableL, 0);
//  analogWrite(EnableR, 0);
//  delay(400);
//
//  
//  digitalWrite(HighL, LOW);
//  digitalWrite(LowL, HIGH);
//  digitalWrite(HighR, HIGH);     // forward
//  digitalWrite(LowR, LOW);
//  
//  analogWrite(EnableL, 200);
//  analogWrite(EnableR, 200);
//  delay(900);
//
//  analogWrite(EnableL, 0);
//  analogWrite(EnableR, 0);
//  delay(400);
//
//  digitalWrite(HighL, LOW);
//  digitalWrite(LowL, HIGH);
//  digitalWrite(HighR, HIGH);    //   left
//  digitalWrite(LowR, LOW);
//  analogWrite(EnableL, 200);
//  analogWrite(EnableR, 200);
//  delay(700);
//
//
//  analogWrite(EnableL, 0);
//  analogWrite(EnableR, 0);
//  delay(1000);
//
//
//
//  digitalWrite(HighL, LOW);
//  digitalWrite(LowL, HIGH);
//  digitalWrite(HighR, HIGH);     // forward
//  digitalWrite(LowR, LOW);
//  analogWrite(EnableL, 150);
//  analogWrite(EnableR, 150);
//  delay(300);
//}
//
//
//
//
//void loop() 
//{
//  Serial.print(a);
//  Serial.print(b);
//  Serial.print(c);
//  Serial.print(d);
//  Serial.println(data);
//  Data();
//  if(data==9)
//   {
//     Stop();
//   }
//   
//  else if(data==10)
//   {
//     Forward();
//   }
//     
//  else if(data==2)
//   {
//     Right2();
//   }
//     
//  else if(data==3)
//   {
//     Right2();
//   }
//     
//  else if(data==4)
//   {
//     Left2();
//   }
//    
//  else if(data==5)
//   {
//     Left2();
//   }
//    
//  else if(data==6)
//   {
//     Left2();
//   }
//     else if (data==7)
//   {
//     Stop();
//   }
//    
//  else if (data==8)
//   {
//    Stop();
////      analogWrite(EnableL, 0);
////      analogWrite(EnableR, 0);
//      delay(4000);                      // stop sign detection
//    Forward();
////      analogWrite(EnableL, 150);
////      analogWrite(EnableR, 150);
//      delay(1000);
//   }
//
//     else if(data>8)
//   {
//     Stop();
//   }
//
//// uint32_t period = 5 * 60000L;       // 5 minutes
//
////for( uint32_t tStart = millis();  (millis()-tStart) < 5000L;  ){
////   Forward();
////}
////Stop();
////delay(500);
////for( uint32_t tStart = millis();  (millis()-tStart) < 3000L;  ){   
////   Left3();
////Stop();
////delay(300);
////}
////
////for( uint32_t tStart = millis();  (millis()-tStart) < 3000L;  ){   
////  Right3();
////  Stop();
////  delay(300);
////}
////for( uint32_t tStart = millis();  (millis()-tStart) < 3000L;  ){   
////  Left3();
////  Stop();
////  delay(300);
////}
////Stop();
////delay(500);
////for( uint32_t tStart = millis();  (millis()-tStart) < 3000L;  ){   
////  Forward();
////}
////for( uint32_t tStart = millis();  (millis()-tStart) < 10000L;  ){   
////  Stop();
////}
//
//
//}





























//**************************************************************************************************************************************************************************
// #define MQ3 0
// #define Alcohol_Val 300
//
//
//#define echoPin 12
//#define trigPin 11
//
//long duration, distance;
//
//#define in1 5 //L298n Motor Driver pins.
//#define in2 6
//#define in3 9
//#define in4 10
//#define LED 13
//
//float Breathe_value;
//int command; //Int to store app command state.
//int Speed = 204; // 0 - 255.
//int Speedsec;
//int buttonState = 0;
//int lastButtonState = 0;
//int Turnradius = 0; //Set the radius of a turn, 0 - 255 Note:the robot will malfunction if this is higher than int Speed.
//int brakeTime = 45;
//int brkonoff = 1; //1 for the electronic braking system, 0 for normal.
//
//
//void setup() {
//  pinMode(in1, OUTPUT);
//  pinMode(in2, OUTPUT);
//  pinMode(in3, OUTPUT);
//  pinMode(in4, OUTPUT);
//  pinMode(LED, OUTPUT); //Set the LED pin.
//
//  pinMode(MQ3, INPUT);    // Alcohol sensor MQ3 Sensor
//
//  pinMode(trigPin, OUTPUT);     // Ultra Sonic Sensor
//  pinMode(echoPin, INPUT);    
//  Serial.begin(9600);  //Set the baud rate to your Bluetooth module.
//}
//
//void loop() {
//
//
//  Breathe_value = analogRead(MQ3);
//  Serial.println("Alcohol value");
//  Serial.println(Breathe_value);
//  
//  digitalWrite(trigPin, LOW);
//  delayMicroseconds(2);
//  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPin, LOW);
//  duration = pulseIn(echoPin, HIGH);
//  distance = duration / 58.2;
//  String disp = String(distance);
//  Serial.println("Distance :" + disp + " cm");
//
//
//
//  if ( Breathe_value < Alcohol_Val )   //if alcohol is not detected Start the car else donot start Car
//   {
//  // start if there is no object otherwise stop
//    if(distance>=30)
//    {
//    
//          if (Serial.available() > 0) {
//          command = Serial.read();
//          Stop(); //Initialize with motors stoped.
//          Serial.println(command);
//          switch (command) {
//            case 'F':
//              forward();
//              break;
//            case 'B':
//              back();
//              break;
//            case 'L':
//              left();
//              break;
//            case 'R':
//              right();
//              break;
//            case 'G':
//              forwardleft();
//              break;
//            case 'I':
//              forwardright();
//              break;
//            case 'H':
//              backleft();
//              break;
//            case 'J':
//              backright();
//              break;
//            case '0':
//              Speed = 100;
//              break;
//            case '1':
//              Speed = 140;
//              break;
//            case '2':
//              Speed = 153;
//              break;
//            case '3':
//              Speed = 165;
//              break;
//            case '4':
//              Speed = 178;
//              break;
//            case '5':
//              Speed = 191;
//              break;
//            case '6':
//              Speed = 204;
//              break;
//            case '7':
//              Speed = 216;
//              break;
//            case '8':
//              Speed = 229;
//              break;
//            case '9':
//              Speed = 242;
//              break;
//            case 'q':
//              Speed = 255;
//              break;
//          }
//    Speedsec = Turnradius;
//    if (brkonoff == 1) {
//      brakeOn();
//    } else {
//      brakeOff();
//    }
//  }
//
//
//
//  }else{   // if ultraSonic sensor range is nearer than stop
//      Stop();
//      Serial.println("Danger Stop!");
//  }
//}else{        // Alcohol is Detected Stop
//    Stop();
//    Serial.println("Alcohol is detected! Please Donot drink and drive.");
//}
//
//}
//
//void forward() {
//  analogWrite(in1, Speed);
//  analogWrite(in3, Speed);
//}
//
//void back() {
//  analogWrite(in2, Speed);
//  analogWrite(in4, Speed);
//}
//
//void left() {
//  analogWrite(in3, Speed);
//  analogWrite(in2, Speed);
//}
//
//void right() {
//  analogWrite(in4, Speed);
//  analogWrite(in1, Speed);
//}
//void forwardleft() {
//  analogWrite(in1, Speedsec);
//  analogWrite(in3, Speed);
//}
//void forwardright() {
//  analogWrite(in1, Speed);
//  analogWrite(in3, Speedsec);
//}
//void backright() {
//  analogWrite(in2, Speed);
//  analogWrite(in4, Speedsec);
//}
//void backleft() {
//  analogWrite(in2, Speedsec);
//  analogWrite(in4, Speed);
//}
//
//void Stop() {
//  analogWrite(in1, 0);
//  analogWrite(in2, 0);
//  analogWrite(in3, 0);
//  analogWrite(in4, 0);
//}
//
//void brakeOn() {
//  //Here's the future use: an electronic braking system!
//  // read the pushbutton input pin:
//  buttonState = command;
//  // compare the buttonState to its previous state
//  if (buttonState != lastButtonState) {
//    // if the state has changed, increment the counter
//    if (buttonState == 'S') {
//      if (lastButtonState != buttonState) {
//        digitalWrite(in1, HIGH);
//        digitalWrite(in2, HIGH);
//        digitalWrite(in3, HIGH);
//        digitalWrite(in4, HIGH);
//        delay(brakeTime);
//        Stop();
//      }
//    }
//    // save the current state as the last state,
//    //for next time through the loop
//    lastButtonState = buttonState;
//  }
//}
//void brakeOff() {
//
//}

























/* ------------------------------------------------------------------------------------------------------------------------------------    */

//
//#define echoPin 12
//#define trigPin 11
//
//long duration, distance;
//
//const int  EnableL = 5;
//const int  HighL = 6;
//const int  LowL = 7;
//
//const int  EnableR = 10;
//const int  HighR = 8;
//const int  LowR = 9;
//
//
//void setup() {
//  // put your setup code here, to run once
//
//  Serial.begin (9600);
//  pinMode(trigPin, OUTPUT);
//  pinMode(echoPin, INPUT);
//
//  
//  pinMode(EnableL, OUTPUT);
//  pinMode(HighL, OUTPUT);     //Left Side of Motor
//  pinMode(LowL, OUTPUT);
//
//  pinMode(EnableR, OUTPUT);
//  pinMode(HighR, OUTPUT);      //Right Side of Motor
//  pinMode(LowR, OUTPUT);
//
//}
//
//
//void Forward(){
//  digitalWrite(HighL, LOW);
//  digitalWrite(LowL, HIGH);
//  analogWrite(EnableL, 255);
//
//
//  digitalWrite(HighR, HIGH);
//  digitalWrite(LowR, LOW
//  );
//  analogWrite(EnableR, 255);  
//}
//
//
//void Backward(){
//  digitalWrite(HighL, HIGH);
//  digitalWrite(LowL, LOW);
//  analogWrite(EnableL, 255);
//
//
//  digitalWrite(HighR, HIGH);
//  digitalWrite(LowR, LOW);
//  analogWrite(EnableR, 255);  
//}
//
//
//
//void ForwardLeft1(){
//  digitalWrite(HighL, LOW);
//  digitalWrite(LowL, HIGH);
//  analogWrite(EnableL, 200);
//
//
//  digitalWrite(HighR, LOW);
//  digitalWrite(LowR, HIGH);
//  analogWrite(EnableR, 255);  
//}
//
//
//void ForwardLeft2(){
//  digitalWrite(HighL, LOW);
//  digitalWrite(LowL, HIGH);
//  analogWrite(EnableL, 160);
//
//
//  digitalWrite(HighR, LOW);
//  digitalWrite(LowR, HIGH);
//  analogWrite(EnableR, 255);  
//}
//
//
//void ForwardLeft3(){
//  digitalWrite(HighL, LOW);
//  digitalWrite(LowL, HIGH);
//  analogWrite(EnableL, 100);
//
//
//  digitalWrite(HighR, LOW);
//  digitalWrite(LowR, HIGH);
//  analogWrite(EnableR, 255);  
//}
//
//
//void ForwardRight1(){
//  digitalWrite(HighL, LOW);
//  digitalWrite(LowL, HIGH);
//  analogWrite(EnableL, 255);
//
//
//  digitalWrite(HighR, LOW);
//  digitalWrite(LowR, HIGH);
//  analogWrite(EnableR, 200);  
//}
//
//
//void ForwardRight2(){
//  digitalWrite(HighL, LOW);
//  digitalWrite(LowL, HIGH);
//  analogWrite(EnableL, 255);
//
//
//  digitalWrite(HighR, LOW);
//  digitalWrite(LowR, HIGH);
//  analogWrite(EnableR, 160);  
//}
//
//
//void ForwardRight3(){
//  digitalWrite(HighL, LOW);
//  digitalWrite(LowL, HIGH);
//  analogWrite(EnableL, 255);
//
//
//  digitalWrite(HighR, LOW);
//  digitalWrite(LowR, HIGH);
//  analogWrite(EnableR, 100);  
//}
//
//
//void BackwardLeft1(){
//  digitalWrite(HighL, HIGH);
//  digitalWrite(LowL, LOW);
//  analogWrite(EnableL, 200);
//
//
//  digitalWrite(HighR, HIGH);
//  digitalWrite(LowR, LOW);
//  analogWrite(EnableR, 255);  
//}
//
//
//void BackwardLeft2(){
//  digitalWrite(HighL, HIGH);
//  digitalWrite(LowL, LOW);
//  analogWrite(EnableL, 160);
//
//
//  digitalWrite(HighR, HIGH);
//  digitalWrite(LowR, LOW);
//  analogWrite(EnableR, 255);  
//}
//
//
//void BackwardLeft3(){
//  digitalWrite(HighL, HIGH);
//  digitalWrite(LowL, LOW);
//  analogWrite(EnableL, 100);
//
//
//  digitalWrite(HighR, HIGH);
//  digitalWrite(LowR, LOW);
//  analogWrite(EnableR, 255);  
//}
//
//
//
//void BackwardRight1(){
//  digitalWrite(HighL, HIGH);
//  digitalWrite(LowL, LOW);
//  analogWrite(EnableL, 255);
//
//
//  digitalWrite(HighR, HIGH);
//  digitalWrite(LowR, LOW);
//  analogWrite(EnableR, 200);  
//}
//
//void BackwardRight2(){
//  digitalWrite(HighL, HIGH);
//  digitalWrite(LowL, LOW);
//  analogWrite(EnableL, 255);
//
//
//  digitalWrite(HighR, HIGH);
//  digitalWrite(LowR, LOW);
//  analogWrite(EnableR, 160);  
//}
//
//
//void BackwardRight3(){
//  digitalWrite(HighL, HIGH);
//  digitalWrite(LowL, LOW);
//  analogWrite(EnableL, 255);
//
//
//  digitalWrite(HighR, HIGH);
//  digitalWrite(LowR, LOW);
//  analogWrite(EnableR, 100);  
//}
//
//
//void loop() {
//  // put your main code here, to run repeatedly:
//  Forward();
////  delay(5000);
////  
////  ForwardRight1();
////  delay(5000);
////  ForwardRight2();
////  delay(5000);
////  ForwardRight3();
////  delay(5000);
////  
////  ForwardLeft1();
////  delay(5000);
////  ForwardLeft2();
////  delay(5000);
////  ForwardLeft3();
////  delay(5000);
////
////  
////  Backward();
////  delay(5000);
////  
////  BackwardRight1();
////  delay(5000);
////  BackwardRight2();
////  delay(5000);
////  BackwardRight3();
////  delay(5000);
////  
////  BackwardLeft1();
////  delay(5000);
////  BackwardLeft2();
////  delay(5000);
////  BackwardLeft3();
////  delay(5000);
//
//
//  digitalWrite(trigPin, LOW);
//  delayMicroseconds(2);
//  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPin, LOW);
//  duration = pulseIn(echoPin, HIGH);
//  distance = duration / 58.2;
//  String disp = String(distance);
//  Serial.println("distance :");
//  Serial.println(disp);  
//  Serial.println(" cm");
// if(distance<=30){
//  stop();
//  }
//
//  
//  }
//
//
//  void stop(){
//    digitalWrite(HighL, 0);     //Left Side of Motor
//  digitalWrite(LowL, 0);
//
//
//  digitalWrite(HighR, 0);      //Right Side of Motor
//  digitalWrite(LowR, 0);
//
//    Serial.print("Danger! Stop");
//  }
