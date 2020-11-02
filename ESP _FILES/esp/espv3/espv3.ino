#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>   //esp files
const char *ssid = "android ap";  //ENTER YOUR WIFI SETTINGS
const char *password = "androidap"; 
void setup() {
  // put your setup code here, to run once:
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
  // put your main code here, to run repeatedly:
  HTTPClient http;    //Declare object of class HTTPClient
  WiFiClient client;  //Declare object of class WifiClient

  String ToCo_id;
 // int gas,count1,water;
  ToCo_id="T2003";
  gas=22;
  count1=5;
  water=20;
  
  http.begin(client,"http://192.168.43.35/test/designv1.php?ToCo_id="+ToCo_id+"&gas="+gas+"&count1="+count1+"&water="+water);              //Specify request destination
 int httpCode = http.GET();
  Serial.println(httpCode);   //Print HTTP return code
 http.end();  //Close connection
  delay(3000);
}
