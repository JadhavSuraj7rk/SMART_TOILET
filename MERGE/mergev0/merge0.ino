#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>  
#include<SoftwareSerial.h>
SoftwareSerial mySerial(D3,D4);
int gas,count1,dirt,points;
String water,dirty;
const char *ssid = "android ap";  //ENTER YOUR WIFI SETTINGS
const char *password = "androidap"; 

int watery,i;
char id[1];
String card;
char sweepid[13];
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(D2,OUTPUT);
  delay(1000);
  WiFi.mode(WIFI_OFF);  // Wifi mode off
  delay(1000);
  WiFi.mode(WIFI_STA);  // Wifi station mode
  delay(1000);
  WiFi.begin(ssid,password);  // Connecting to Wifi
  Serial.println("Connecting");
  while(WiFi.status()!=WL_CONNECTED)  // Checking if connected
   {
    delay(500);
    Serial.print(".");
   }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  
}

void loop() {
  digitalWrite(D2,HIGH);
  HTTPClient http; //Declare object of class HTTPClient
  WiFiClient client;
  while(!mySerial.available()){
    }
  for(i=1;i<5;i++){
    
  while(!mySerial.available()){
    }
    
  mySerial.readBytes(id,1); //Read the serial data and store it
  Serial.print(" id=");
  Serial.println(id);
  if(id[0]=='E'){
    while(!mySerial.available()){
     }
  int e1= mySerial.read();
      if(e1==0){
      Serial.println("Error in gas");
      
      //delay(100);
      }
      else if(e1==1){
        Serial.println("Error in water");
      }
  else if(e1==2){
        Serial.println("no error");
      }
  }
 if(id[0]=='G'){
  while(mySerial.available()<2){
    }  
    byte b1  = mySerial.read();
    byte b2 =  mySerial.read();
    gas = ((int)b1) * 256 + b2;
    Serial.print("gas: ");
    Serial.println(gas);
  }
 
  if(id[0]=='C'){
  while(!mySerial.available()){
    }
  count1=mySerial.read(); //Read the serial data and store it
  Serial.print(" count1=");
  Serial.println(count1);
 }
  if(id[0]=='W'){
   while(!mySerial.available()){
    }
  watery=mySerial.read(); //Read the serial data and store it
  Serial.print(" water=");
  
  if(watery==1){
    water="YES";
    Serial.println(water);
  }
  else{
    water="NO";
    Serial.println(water);
  }
 }
if(id[0]=='P'){
   while(!mySerial.available()){
    }
int   point=mySerial.read(); //Read the serial data and store it
   Serial.print(" points=");
   Serial.println(point);
   while(!mySerial.available()){
   }
   mySerial.readBytes(sweepid,12);
   for(i=0;i<12;i++){
   card.concat(sweepid[i]);
   }
   Serial.print("card=");
   Serial.println(card);
   card.trim();
   card.replace(" ",".");
   Serial.println(card);
}
  // put your main code here, to run repeatedly:

}
}
