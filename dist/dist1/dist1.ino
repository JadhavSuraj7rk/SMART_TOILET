// defines pins numbers
#include <LiquidCrystal_I2C.h>
const int trigPin = 9;
const int echoPin = 10;
LiquidCrystal_I2C lcd(0x27, 16, 2);
// defines variables
long duration;
int distance;
int counter,count;
int current=0;
void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
lcd.begin();
}

void loop() {
  lcd.clear();
  
   int fn=dist();
  if(fn==1){
  while(fn==1){
    counter++;
    fn=dist();
    delay(1000);
  }
  }
else{
if(counter>2){
  count=count+1;
  counter=0;
  Serial.print("count");
  Serial.println(count);
  lcd.setCursor(0,0);
  lcd.print(count);
}
}
delay(1000);
}
int dist(){
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
distance= duration*0.034/2;

// Prints the distance on the Serial Monitor
//Serial.print("Distance: ");
Serial.println(distance);
lcd.setCursor(0,1);
  lcd.print(distance);
  //lcd.clear();
delay(100);
if(distance<=100)
{
current=1;
}
else {
  current=0;
}
return current;
}
