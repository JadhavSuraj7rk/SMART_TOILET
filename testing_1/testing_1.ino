#include "MQ135.h"
#include "MQ7.h"
const int AOUTpin=A3;//the AOUT pin of the CO sensor goes into analog pin A0 of the arduino
MQ7 mq7(A3, 5.0);
MQ135 mq135(A0,5.0);

void setup() {
    Serial.begin(9600);
}

void loop() {
    float ppm1= mq135.getPPM());
    float ppm = mq7.getPPM();
    delay(500);
}
