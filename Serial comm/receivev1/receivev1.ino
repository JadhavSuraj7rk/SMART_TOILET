int gas,count1;
int water;
char id[2];
void setup() {
  //Serial Begin at 9600 Baud 
  Serial.begin(9600);
}

void loop() {
  while(!Serial.available()){
    }
  Serial.readBytes(id,1); //Read the serial data and store it
  Serial.print(" id=");
  Serial.println(id);
  switch ('id'){
  case 'G':
            while(!Serial.available()){
          }
          gas=Serial.read(); //Read the serial data and store it
          Serial.print(" gas=");
          Serial.println(gas);
          break;
  case 'C':        
          while(!Serial.available()){
          }
          count1=Serial.read(); //Read the serial data and store it
          Serial.print(" count1=");
          Serial.println(count1);
          break;
 case 'W':
         while(!Serial.available()){
         }
         water=Serial.read(); //Read the serial data and store it
         Serial.print(" water=");
         Serial.println(water);
         break;
  }

  delay(1000);
}
