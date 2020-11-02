#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
const char *ssid = "Realme 2";  //ENTER YOUR WIFI SETTINGS
const char *password = "siddhesh"; 
const char *host = "192.168.43.35"; 
//String xyz="http://192.168.43.35/test/espphp.php";
const IPAddress server(192,168,43,35);

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(9600);
  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.mode(WIFI_STA);
  delay(1000);
  WiFi.begin(ssid,password);
  Serial.println("Connecting");
  while(WiFi.status()!=WL_CONNECTED)
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
  WiFiClient client;
  if (client.connect(server, 80)) {
    Serial.println(" client connected");
    client.println("client connected");
    delay(5000);
    //return;
  }
 else{
  Serial.println("Not connected to server");
 }
  
  String name1,city,postData ;
  name1="Sid";
  city="Lahore";
  int percentile=random(85,99);
 
  //Post Data
  //postData = "name1=" + name1 + "&city=" + city + "&percentile=" + percentile ;
  
  http.begin(client,"http://192.168.43.92/test/espphp.php?name1="+name1);              //Specify request destination
 // http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
 int httpCode = http.GET();
 // int httpCode = http.POST(postData);   //Send the request
  //String payload = http.getString();    //Get the response payload
 
  Serial.println(httpCode);   //Print HTTP return code
  //Serial.println(payload);    //Print request response payload
 
  http.end();  //Close connection
  Serial.println("yes");
  delay(5000);
}
