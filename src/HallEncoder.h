#ifndef HALLENCODER_H
#define HALLENCODER_H

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
 #include <pins_arduino.h>
#endif

class HallEncoder{
    public:
        HallEncoder(uint8_t pin1, uint8_t pin2,  uint16_t steps, unsigned long timeout);
        void begin();
        void update(); //update the scheduler
        
        // api
        int getDirection();
        float getRPM();
        uint16_t getPosition();
        unsigned long getTime();
        bool getTimeout();
        
    private:
        void parseEncoder_();
        void calculateRPM_();

        uint8_t pin1_, pin2_; // Hall Effect pins
        int16_t position_; //current position of rotation
        float rpm_;
        uint8_t timeout_flag_;
        uint16_t steps_; //number of magnets on rotation
        unsigned long timeout_, timeDiff_, oldTime_;
        int direction_;
        bool sens1_, sens2_, sens1_old_, sens2_old_; // encoder measurement states
};

#endif // HALLENCODER_H