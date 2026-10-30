#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor {
    public: 
        Motor(int ena1, int drive1, int drive2) : 
        _drivePin1(drive1), _drivePin2(drive2), _enable(ena1) {

            // Set pinmodes in constructor (initializer list)
            pinMode(_enable, OUTPUT);
            pinMode(_drivePin1, OUTPUT);
            pinMode(_drivePin2, OUTPUT);

        }

        void SetSpeed(int motorSpeed) {

            // Give Motor speed on [0, 255]
            _motorSpeed = motorSpeed;

        }

        void DriveMotor(bool reverse=false) {

            // Forward State
            if (reverse == false) {

                digitalWrite(_drivePin1, LOW);
				digitalWrite(_drivePin2, HIGH);
				analogWrite(_enable,_motorSpeed);

            // Reverse State
            } else {

                digitalWrite(_drivePin1, HIGH);
				digitalWrite(_drivePin2, LOW);
				analogWrite(_enable,_motorSpeed);

            }

            return;

        }

        void DriveMotorJoy(int joyInput) {

            // Joy input is on the [0, 1023]

            int speedVal = map(joyInput, 0, 1023, -255, 255);

            if (speedVal < (-1) *_joyDeadzone) {
                this -> SetSpeed(abs(speedVal));

                this -> DriveMotor(true);

            } else if (speedVal > _joyDeadzone) {
                this -> SetSpeed(speedVal);
                this -> DriveMotor();

            } else {
                this -> SetSpeed(0);
                this -> DriveMotor();
            }

        }   

        void stopMotor() {

            this -> SetSpeed(0);
            this -> DriveMotor();
        }


    private:

        int _drivePin1;
        int _drivePin2;

        int _enable;

        int _motorSpeed = 0;

        int _joyDeadzone = 3;

};


#endif // MOTOR_H
