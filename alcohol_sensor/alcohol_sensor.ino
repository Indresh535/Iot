//Alcohol Detector based on MQ3
 /* Here are the list of I/O pins*/3
 #define MQ3 A0
 #define Buzzer 8 
 #define LED 9
 /***/
//Threshold value of MQ3 reading above which it should trigger/
 #define Thres_Val 440
 //
 // global int to store the analog reading from MQ3 (0 to 1023)
 int value;
 void setup() {
   // declaring the input and output pins
   pinMode(MQ3, INPUT);
   pinMode(Buzzer, OUTPUT);
   pinMode(LED, OUTPUT);
 // Serial Output for debugging
   Serial.begin(9600);
 }
 void loop() {
   // reads the analog value from MQ3
   value = analogRead(MQ3);
 // sends the value to UART for debugging
   Serial.println(value);
 if ( value > Thres_Val )   //if alcohol is detected
   {
     digitalWrite ( LED , HIGH );    // turns the LED on
 digitalWrite(Buzzer,HIGH);    // turns on (uncomment if buzzer is used) 
digitalWrite(Buzzer, HIGH);             //Generate a 1000Hz tone only if you use speaker (comment out if buzzer is used)
 }
 else {
     digitalWrite(LED, LOW);       //  turns the LED off
 digitalWrite(Buzzer,LOW);   //  turns off (uncomment if buzzer is used) 
digitalWrite(Buzzer,LOW);               //  Removes the tone from speaker (comment out if buzzer is used)
 }
 delay (500);            //  a 500ms delay before reading is taken again
 }
