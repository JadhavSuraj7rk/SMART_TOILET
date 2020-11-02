int gas,count1;
int water;
char id[2];
void setup() {
  //Serial Begin at 9600 Baud 
  Serial.begin(9600);
  pinMode(D2,OUTPUT);
  
}

void loop() {
  digitalWrite(D2,HIGH);
  while(!Serial.available()){
    }
  Serial.readBytes(id,1); //Read the serial data and store it
  Serial.print(" id=");
  Serial.println(id);
 if(id[0]=='G'){
  while(!Serial.available()){
    }
  
  gas=Serial.read(); //Read the serial data and store it
  Serial.print(" gas=");
  Serial.println(gas);
 }
  if(id[0]=='C'){
  while(!Serial.available()){
    }
  count1=Serial.read(); //Read the serial data and store it
  Serial.print(" count1=");
  Serial.println(count1);
 }
  if(id[0]=='W'){
   while(!Serial.available()){
    }
  water=Serial.read(); //Read the serial data and store it
  Serial.print(" water=");
  Serial.println(water);
 }
  
 // delay(1000);
}
