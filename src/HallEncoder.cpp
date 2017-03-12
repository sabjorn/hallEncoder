#include "hallencoder.h"

#define TIMEOUT_DEFAULT 1000

#define TOTALTICKS 1000

HallEncoder::HallEncoder(uint8_t pin1, uint8_t pin2, 
uint16_t steps, unsigned long timeout){
    pin1_ = pin1;
    pin2_ = pin2;
    steps_ = steps;
    timeout_ = timeout;

    sens1_ = 0;
    sens2_ = 0;
    sens1_old_ = 0;
    sens2_old_ = 0;
    
    direction_ = 0;
    rpm_ = 0;
    timeDiff_ = 0;
    oldTime_ = 0;
}

void HallEncoder::begin(){
    pinMode(pin1_, INPUT);
    pinMode(pin2_, INPUT);
}

void HallEncoder::update(){
    // must be called every loop() in main.

    //@note may require changing to direct port access
    // or interrupts for optimization.
    sens1_ = digitalRead(pin1_);
    sens2_ = digitalRead(pin2_);

    parseEncoder_();

    sens1_old_ = sens1_;
    sens2_old_ = sens2_;
}

int8_t HallEncoder::getDirection(){
    return direction_;
}

uint16_t HallEncoder::getRPM(){
    return rpm_;
}

uint16_t HallEncoder::getPosition(){
    return position_;
}

unsigned long HallEncoder::getTime(){
    return timeDiff_;
}

void HallEncoder::parseEncoder_(){
    unsigned long now = millis(); //microseconds?

    // increment position
    int temp = 0;
    if(sens1_old_ && sens2_old_){
        if(!sens1_ && sens2_) temp = 1;
        if(sens1_ && !sens2_) temp = -1;
    }else if(!sens1_old_ && sens2_old_){
        if(!sens1_ && !sens2_) temp = 1;
        if(sens1_ && sens2_) temp = -1;
    }else if(!sens1_old_ && !sens2_old_){
        if(sens1_ && !sens2_) temp = 1;
        if(!sens1_ && sens2_) temp = -1;
    }else if(sens1_old_ && !sens2_old_){
        if(sens1_ && sens2_) temp = 1;
        if(!sens1_ && !sens2_) temp = -1;
    }
    position_ += temp;    
    position_ = position_ % (4 * steps_); //4 states per step
    
    // RPM is calculated as average of time between steps 
    if(temp){
        // only take time measurement once every 4 states
        if( !(position_ % 4) ){
            timeDiff_ = now - oldTime_;
            oldTime_ = now;
            calculateRPM_();
        }
    }

    // @note: this may be wrong.
    //direction change check
    if (direction_ != temp)
        rpm_ = 0;
    direction_ = temp;

    //timeout check
    if ((now - oldTime_) > timeout_){
        rpm_ = 0;
        //direction_ = 0;
    }
}

void HallEncoder::calculateRPM_(){
    // probably need to average the RPM over time
    float temp = 1 / (timeDiff_ * steps_ * 1.0) * 60000;
    rpm_ = (rpm_ + temp) / 2.; // average RPM between two samples.
}