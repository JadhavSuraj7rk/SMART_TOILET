#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>   //esp files
#include<SoftwareSerial.h> //Included SoftwareSerial Library
SoftwareSerial mySerial(D3,D4);
const char *ssid = "android ap";  //ENTER YOUR WIFI SETTINGS
const char *password = "androidap"; 
String ToCo_id="TOILET-1";
int compartment=2;
String area="VIKHROLI";
String water;
int gas,count1,point;
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
  for(i=1;i<4;i++){
  while(!mySerial.available()){
    }
  mySerial.readBytes(id,1); //Read the serial data and store it
  Serial.print(" id=");
  Serial.println(id);
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
}
  card="xxxxxxxx";
  point=-1;
   http.begin(client,"http://192.168.43.35/test/designv3.php?ToCo_id="+ToCo_id+"&gas="+gas+"&count1="+count1+"&water="+water+"&area="+area+"&compartment="+compartment+"&point="+point+"&card="+card);
   delay(500);
   int httpCode = http.GET();
   Serial.println(httpCode);
   http.end();
   Serial.println("next");
   card=""; 
   delay(1000);
   while(!mySerial.available()){
    }
   mySerial.readBytes(id,1); //Read the serial data and store it
   Serial.print(" id=");
   Serial.println(id);
   if(id[0]=='P'){
   while(!mySerial.available()){
    }
   point=mySerial.read(); //Read the serial data and store it
   Serial.print(" points=");
   Serial.println(point);
   while(!mySerial.available()){
   }
   mySerial.readBytes(sweepid,13);
   for(i=0;i<13;i++){
   card.concat(sweepid[i]);
   }
   Serial.print("card=");
   Serial.println(card);
   card.trim();
   card.replace(" ",".");
   Serial.println(card);
   http.begin(client,"http://192.168.43.35/test/designv3.php?ToCo_id="+ToCo_id+"&gas="+gas+"&count1="+count1+"&water="+water+"&area="+area+"&compartment="+compartment+"&point="+point+"&card="+card);
   httpCode = http.GET();
   Serial.println(httpCode);
   http.end();
   delay(1000);
    while(WiFi.status()!=WL_CONNECTED) {
    digitalWrite(D2,LOW);
 }
 delay(1000);

}
}
