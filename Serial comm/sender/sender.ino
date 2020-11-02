
#include<SoftwareSerial.h> //Included SoftwareSerial Library
//Started mySerial SoftwareSerial
SoftwareSerial mySerial(10,11);
int x=800;
char id[1];

void setup() {
  // put your setup code here, to run once:
 mySerial.begin(9600);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  id[0]='G';
  mySerial.write(id,1);
  delay(500);
  uint8_t LSB = x;
  uint8_t MSB = x >> 8;
  mySerial.write(MSB);
  mySerial.write(LSB);
  delay(100);
}
