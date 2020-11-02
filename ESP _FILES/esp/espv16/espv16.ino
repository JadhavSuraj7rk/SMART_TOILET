#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>   //esp files
#include<SoftwareSerial.h> //Included SoftwareSerial Library
#include <Wire.h>

SoftwareSerial mySerial(D7, D8);
const char *ssid = "android ap";  //ENTER YOUR WIFI SETTINGS
const char *password = "androidap";
String ToCo_id = "TOILET-1";
int compartment = 2;
String area = "VIKHROLI";
String water;
int gas, count1, point;
int count2 = 0;
int watery, i;
char id[1];
String card;
const int errorinterrupt = 14;
char sweepid[13];

void setup() {

  Serial.begin(9600);
  mySerial.begin(9600);


  pinMode(D2, OUTPUT);
  pinMode(D8, OUTPUT);
  digitalWrite(D2, LOW);
  digitalWrite(D8, LOW);

  delay(500);
  WiFi.mode(WIFI_OFF);  // Wifi mode off
  delay(500);
  WiFi.mode(WIFI_STA);  // Wifi station mode
  delay(500);
  WiFi.begin(ssid, password); // Connecting to Wifi
  Serial.println("Connecting");


  while (WiFi.status() != WL_CONNECTED) // Checking if connected
  {
    //    lcd.write(byte(6));
    delay(1000);
    Serial.print(".");
  }
  //lcd.clear();
  Serial.println("");
  Serial.print("Connected to ");
  //  lcd.setCursor(0, 0);
  //  lcd.print("Connected to");

  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  delay(100);
  //lcd.clear();

}

void loop() {
  //lcd.clear();
  digitalWrite(D2, HIGH);
  digitalWrite(D8, HIGH);
  HTTPClient http; //Declare object of class HTTPClient
  WiFiClient client;
  while (digitalRead(errorinterrupt) == HIGH) {
    
  }
  for (i = 1; i < 4; i++) {

    while (!mySerial.available()) {
    }
    mySerial.readBytes(id, 1); //Read the serial data and store it
    Serial.print(" id=");
    Serial.println(id);
    if (id[0] == 'C') {
      while (!mySerial.available()) {

      }
      count1 = mySerial.read();
      count2 = count2 + count1; //Read the serial data and store it
      Serial.print(" count1=");
      Serial.println(count1);
      Serial.println(count2);
      continue;
    }
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
      continue;
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
      continue;
    }
    break;
  }

  //lcd.clear();
  card = "xxxxxxxx";
  point = -1;
  http.begin(client, "http://192.168.43.35/test/designv7.php?ToCo_id=" + ToCo_id + "&gas=" + gas + "&count1=" + count1 + "&water=" + water + "&area=" + area + "&compartment=" + compartment + "&point=" + point + "&card=" + card);
  delay(500);
  int httpCode = http.GET();
  Serial.println(httpCode);
  http.end();
  Serial.println("next");
  card = "";
  while (digitalRead(errorinterrupt) == HIGH) {
    while (mySerial.available()) {
      char k = mySerial.read();
    }
    card = "";
  }
  while (!mySerial.available()) {
  }
  mySerial.readBytes(id, 1); //Read the serial data and store it
  Serial.print(" id=");
  Serial.println(id);

  if (id[0] == 'P') {
    while (!mySerial.available()) {
    }
    //    lcd.clear();
    point = mySerial.read(); //Read the serial data and store it
    Serial.print(" points=");
    Serial.println(point);
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
    Serial.print("card=");
    Serial.println(card);

    card.trim();
    card.replace(" ", ".");
    Serial.println(card);

    http.begin(client, "http://192.168.43.35/test/designv7.php?ToCo_id=" + ToCo_id + "&gas=" + gas + "&count1=" + count1 + "&water=" + water + "&area=" + area + "&compartment=" + compartment + "&point=" + point + "&card=" + card);
    httpCode = http.GET();
    Serial.println(httpCode);
    http.end();
    //delay(50);
    //lcd.clear();
    while (WiFi.status() != WL_CONNECTED) {
      digitalWrite(D2, LOW);
      digitalWrite(D8, LOW);
    }
    delay(1000);
    //lcd.clear();



  }

}


//////thumbsup
