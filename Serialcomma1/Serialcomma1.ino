char id[6];
int i;
String card = "";
#include<SoftwareSerial.h> //Included SoftwareSerial Library
//Started mySerial SoftwareSerial
SoftwareSerial mySerial(D3,D4);

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 mySerial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(i=0;i<6;i++){
  while(!mySerial.available()){
  }
  //mySerial.readBytes(id,i); //Read the serial data and store it
  id[i] = mySerial.read();
  //Serial.print(" id=");
 // Serial.println(id);
  card.concat(id[i]);
  }
  Serial.print("card=");
  Serial.println(card);
  card="";
}
