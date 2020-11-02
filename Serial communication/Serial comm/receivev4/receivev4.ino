#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>   //esp files
const char *ssid = "android ap";  //ENTER YOUR WIFI SETTINGS
const char *password = "androidap"; 
int gas,count1;
int water;
char id[2];
void setup() {
  //Serial Begin at 9600 Baud 
  Serial.begin(9600);
  pinMode(D2,OUTPUT);
  delay(1000);
  Serial.begin(9600);
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
  while(!Serial.available()){
    }
  Serial.readBytes(id,1); //Read the serial data and store it
  Serial.print(" id=");
  Serial.println(id);
 if(id[0]=='G'){
  while(!Serial.available()){
    }
  
  gas=Serial.read(); //Read the serial data and store it
  Serial.print(" gas=");
  Serial.println(gas);
 }
  if(id[0]=='C'){
  while(!Serial.available()){
    }
  count1=Serial.read(); //Read the serial data and store it
  Serial.print(" count1=");
  Serial.println(count1);
 }
  if(id[0]=='W'){
   while(!Serial.available()){
    }
  water=Serial.read(); //Read the serial data and store it
  Serial.print(" water=");
  Serial.println(water);
 }
  while(WiFi.status()!=WL_CONNECTED) {
    digitalWrite(D2,LOW);
  }
 // delay(1000);
}
