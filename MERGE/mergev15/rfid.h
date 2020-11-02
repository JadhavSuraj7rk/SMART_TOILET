#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include "RTClib.h"
#define SS_PIN 10
#define RST_PIN 9
#define LED_G 7 //define green LED pin
int points,access1;
int str_len;
char sweepid[12];
String content;
RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int minu=0,sinu=0;
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.


void rfidsetup() 
{
  Serial.begin(9600);
  //Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
 
  pinMode(LED_G, OUTPUT);
    pinMode(8, OUTPUT);
  //Serial.println("Put your card to the reader...");
  //Serial.println();

}



void rfidloop () {
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
     
    
  }
 // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  
  DateTime now = rtc.now();
  DateTime future (now + TimeSpan(0,0,2,0));
  sinu=future.minute();
  Serial.print("future=");
  Serial.println(sinu);
  minu=now.minute();
    
  // Look for new cards
  while ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    DateTime now = rtc.now(); 
     Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    minu=now.minute();
    access1=digitalRead(4);
    while(access1==0){
    access1=digitalRead(4);
    digitalWrite(7, LOW);
    }
    digitalWrite(7, HIGH);
    if(minu==sinu){
      break;
    }
    delay(1000);
  }
  // Select one of the cards
  while( ! mfrc522.PICC_ReadCardSerial()) 
  {
    if(minu==sinu){
      break;
    }
   Serial.print("..");
  }
  
  if(minu==sinu){
    Serial.println("Water wash");
    digitalWrite(8,HIGH);
    delay(5000);
    digitalWrite(8,LOW);
    digitalWrite(7,LOW);
    content=" XX XX XX XX";
    points=sinu-minu;
  }
  else{
  //Show UID on serial monitor
  Serial.print("UID tag :");
  
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  //if (content.substring(1) == "ED D6 D6 73") //change here the UID of the card/cards that you want to give access
  
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    Serial.println(content);
    points=sinu-minu;
    Serial.println(sinu);
    Serial.println(minu);
    Serial.println(points);
    digitalWrite(7, LOW);

    }
    
  
    
   
    //delay(300);
    
      
    
   }
   //delay(500);
  
