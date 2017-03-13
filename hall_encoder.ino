#include "hallencoder.h"

#define HALL1 2
#define HALL2 3


//debug variables
unsigned long oldTime = 0;
unsigned long delayTime = 1000;


HallEncoder wheel(HALL1, HALL2, 4, 1000);

void setup(){
    Serial.begin(115200);

    wheel.begin();
}

void loop(){
    wheel.update();

    unsigned long now = millis();

    if(now - oldTime > delayTime){
        Serial.print("Time: ");
        Serial.print(wheel.getTime());

        Serial.print("\tRPM: ");
        Serial.print(wheel.getRPM());

        Serial.print("\tDirection: ");
        Serial.print(wheel.getDirection());

        Serial.print("\tPosition: ");
        Serial.println(wheel.getPosition());

        oldTime = now;
    }
}