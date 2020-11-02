#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>   //esp files
const char *ssid = "Realme 2";  //ENTER YOUR WIFI SETTINGS
const char *password = "siddhesh"; 
const char *host = "192.168.43.35"; 


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

  String name1,city,postData ;
  name1="Sid";
  city="Lahore";
  int percentile=random(85,99);
  
  http.begin(client,"http://192.168.43.92/test/espphp.php?name1="+name1);              //Specify request destination
 // http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
 int httpCode = http.GET();
 
  Serial.println(httpCode);   //Print HTTP return code
 
  http.end();  //Close connection
  Serial.println("yes");
  delay(5000);
}
