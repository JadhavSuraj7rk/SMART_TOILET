#include<SoftwareSerial.h> //Included SoftwareSerial Library
//Started mySerial SoftwareSerial
SoftwareSerial mySerial(10,11);

int pin=2;
int access;
 char id[1];
   const int trigPin = 9;
const int echoPin = 8;
long duration;
int distance;
int counter, count1;
int current = 0;
int water;
int gas = 0;

void setup() {
  //Serial mySerial Begin at 9600 Baud
  mySerial.begin(9600);
  Serial.begin(9600);
  pinMode(pin,INPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); 

  
}

void loop() {
  access=digitalRead(pin);
  while(access==0){
     access=digitalRead(pin);
    }
//  id[0]='C';
//  mySerial.write(id,1);
//  delay(100);
//  county();
//  delay(100);  
//  id[0]='G';
//  mySerial.write(id,1);
//  delay(100);
//  gasy();
//  delay(100);
//  
//  id[0]='W';
//  mySerial.write(id,1);
//  delay(100);
//  watery();
//  delay(2000); 
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
      id[0]='C';
      mySerial.write(id,1);
      delay(100);
      Serial.print("count");
      Serial.println(count1);
      mySerial.write(count1);
      delay(100);
      id[0]='G';
      mySerial.write(id,1);
      delay(100);
      Serial.print("ppm=");    
      int gaslevel=mq135();
      Serial.println(gaslevel);
      mySerial.write(gaslevel);
      delay(100);
      id[0]='W';
      mySerial.write(id,1);
      delay(100);
      Serial.print("taki=");
      int waterlevel=level();
      Serial.println(waterlevel); 
      mySerial.write(waterlevel);
      delay(2000);
}
  }
}



/////////
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
 
  gas = analogRead(A0);
  Serial.println(gas);
  //float ppm = gasSensor.getPPM();
 
  //digitalWrite(13,HIGH);
  //Serial.print("CO2 ppm gas : ");
  return gas;
}


////////waterlevel
int level()
{
 
  water = analogRead(A1);
  return water;
}
