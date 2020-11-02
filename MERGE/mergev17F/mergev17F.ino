#include<SoftwareSerial.h> //Included SoftwareSerial Library
//Started mySerial SoftwareSerial
SoftwareSerial mySerial(5, 6);
#include "rfid.h"
int pin = 4;
int access;
char id[1];
const int trigPin = 2;
const int echoPin = 3;
long duration;
int distance;
int counter, count1;
int current = 0;
int water;
int gas = 0;
int fn;
int gaslevel;
int waterlevel;
//int dirtlevel;
int Y;
//int laser;
int dirt1, i;
int count2;





void setup() {
  //Serial mySerial Begin at 9600 Baud
  mySerial.begin(9600);
  Serial.begin(9600);
  pinMode(pin, INPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);
  digitalWrite(7, LOW);
  // rtcsetup();
  rfidsetup();
  //rtcsetup();


}

void loop() {
  //rfidloop();
  access = digitalRead(pin);
  while (access == 0) {
    access = digitalRead(pin);
  }
  gas = analogRead(A0);
  water=analogRead(A1);
  Y=map(water,0,650,0,100);
  while (gas == 0 || gas > 1000||Y>100) {
    Serial.println("error");
    analogWrite(A2,0);
  }
analogWrite(A2,168);
  fn = dist();
  if (fn == 1) {
    while (fn == 1) {
      counter++;
      fn = dist();
      delay(500);
    }
  }
  else {
    if (counter > 2) {
      count1 = count1 + 1;
      count2 = count2 + 1;
      counter = 0;
      delay(10000);
      check();
    }

    Serial.print("count=");
    Serial.println(count1);
    Serial.print("count esp=");
    Serial.println(count2);
    gaslevel = mq135();
    Serial.print("ppm=");
    Serial.println(gaslevel);
    waterlevel = level();
    Serial.print("taki=");
    Serial.println(waterlevel);

    //      dirtlevel=dirt();
    //      Serial.print("dirt=");
    //      Serial.println(dirtlevel);
    if (gaslevel > 500 || waterlevel == 0 ) {
      digitalWrite(7, HIGH);
      call();


    }
  }
  delay(50);
}

void check() {
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

void call() {
  id[0] = 'C';
  mySerial.write(id, 1);
  delay(100);
  Serial.print("count");
  Serial.println(count1);
  mySerial.write(count1);
  delay(100);

  id[0] = 'S';
  mySerial.write(id, 1);
  delay(100);
  Serial.println("count esp=");
  Serial.println(count2);
  mySerial.write(count2);
  delay(100);
  id[0] = 'G';
  mySerial.write(id, 1);
  delay(100);
  Serial.print("ppm=");
  Serial.println(gaslevel);
  uint8_t gLSB = gaslevel;
  uint8_t gMSB = gaslevel >> 8;
  mySerial.write(gMSB);
  mySerial.write(gLSB);
  //mySerial.write(gaslevel);
  delay(100);
  id[0] = 'W';
  mySerial.write(id, 1);
  delay(100);
  Serial.print("taki=");
  Serial.println(waterlevel);
  mySerial.write(waterlevel);
  //      points=-1;
  //      id[0]='P';
  //      mySerial.write(id,1);
  //      Serial.print("points=");
  //      Serial.println(points);
  //      mySerial.write(points);
  //      delay(100);
  //      str_len = content.length() + 2;
  //      content.toCharArray(sweepid, str_len);
  //      mySerial.write(sweepid,12);
  //      content="";
  //      delay(100);
  rfidloop();
  count1 = 0;
  if (minu == sinu) {
    if (level() == 0) {
      Serial.print("no  water wash");
    }
    else {
      Serial.print("water wash");
      digitalWrite(8, HIGH);
      delay(5000);
      digitalWrite(8, LOW);

    }
    content = " XX XX XX XX";
    points = sinu - minu;
  }
  gaslevel = mq135();
  waterlevel = level();
  if (gaslevel > 100 || waterlevel == 0 ) {
    points = 0;
  }
  id[0] = 'P';
  mySerial.write(id, 1);
  Serial.print("points=");
  Serial.println(points);
  mySerial.write(points);
  delay(50);
  str_len = content.length() + 1;
  content.toCharArray(sweepid, str_len);
  mySerial.write(sweepid, 12);
  content = "";
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
  if (distance <= 30)
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
  water=analogRead(A1);
  Y=map(water,0,650,0,100);
  while (gas == 0 || gas > 1000||Y>100) {
    Serial.println("error");
    analogWrite(A2,0);
  }
analogWrite(A2,168);
  //gas = analogRead(A0);
  return gas;
}


////////waterlevel
int level()
{

   gas = analogRead(A0);
  water=analogRead(A1);
  Y=map(water,0,650,0,100);
  while (gas == 0 || gas > 1000||Y>100) {
    Serial.println("error");
    analogWrite(A2,0);
  }
analogWrite(A2,168);
    water = analogRead(A1);
    Y = map(water, 0, 650, 0, 100);
    if (Y > 50) {
      return 1;
    }
    else if (Y < 50) {
      return 0;
    }

  }



  ////dirt
  //int dirt()
  //{
  //  analogWrite(A2,255);
  //  delay(1000);
  //  dirt1=digitalRead(8);
  //  analogWrite(A2,0);
  //  return dirt1;
  //}
 
