#include<SoftwareSerial.h> //Included SoftwareSerial Library
//Started mySerial SoftwareSerial
SoftwareSerial mySerial(0, 6);
#include "rfid.h"
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

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
String watery;

void setup() {
  //Serial mySerial Begin at 9600 Baud
  mySerial.begin(9600);
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  pinMode(pin, INPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);
  pinMode(5, OUTPUT);
  pinMode(A3, OUTPUT);
  digitalWrite(7, LOW);
  analogWrite(5, 190);
  analogWrite(A3, 0);
  // rtcsetup();
  rfidsetup();
  //rtcsetup();
  lcd.setCursor(0, 0);
  lcd.print("connecting");
  lcd.clear();

}

void loop() {

  //rfidloop();


  access = digitalRead(pin);
  while (access == 0) {
    access = digitalRead(pin);
    //lcd.setCursor(10,0);
  }
  //   error();
  //   analogWrite(A1,168);
  fn = dist();
  if (fn == 1) {
    while (fn == 1) {
      counter++;
      fn = dist();
      digitalWrite(7, HIGH);
      delay(500);
    }
  }
  else {
    if (counter > 2) {
      count1 = count1 + 1;
      count2 = count2 + count1;
      counter = 0;
      delay(8000);
      check();
    }
    digitalWrite(7, LOW);
    Serial.print("count=");
    Serial.println(count1);
    // Serial.print("count esp=");
    // Serial.println(count2);
    gaslevel = mq135();
    Serial.print("ppm=");
    Serial.println(gaslevel);
    waterlevel = level();
    Serial.print("taki=");
    Serial.println(waterlevel);
    if (count2 > 10) {
      count2 = 0;
      automatic();
    }
    if (gaslevel > 110 || waterlevel == 0 ) {
      call();
    }
  }
  //delay(50);
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
      count2 = count2 + count1;
      counter = 0;
    }
    delay(8000);
    check();
  }

  loop();
}

void call() {
  if (gaslevel > 110 && waterlevel != 0)  {
    analogWrite(A3, 255);
    delay(9000);
    analogWrite(A3, 0);
    gaslevel = mq135();
    Serial.println("gaslevel");
    Serial.println(gaslevel);
    while (gaslevel < 110) {
      loop();
    }
  }
  analogWrite(5, 0);
  digitalWrite(7, HIGH);
  id[0] = 'C';
  mySerial.write(id, 1);
  delay(100);
  Serial.print("count");
  Serial.println(count1);
  mySerial.write(count1);
  delay(100);
  analogWrite(5, 190);
  id[0] = 'G';
  mySerial.write(id, 1);
  delay(50);
  Serial.print("ppm=");
  Serial.println(gaslevel);
  uint8_t gLSB = gaslevel;
  uint8_t gMSB = gaslevel >> 8;
  mySerial.write(gMSB);
  mySerial.write(gLSB);
  //mySerial.write(gaslevel);
  delay(50);
  id[0] = 'W';
  mySerial.write(id, 1);
  delay(100);
  Serial.print("taki=");
  Serial.println(waterlevel);
  mySerial.write(waterlevel);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TOILET IS");
  lcd.setCursor(0, 1);
  lcd.print("UNCLEAN");
  thumbdown();
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("GAS");
  lcd.setCursor(0, 1);
  lcd.print(gaslevel);
  if (waterlevel == 1) {
    watery = "YES";
    lcd.setCursor(5, 0);
    lcd.print("WATER");
    lcd.setCursor(6, 1);
    lcd.print(watery);
    //lcd.setCursor(6, 1);
    // lcd.print(water);
  }
  else {
    watery = "NO";
    lcd.setCursor(5, 0);
    lcd.print("WATER");
    lcd.setCursor(6, 1);
    lcd.print(watery);
    //lcd.print(water);

  }

  lcd.setCursor(11, 0);
  lcd.print("COUNT");
  lcd.setCursor(13, 1);
  lcd.print(count2);

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
      digitalWrite(7, LOW);  
    }
    delay(1000);
    content = " XX XX XX XX";
    points = 0;
  }
  analogWrite(5, 0);
  gaslevel = mq135();
  waterlevel = level();
  if (gaslevel > 110 || waterlevel == 0 ) {
    points = 0;
  }
  else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("TOILET IS");
    lcd.setCursor(0, 1);
    lcd.print("CLEAN");
    thumbsup();

    delay(1000);
  }
  id[0] = 'P';
  mySerial.write(id, 1);
  Serial.print("points=");
  Serial.println(points);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("points:");
  lcd.setCursor(7, 0);
  mySerial.write(points);
  lcd.print(points);
  //delay(1000);
  str_len = content.length() + 1;
  content.toCharArray(sweepid, str_len);
  mySerial.write(sweepid, 12);
  content = "";
  lcd.setCursor(0, 1);
  lcd.print("ID:");
  lcd.setCursor(3, 1);
  lcd.print(sweepid);
  delay(2000);
  analogWrite(5, 190);
  lcd.clear();

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
  //  analogWrite(A1,168);
  gas = analogRead(A0);
  if (gas == 0 || gas > 1000) {
    while (gas == 0 || gas > 1000) {

      digitalWrite(7, HIGH);
      delay(200);
      digitalWrite(7, LOW);
      Serial.println("error");
      lcd.clear();
      lcd.setCursor(0, 0);
      // lcd.autoscroll();
      lcd.print("GAS ERROR");
      delay(1000);
    }
    delay(100);
  }
  return gas;
}


////////waterlevel
int level()
{
  water = analogRead(A1);
  if ( water > 750) {
    while ( water > 750) {
      digitalWrite(7, HIGH);
      delay(200);
      digitalWrite(7, LOW);
      Serial.println("error");
      lcd.clear();
      lcd.setCursor(0, 0);
      // lcd.autoscroll();
      lcd.print("WATER ERROR");
      delay(1000);
    }
    delay(100);
  }
  Y = map(water, 0, 400, 0, 100);

  //analogWrite(A1,168);
  if (Y > 40) {
    return 1;
  }
  else if (Y < 40) {
    return 0;
  }

}





void thumbsup() {
  byte thumb1[8] = {B00100, B00011, B00100, B00011, B00100, B00011, B00010, B00001};
  byte thumb2[8] = {B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00011};
  byte thumb3[8] = {B00000, B00000, B00000, B00000, B00000, B00000, B00001, B11110};
  byte thumb4[8] = {B00000, B01100, B10010, B10010, B10001, B01000, B11110, B00000};
  byte thumb5[8] = {B00010, B00010, B00010, B00010, B00010, B01110, B10000, B00000};
  byte thumb6[8] = {B00000, B00000, B00000, B00000, B00000, B10000, B01000, B00110};
  lcd.createChar(0, thumb1);
  lcd.createChar(1, thumb2);
  lcd.createChar(2, thumb3);
  lcd.createChar(3, thumb4);
  lcd.createChar(4, thumb5);
  lcd.createChar(5, thumb6);
  lcd.setCursor(11, 1);
  lcd.write(0);
  lcd.setCursor(11, 0);
  lcd.write(1);
  lcd.setCursor(12, 1);
  lcd.write(2);
  lcd.setCursor(12, 0);
  lcd.write(3);
  lcd.setCursor(13, 1);
  lcd.write(4);
  lcd.setCursor(13, 0);
  lcd.write(5);
}



void thumbdown() {
  byte thumb1[8] = {B00001, B00010, B00011, B00100, B00011, B00100, B00011, B00100};
  byte thumb2[8] = {B00011, B00000, B00000, B00000, B00000, B00000, B00000, B00000};
  byte thumb3[8] = {B11110, B00001, B00000, B00000, B00000, B00000, B00000, B00000};
  byte thumb4[8] = {B00000, B11110, B01000, B10001, B10010, B10010, B01100, B00000};
  byte thumb5[8] = {B00000, B10000, B01110, B00010, B00010, B00010, B00010, B00010};
  byte thumb6[8] = {B00110, B01000, B10000, B00000, B00000, B00000, B00000, B00000};
  lcd.createChar(0, thumb1);
  lcd.createChar(1, thumb2);
  lcd.createChar(2, thumb3);
  lcd.createChar(3, thumb4);
  lcd.createChar(4, thumb5);
  lcd.createChar(5, thumb6);
  lcd.setCursor(11, 0);
  lcd.write(0);
  lcd.setCursor(11, 1);
  lcd.write(1);
  lcd.setCursor(12, 0);
  lcd.write(2);
  lcd.setCursor(12, 1);
  lcd.write(3);
  lcd.setCursor(13, 0);
  lcd.write(4);
  lcd.setCursor(13, 1);
  lcd.write(5);
}

void automatic() {
  check();
  digitalWrite(8, HIGH);
  analogWrite(A3, 255);
  delay(5000);
  digitalWrite(8, LOW);
  analogWrite(A3, 0);
}
/////ERROR
