#include "hallencoder.h"

#define HALL1 2
#define HALL2 3

uint16_t temp_position = 0;
unsigned long old_time = 0;

HallEncoder wheel(HALL1, HALL2, 4, 1500);

void setup(){
    Serial.begin(115200);
    wheel.begin();
}

void loop(){

    // Call this every loop
    wheel.update();

    // Prints the RPM value
    unsigned long now = millis();
    if (now - old_time > 100){
        Serial.print("RPM: ");
        Serial.println(wheel.getRPM());
        old_time = now;
    }

        // print out values if wheel moves or RPM is set to 0 (from timeout)
    // if(temp_position != wheel.getPosition()){
    //     Serial.print("Time: ");
    //     Serial.print(wheel.getTime());

    //     Serial.print("\tRPM: ");
    //     Serial.print(wheel.getRPM());

    //     Serial.print("\tDirection: ");
    //     Serial.print(wheel.getDirection());

    //     Serial.print("\tPosition: ");
    //     Serial.println(wheel.getPosition());

    //     temp_position = wheel.getPosition();
    // }
        // when TIMEOUT reached, this tells you.
        // TIMEOUT will set RPM to 0.
    // if(wheel.getTimeout()){
    //     Serial.println("TIMEOUT!!!");
    // }
}