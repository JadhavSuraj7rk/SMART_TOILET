#include<SoftwareSerial.h> //Included SoftwareSerial Library
//Started mySerial SoftwareSerial
SoftwareSerial mySerial(6,7);
#include "rfid.h"
#include "RTClib.h"
RTC_DS1307 rtc1;
int chinu=0,mari=0;
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
int dirt1;
DateTime now1 = rtc1.now();
DateTime future1 (now1 + TimeSpan(0,1,0,0));



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

  chinu=future1.hour();
}

void loop() {
  //rfidloop();
  access=digitalRead(pin);
  while(access==0){
     access=digitalRead(pin);
    }
  DateTime now1 = rtc1.now();
  mari=now1.hour();

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
      dirtlevel=dirt();
      Serial.print("dirt");
      Serial.println(dirtlevel);
      if (gaslevel > 200 || waterlevel==0|| dirtlevel==0 ) {
        digitalWrite(3, HIGH);
        call();
      }
      if(chinu==mari){
        
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
      id[0]='D';
      mySerial.write(id,1);
      delay(100);
      Serial.print("dirt=");  
      Serial.println(dirtlevel); 
      mySerial.write(dirtlevel);
      id[0]='W';
      mySerial.write(id,1);
      delay(100);
      Serial.print("taki=");  
      Serial.println(waterlevel); 
      mySerial.write(waterlevel);
      //delay(2000);
      rfidloop();
      DateTime future1 (now1 + TimeSpan(0,1,0,0));
      chinu=future1.hour();
       
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
  Y=map(water,0,700,0,100);
  if(Y>70){
  return 1;  
  }
  else if(Y<70){
    return 0;
  }
  
}



//////dirt
int dirt()
{
  digitalWrite(8,HIGH);
  delay(300);
  dirt1=digitalRead(6);
  return dirt1;
}
