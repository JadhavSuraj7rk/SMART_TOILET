#include<SoftwareSerial.h> //Included SoftwareSerial Library
//Started mySerial SoftwareSerial
SoftwareSerial mySerial(10,11);
int gas=955;
int count1=10;
int water=255;
int pin=2;
int access;
 char id[1];

void setup() {
  //Serial mySerial Begin at 9600 Baud
  mySerial.begin(9600);
  pinMode(pin,INPUT);
  
}

void loop() {
 // mySerial.write(id,1);
  //delay(1000);
  //mySerial.write(gas);
  //delay(1000);
 // mySerial.write(count1);
  //delay(1000);
  //mySerial.write(water);
  //delay(1000);
  access=digitalRead(pin);
  while(access==0){
     access=digitalRead(pin);
    }
  id[0]='G';
  mySerial.write(id,1);
  delay(500);
  gasy();
  delay(100);
  id[0]='C';
  mySerial.write(id,1);
  delay(100);
  county();
  delay(100);
  id[0]='W';
  mySerial.write(id,1);
  delay(100);
  watery();
  delay(1000);  
}

void gasy(){
  
  uint8_t gLSB = gas;
  uint8_t gMSB = gas >> 8;
  mySerial.write(gMSB);
  mySerial.write(gLSB);
 delay(500);
 
}

void county(){

 
  mySerial.write(count1);

}

void watery(){
  

   mySerial.write(water);
   
}
