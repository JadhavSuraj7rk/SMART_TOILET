#include<SoftwareSerial.h> //Included SoftwareSerial Library
//Started mySerial SoftwareSerial
SoftwareSerial mySerial(D3,D4);
char id[1];
void setup() {
  // put your setup code here, to run once:
  mySerial.begin(9600);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 while(!mySerial.available()){
    }
  mySerial.readBytes(id,1); //Read the serial data and store it
  Serial.print(" id=");
  Serial.println(id);
  delay(100);
  while(mySerial.available()<2){
    }  
    int measure;
    byte b1  = mySerial.read();
    byte b2 =  mySerial.read();
    measure = ((int)b1) * 256 + b2;
    Serial.print("measure: ");
    Serial.println(measure);
 
}
