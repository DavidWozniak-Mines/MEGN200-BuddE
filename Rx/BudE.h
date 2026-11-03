#ifndef BUD_E_H
#define BUD_E_H

#include <Arduino.h>

#include "Motor.h"
#include "Ultrasonic.h"

class BudE {

    public:

        BudE(Motor& LEFT_WHEEL, Motor& RIGHT_WHEEL, Ultrasonic& DISTANCE) :
        _leftWheel(LEFT_WHEEL), _rightWheel(RIGHT_WHEEL), _distanceSensor(DISTANCE) {}

        void ManualDrive(int SPEED, int STEER);

        void AutonDrive();

    private:

        Ultrasonic& _distanceSensor;

        Motor& _leftWheel;
        Motor& _rightWheel;


};

#endif // BUD_E_H