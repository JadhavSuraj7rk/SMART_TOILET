#include<SoftwareSerial.h> //Included SoftwareSerial Library
//Started mySerial SoftwareSerial
SoftwareSerial mySerial(6, 7);
String str= "Hello";
int str_len = str.length() + 1;
char id[6];
int i;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
mySerial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  str.toCharArray(id, str_len);
 for(i=0;i<6;i++){
 Serial.print(id[i]);
 mySerial.write(id[i]);
 delay(1000);
}
Serial.println(id);
}
