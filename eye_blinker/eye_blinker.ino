int flag=0;
int t1=0;
int t2=0;
void setup() 
{
  Serial.begin(9600);
  pinMode(2,OUTPUT);

}
void loop() 
{
  int x=analogRead(A0);
  Serial.println(x);

    if(x<400 && flag==0)
  {
    flag=1;
    t1=millis();
  }
  else if(x>400 && flag==1)
  {
    flag=0;
    t2=millis();
    Serial.println(t2-t1);
    if((t2-t1)>250)
    {
      digitalWrite(2,HIGH);
      Serial.println("Alert2!!!!!!!!!!!!!!!!!");
      delay(2000);
      digitalWrite(2,LOW);
    }
    else; 
  } 
}
