#include "MQ135.h"
#include "MQ7.h"
MQ7 mq7(A3, 5.0);
MQ135 mq135(A1,5.0);
int ip=9;
int counter=0;
int count=0;
int analogInPin=A0;                                                             
int sensorPin=0;
void setup() {
  pinMode(ip,INPUT);
pinMode(A0,INPUT);
Serial.begin(9600);
}

void loop() {
  int sensorvalue=digitalRead(ip);
  if (sensorvalue==LOW)
{while(sensorvalue==LOW)
  {counter=counter+1;
   sensorvalue=digitalRead(ip);
   delay(1000); 
  }
}
else if (sensorvalue==HIGH){
  float fn= NH3();
  Serial.print("NH3=");
  Serial.println(fn);
  float fc= CO();
  Serial.print("CO=");
  Serial.println(fc);
  int   t=  taki();
  //Serial.println(t);
  if (t==0){
    Serial.println("taki empty");
  }
  else if(t==1) {
    Serial.println("taki full");
  }
}
  if(counter>2)
{
  count=count+1;
  Serial.print("Person = ");
  Serial.println(count);
  counter=0;
  delay(3000);
}

}








//////NH3 Function///////////////////////
float NH3(){
float n=0;
float sn=0;
for(int i=0;i<6;i++){
n= n + mq135.getPPM();
}
 sn=n/5;
 return sn;
}
//////CO Function/////////////////////////
float CO(){
float sc=0;
float c=0;
for(int j=0;j<6;j++){
c= c + mq7.getPPM();
}
 sc=c/5;
 return sc;
}
//////panaychi taki Function/////////////
int taki(){
  sensorPin=analogRead(analogInPin);
  if(sensorPin<=150)
  {
    return 0;
  }
   if(sensorPin>500)
  {
    return 1;
  }
  
}
