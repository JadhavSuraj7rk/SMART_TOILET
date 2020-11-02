#include<SoftwareSerial.h> //Included SoftwareSerial Library
//Started mySerial SoftwareSerial
SoftwareSerial mySerial(6,7);
#include "rfid.h"
int pin=2;
int access;
char id[1];
const int trigPin = 4;
const int echoPin = 5;
long duration;
int distance;
int counter, count1;
int current = 0;
int water;
int gas = 0;
int fn;
int gaslevel;
int waterlevel;
int dirtlevel;
int Y;
int laser;
int dirt1,i;




void setup() {
  //Serial mySerial Begin at 9600 Baud
  mySerial.begin(9600);
  Serial.begin(9600);
  pinMode(pin,INPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); 
 // rtcsetup();
  rfidsetup();
  //rtcsetup();

  
}

void loop() {
  //rfidloop();
  access=digitalRead(pin);
  while(access==0){
     access=digitalRead(pin);
    }
    //error();
 fn = dist();
  if (fn == 1) {
    while (fn == 1) {
      counter++;
      fn = dist();
      delay(1000);
    }
  }
  else {
    if (counter > 2) {
      count1 = count1 + 1;
      counter = 0;
      delay(10000);
      check();
      }
      
      Serial.print("count");
      Serial.println(count1);  
      gaslevel=mq135();
      Serial.print("ppm="); 
      Serial.println(gaslevel);
      waterlevel=level();
      Serial.print("taki=");  
      Serial.println(waterlevel);
      
//      dirtlevel=dirt();
//      Serial.print("dirt=");
//      Serial.println(dirtlevel);
     if (gaslevel > 0 || waterlevel==0 ) {
        digitalWrite(3, HIGH);
        call();
        
        
      }  
  }
  delay(1000);
}

void check(){
   fn = dist();
  if (fn == 1) {
    while (fn == 1) {
      counter++;
      fn = dist();
      delay(1000);
    }
    if (counter > 2) {
      count1 = count1 + 1;
      counter = 0;
      }
      delay(10000);
      check();
  }
 
      loop();
  }

void call(){
      id[0]='C';
      mySerial.write(id,1);
      delay(100);
      Serial.print("count");
      Serial.println(count1);
      mySerial.write(count1);
      delay(100);
      id[0]='G';
      mySerial.write(id,1);
      delay(100);
      Serial.print("ppm="); 
      Serial.println(gaslevel);
      uint8_t gLSB = gaslevel;
      uint8_t gMSB = gaslevel >> 8;
      mySerial.write(gMSB);
      mySerial.write(gLSB);
      //mySerial.write(gaslevel);
      delay(100);
      id[0]='W';
      mySerial.write(id,1);
      delay(100);
      Serial.print("taki=");  
      Serial.println(waterlevel); 
      mySerial.write(waterlevel);
      //delay(2000);
      rfidloop();
      count1=0;
       id[0]='P';
      mySerial.write(id,1);
      Serial.print("points=");
      Serial.println(points);
      mySerial.write(points);
      delay(100);
      str_len = content.length() + 2;
      content.toCharArray(sweepid, str_len);
      mySerial.write(sweepid,13);
      content="";
      delay(100); 
       

}


/////////
//////distance measurement
int dist() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  delay(100);
  if (distance <= 50)
  {
    current = 1;
  }
  else {
    current = 0;
  }
  return current;
}


////////air quality
int mq135()
{
 
  gas = analogRead(A0);
  return gas;
}


////////waterlevel
int level()
{
 
  water = analogRead(A1);
  Y=map(water,0,450,0,100);
  if(Y>70){
  return 1;  
  }
  else if(Y<70){
    return 0;
  }
  
}



////dirt
int dirt()
{
  analogWrite(A2,255);
  delay(1000);
  dirt1=digitalRead(8);
  analogWrite(A2,0);
  return dirt1;
}
//void error(){
//  int g1,w1;
//  
//   //char errw[5];
//  g1=analogRead(A0);
//  w1=analogRead(A1);
//  if(g1==0||g1>1000||w1<100||w1>1000){
//    id[0]='V';
//      mySerial.write(id,1);
//      delay(200);
//      if(g1==0||g1>1000){
//         int e=0;
//         mySerial.write(e);
//         Serial.println(e);
//      }
//      
//    
//  else if(w1<100||w1>1000){
//   int e=1;
//         mySerial.write(e);
//         Serial.println(e);
//      }
//    delay(100);
//  }
//}
