#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>   //esp files
const char *ssid = "android ap";  //ENTER YOUR WIFI SETTINGS
const char *password = "androidap";
#define A D2
#define B D1
#define C D0
#define ANALOGPIN A0
int gas = 0;
const int trigPin = D5;
const int echoPin = D6;
//LiquidCrystal_I2C lcd(0x27, 16, 2);
long duration;
int distance;
int counter, count1;
int current = 0;
int water;
void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(9600);
  WiFi.mode(WIFI_OFF);  // Wifi mode off
  delay(1000);
  WiFi.mode(WIFI_STA);  // Wifi station mode
  delay(1000);
  WiFi.begin(ssid, password); // Connecting to Wifi
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) // Checking if connected
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  HTTPClient http;    //Declare object of class HTTPClient
  WiFiClient client;  //Declare object of class WifiClient

  String ToCo_id;
  // int gas,count1,water;
  ToCo_id = "T2004";
  int fn = dist();
  if (fn == 1) {
    while (fn == 1) {
      counter++;
      fn = dist();
      delay(1000);
    }
  }
  else {
    if (counter > 2) {
      count1 = count1 + 1;
      counter = 0;
      Serial.print("count");
      Serial.println(count1);
      Serial.print("ppm=");
      int gaslevel=mq135();
      Serial.print("taki=");
      int waterlevel=level();
      http.begin(client, "http://192.168.43.35/test/designv1.php?ToCo_id=" + ToCo_id + "&gaslevel=" + gaslevel + "&count1=" + count1 + "&waterlevel=" + waterlevel); //Specify request destination
      int httpCode = http.GET();
      Serial.println(httpCode);   //Print HTTP return code
      http.end();  //Close connection
      delay(3000);

    }
  }
  delay(1000);
}

//////distance measurement
int dist() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance = duration * 0.034 / 2;

  // Prints the distance on the Serial Monitor
  //Serial.print("Distance: ");
  //Serial.println(distance);
  //lcd.setCursor(0,1);
  //lcd.print(distance);
  //lcd.clear();
  delay(100);
  if (distance <= 50)
  {
    current = 1;
  }
  else {
    current = 0;
  }
  return current;
}


////////air quality
int mq135()
{
  digitalWrite(A, 0);
  digitalWrite(B, 0);
  digitalWrite(C, 0);
  gas = analogRead(ANALOGPIN);
  Serial.println(gas);
  //float ppm = gasSensor.getPPM();
  delay(1000);
  //digitalWrite(13,HIGH);
  //Serial.print("CO2 ppm gas : ");
  return gas;
}


////////waterlevel
int level()
{
  digitalWrite(A, 0);
  digitalWrite(B, 0);
  digitalWrite(C, 1);
  water = analogRead(ANALOGPIN);
  return water;
}
