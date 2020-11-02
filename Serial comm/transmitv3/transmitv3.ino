#include<SoftwareSerial.h> //Included SoftwareSerial Library
//Started mySerial SoftwareSerial
SoftwareSerial mySerial(10,11);
const byte interruptPin = 2;
int gas=45;
int count1=12;
int water=255;
 char id[1];

void setup() {
  //Serial mySerial Begin at 9600 Baud
  mySerial.begin(9600);
  pinMode(interruptPin, INPUT);
  //digitalWrite(interruptPin,HIGH);
  attachInterrupt(digitalPinToInterrupt(interruptPin), process, FALLING);
}

void loop() {
 
}
void process(){
  id[0]='G';
  mySerial.write(id,1);
  del();
  gasy();
  del();
  id[0]='C';
  mySerial.write(id,1);
  del();
  county();
  del();
  id[0]='W';
  mySerial.write(id,1);
  del();
  watery();
  del(); 
}

void gasy(){
  
 
  mySerial.write(gas);

 
}

void county(){

 
  mySerial.write(count1);

}

void watery(){
  

   mySerial.write(water);
   
}
void del(){
  delay(200);
}
