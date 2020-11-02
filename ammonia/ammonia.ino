#include <LiquidCrystal_I2C.h>
//#include "MQ135.h"
//#include "MQ7.h"
LiquidCrystal_I2C lcd(0x27, 16, 2);
//MQ135 mq135(A0,5.0);
//MQ7 mq7(A3, 5.0);

void setup() {
    Serial.begin(9600);
    lcd.begin(); 
    lcd.backlight();
}

void loop() {
  //float x=mq135.getPPM();
//  float ppm = mq7.getPPM();
    Serial.println(analogRead(A0));
    //lcd.setCursor(0,0);
    //lcd.print("NH3=");
    //lcd.print(x);
    lcd.setCursor(0,0);
    lcd.print(analogRead(A0));
  //  lcd.setCursor(0,1);
   // lcd.print("CO=");
//    lcd.print(ppm);
  //  lcd.setCursor(11,1);
    //lcd.print(analogRead(A3));
    delay(500);
    lcd.clear();
   
}
