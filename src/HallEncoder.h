#ifndef HALLENCODER_H
#define HALLENCODER_H

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
 #include <pins_arduino.h>
#endif

// namespace motorstates
// {
//   enum Directions{FORWARD, BACKWARD, OFF}; //the states of the piston
// }

class HallEncoder{
    public:
        HallEncoder(uint8_t pin1, uint8_t pin2,  uint16_t steps, unsigned long timeout);
        void begin();
        void update(); //update the scheduler
        
        // api
        int8_t getDirection();
        uint16_t getRPM();
        uint16_t getPosition();
        unsigned long getTime();
        
    private:
        void parseEncoder_();
        void calculateRPM_();

        uint8_t pin1_, pin2_; // Hall Effect pins
        int16_t position_; //current position of rotation
        float rpm_;
        uint16_t steps_; //number of magnets on rotation
        unsigned long timeout_, timeDiff_, oldTime_;
        int8_t direction_;
        bool sens1_, sens2_, sens1_old_, sens2_old_; // encoder measurement states
};

#endif // HALLENCODER_H