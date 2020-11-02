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
String dirty,water;
int gas,count1,dirt,points;
int watery,i;
char id[1];
char sweepid[12];
String card;
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
 
//Declare object of class HTTPClient
   //Declare object of class WifiClient
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
   data();
   delay(1000);
   point();
   
//  }

     //Close connection
   delay(500);
  
    while(WiFi.status()!=WL_CONNECTED) {
    digitalWrite(D2,LOW);
 }
 delay(1000);
}

void data(){
   HTTPClient http; 
   WiFiClient client; 
  http.begin(client,"http://192.168.43.35/test/designv2.php?ToCo_id="+ToCo_id+"&gas="+gas+"&count1="+count1+"&water="+water+"&dirty="+dirty+"&area="+area+"&compartment="+compartment);              //Specify request destination
   int httpCode = http.GET();
   Serial.println(httpCode);
   http.end(); 
}

void point(){
   HTTPClient http; 
   WiFiClient client;
  while(!mySerial.available()){
    }
  mySerial.readBytes(id,1); //Read the serial data and store it
  Serial.print(" id=");
  Serial.println(id);
  if(id[0]=='P'){
  while(!mySerial.available()){
    }
  points=mySerial.read(); //Read the serial data and store it
  Serial.print(" points=");
  Serial.println(points);
  while(!mySerial.available()){
  }
  mySerial.readBytes(sweepid,13);
   for(i=0;i<12;i++){
   card.concat(sweepid[i]);
   }
   Serial.print("card=");
   Serial.println(card);
   http.begin("http://192.168.43.35/test/credit.php?card="+card+"&points="+points);              //Specify request destination
   int httpCode = http.GET();
   Serial.println(httpCode);
   String pay=http.getString();
   Serial.println(pay);
   http.end();
   card="";
}
}
