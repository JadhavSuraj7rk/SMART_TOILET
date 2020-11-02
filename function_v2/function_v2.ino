#include "MQ135.h"
#include "MQ7.h"
MQ7 mq7(A3, 5.0);
MQ135 mq135(A1,5.0);
int ip=9;
int counter=0;
int count=0;
int analogInPin=A0;                                                             
int sensorPin=0;
int sensorvalue=0;
const byte interruptPin = 2;
void setup() {
  
  pinMode(interruptPin, INPUT_PULLUP);
  pinMode(ip,INPUT);
  pinMode(A0,INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, LOW);
  Serial.begin(9600);
}

void loop() {
  Serial.print(".");
  delay(1000);
  
}
  


void blink() {
  sensorvalue=digitalRead(interruptPin);
  show();
}
void show(){
if (sensorvalue==LOW)
{while(sensorvalue==LOW)
  {counter=counter+1;
   sensorvalue=digitalRead(interruptPin);
   delay(1000); 
  }
}
  
  if(counter>2)
{
  count=count+1;
  counter=0;
  sense();
  delay(300);
}
}

//////NH3 Function///////////////////////
float NH3(){
float n=0;
float sn=0;
for(int i=0;i<6;i++){
n= n + mq135.getPPM();
delay(100);
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
delay(100);
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

/////////////////Sense function//////////////
void sense(){
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
  Serial.print("Person = ");
  Serial.println(count);
}
