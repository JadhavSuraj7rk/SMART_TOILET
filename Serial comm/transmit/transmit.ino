#include<SoftwareSerial.h> //Included SoftwareSerial Library
//Started mySerial SoftwareSerial
SoftwareSerial mySerial(10,11);
int gas=45;
int count1=12;
int water=255;
char id[1]="A";

void setup() {
  //Serial mySerial Begin at 9600 Baud
  mySerial.begin(9600);
}

void loop() {
  mySerial.write(id,1);
  delay(1000);
  mySerial.write(gas);
  delay(1000);
  mySerial.write(count1);
  delay(1000);
  mySerial.write(water);
  delay(1000);
}
