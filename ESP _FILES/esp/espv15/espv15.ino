#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>   //esp files
#include<SoftwareSerial.h> //Included SoftwareSerial Library
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial mySerial(D7, D8);
const char *ssid = "android ap";  //ENTER YOUR WIFI SETTINGS
const char *password = "androidap";
String ToCo_id = "TOILET-1";
int compartment = 2;
String area = "VIKHROLI";
String water;
int gas, count1, point, count2;
int watery, i;
char id[1];
String card;
char sweepid[13];
const int errorintrrupt = 14;
byte wifi[8] = {
  B00000,
  B01110,
  B10001,
  B00000,
  B00100,
  B01010,
  B00000,
  B00100,
};
void setup() {

  Serial.begin(9600);
  mySerial.begin(9600);
  Wire.begin(2, 0);
  lcd.begin();
  lcd.backlight();
  pinMode(D2, OUTPUT);
  pinMode(D8, OUTPUT);
 // attachInterrupt(digitalPinToInterrupt(errorintrrupt),CREDIT, FALLING);
  digitalWrite(D2, LOW);
  digitalWrite(D8, LOW);
  lcd.createChar(6, wifi);
  delay(500);
  WiFi.mode(WIFI_OFF);  // Wifi mode off
  delay(500);
  WiFi.mode(WIFI_STA);  // Wifi station mode
  delay(500);
  WiFi.begin(ssid, password); // Connecting to Wifi
  Serial.println("Connecting");
  lcd.setCursor(0, 0);
  lcd.print("Connecting ");


  while (WiFi.status() != WL_CONNECTED) // Checking if connected
  {


    lcd.write(byte(6));
    delay(2000);
    Serial.print(".");


  }
  lcd.clear();
  Serial.println("");
  Serial.print("Connected to ");
  lcd.setCursor(0, 0);
  lcd.print("Connected to");
  lcd.setCursor(0, 1);
  lcd.print(ssid);
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  delay(500);
  lcd.clear();

}

void loop() {
  lcd.clear();
  digitalWrite(D2, HIGH);
  digitalWrite(D8, HIGH);
  HTTPClient http; //Declare object of class HTTPClient
  WiFiClient client;


  for (i = 1; i < 5; i++) {

    while (!mySerial.available()) {
      while (WiFi.status() != WL_CONNECTED) {
        digitalWrite(D2, LOW);
        digitalWrite(D8, LOW);
      }
    }
    mySerial.readBytes(id, 1); //Read the serial data and store it
    Serial.print(" id=");
    Serial.println(id);
    if (id[0] == 'G') {

      while (mySerial.available() < 2) {
        while (WiFi.status() != WL_CONNECTED) {
          digitalWrite(D2, LOW);
          digitalWrite(D8, LOW);
        }
      }
      byte b1  = mySerial.read();
      byte b2 =  mySerial.read();
      gas = ((int)b1) * 256 + b2;
      Serial.print("gas: ");
      Serial.println(gas);



    }

    if (id[0] == 'C') {
      while (!mySerial.available()) {
        while (WiFi.status() != WL_CONNECTED) {
          digitalWrite(D2, LOW);
          digitalWrite(D8, LOW);
        }
      }
      count1 = mySerial.read(); //Read the serial data and store it
      Serial.print(" count1=");
      Serial.println(count1);


    }

    if (id[0] == 'S') {
      while (!mySerial.available()) {
        while (WiFi.status() != WL_CONNECTED) {
          digitalWrite(D2, LOW);
          digitalWrite(D8, LOW);
        }
      }
      count2 = mySerial.read(); //Read the serial data and store it
      Serial.print(" count esp=");
      Serial.println(count2);


    }

    if (id[0] == 'W') {
      while (!mySerial.available()) {
        while (WiFi.status() != WL_CONNECTED) {
          digitalWrite(D2, LOW);
          digitalWrite(D8, LOW);
        }
      }
      watery = mySerial.read(); //Read the serial data and store it
      Serial.print(" water=");



      if (watery == 1) {
        water = "YES";
        Serial.println(water);
        //lcd.setCursor(6, 1);
        // lcd.print(water);
      }
      else {
        water = "NO";
        Serial.println(water);

      }

    }
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TOILET IS");
  lcd.setCursor(0, 1);
  lcd.print("UNCLEAN");
  thumbdown();
  delay(1500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("GAS");
  lcd.setCursor(0, 1);
  lcd.print(gas);
  lcd.setCursor(5, 0);
  lcd.print("WATER");
  lcd.setCursor(6, 1);
  lcd.print(water);
  lcd.setCursor(11, 0);
  lcd.print("COUNT");
  lcd.setCursor(13, 1);
  lcd.print(count2);

  //lcd.clear();




  card = "xxxxxxxx";
  point = -1;
  http.begin(client, "http://192.168.43.35/test/designv5.php?ToCo_id=" + ToCo_id + "&gas=" + gas + "&count1=" + count1 + "&water=" + water + "&area=" + area + "&compartment=" + compartment + "&point=" + point + "&card=" + card);
  delay(500);
  int httpCode = http.GET();
  Serial.println(httpCode);
  http.end();
  Serial.println("next");
  while(digitalRead(errorintrrupt)==HIGH){
    
  }
//  card = "";
//  while (!mySerial.available()) {
//    while (WiFi.status() != WL_CONNECTED) {
//      digitalWrite(D2, LOW);
//      digitalWrite(D8, LOW);
//    }
//    delay(500);
//  }
//
//  mySerial.readBytes(id, 1); //Read the serial data and store it
//  Serial.print(" id=");
//  Serial.println(id);
//
//  if (id[0] == 'P') {
//    while (!mySerial.available()) {
//      while (WiFi.status() != WL_CONNECTED) {
//        digitalWrite(D2, LOW);
//        digitalWrite(D8, LOW);
//      }
//    }
//    lcd.clear();
//    point = mySerial.read(); //Read the serial data and store it
//    Serial.print(" points=");
//    Serial.println(point);
//    lcd.setCursor(0, 0);
//    lcd.print("points:");
//    lcd.setCursor(7, 0);
//    lcd.print(point);
//    while (!mySerial.available()) {
//      while (WiFi.status() != WL_CONNECTED) {
//        digitalWrite(D2, LOW);
//        digitalWrite(D8, LOW);
//      }
//    }
//    //delay(30);
//    mySerial.readBytes(sweepid, 12);
//    for (i = 0; i < 12; i++) {
//      card.concat(sweepid[i]);
//    }
//    Serial.print("card=");
//    Serial.println(card);
//    lcd.setCursor(0, 1);
//    lcd.print("ID:");
//    lcd.setCursor(3, 1);
//    lcd.print(card);
//    card.trim();
//    card.replace(" ", ".");
//    Serial.println(card);

    http.begin(client, "http://192.168.43.35/test/designv5.php?ToCo_id=" + ToCo_id + "&gas=" + gas + "&count1=" + count1 + "&water=" + water + "&area=" + area + "&compartment=" + compartment + "&point=" + point + "&card=" + card);
    httpCode = http.GET();
    Serial.println(httpCode);
    http.end();
    //delay(50);
    //lcd.clear();
    while (WiFi.status() != WL_CONNECTED) {
      digitalWrite(D2, LOW);
      digitalWrite(D8, LOW);
    }
    lcd.clear();
    if (point == 1) {
      lcd.setCursor(0, 0);
      lcd.print("TOILET IS");
      lcd.setCursor(0, 1);
      lcd.print("CLEAN");
      thumbsup();
    }
    delay(1000);
    lcd.clear();



  }




//////thumbsup
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
ICACHE_RAM_ATTR void CREDIT(){
 POINTA(); 
}
void POINTA(){
  card = "";
  while (!mySerial.available()) {
    while (WiFi.status() != WL_CONNECTED) {
      digitalWrite(D2, LOW);
      digitalWrite(D8, LOW);
    }
    
  }

  mySerial.readBytes(id, 1); //Read the serial data and store it
 // Serial.print(" id=");
 // Serial.println(id);

  if (id[0] == 'P') {
    while (!mySerial.available()) {
      while (WiFi.status() != WL_CONNECTED) {
        digitalWrite(D2, LOW);
        digitalWrite(D8, LOW);
      }
    }
    lcd.clear();
    point = mySerial.read(); //Read the serial data and store it
 //   Serial.print(" points=");
 //   Serial.println(point);
    lcd.setCursor(0, 0);
    lcd.print("points:");
    lcd.setCursor(7, 0);
    lcd.print(point);
    while (!mySerial.available()) {
      while (WiFi.status() != WL_CONNECTED) {
        digitalWrite(D2, LOW);
        digitalWrite(D8, LOW);
      }
    }
    //delay(30);
    mySerial.readBytes(sweepid, 12);
    for (i = 0; i < 12; i++) {
      card.concat(sweepid[i]);
    }
 //   Serial.print("card=");
 //   Serial.println(card);
    lcd.setCursor(0, 1);
    lcd.print("ID:");
    lcd.setCursor(3, 1);
    lcd.print(card);
    card.trim();
    card.replace(" ", ".");
  //  Serial.println(card);
}
}
