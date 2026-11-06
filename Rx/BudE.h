#ifndef BUD_E_H
#define BUD_E_H

#include <Arduino.h>

#include "Motor.h"  // For control of each wheel
#include "Ultrasonic.h" // For use of ultrasonic sensing


class BudE {

    public:

        // Constructor to initialize each motor reference as well as the ultrasonic sensor
        BudE(Motor& LEFT_WHEEL, Motor& RIGHT_WHEEL, Ultrasonic& DISTANCE) :
        _leftWheel(LEFT_WHEEL), _rightWheel(RIGHT_WHEEL), _distanceSensor(DISTANCE) {
            // No code needed in the body of the constructor, all is done in the initializer
        }

        // Mode to enable human-controlled driving, inputs for two joystick values
        void ManualDrive(int leftSpeed, int rightSpeed) {

                _leftWheel.DriveMotorJoy(leftSpeed); // Drive each wheel seperately using their joystick values
                _rightWheel.DriveMotorJoy(rightSpeed);

        }


        // Mode to enable autonoums control of the ASAN test course
        void AutonDrive() {

            float forwardThreshold = 25; // Thresold for breakpoint distance

            unsigned long turn = 850;   // Timing for turn values
            unsigned long forwardDrive2 = 500; // Timing for post turn straight

            unsigned long startTime = millis();


            // Drive forward until turn breakpoint is reached, then initiate turn sequence
            while (_distanceSensor.readDistanceCM() > forwardThreshold) {

                Serial.print(_distanceSensor.readDistanceCM()); // Print values for logging purposes

                _leftWheel.DriveMotorJoy(0);
                _rightWheel.DriveMotorJoy(0);
            }


            // Turn Sequence Starts Here
            startTime = millis();

            while (millis() - startTime < turn) {

                _leftWheel.DriveMotorJoy(450);
                _rightWheel.DriveMotorJoy(0);
            }

            startTime = millis();

            while (millis() - startTime < turn) {

                _leftWheel.DriveMotorJoy(0);
                _rightWheel.DriveMotorJoy(450);
            }

            startTime = millis();

            // Turn sequence ends here

            // Drive forward until the ending square is reached
            while (millis() - startTime < forwardDrive2) {

                _leftWheel.DriveMotorJoy(0);
                _rightWheel.DriveMotorJoy(0);
            }

            // Stop all motor motion once auto finishes
            _leftWheel.stopMotor();
            _rightWheel.stopMotor();

            return;
        }


        // Purely for logging purposes, does not impact robot function
        void ultrasonic() {

            // Takes in a prints ultrasonic values
            double testVal = _distanceSensor.readDistanceCM();

            Serial.println(testVal);
        }

    private:

        Ultrasonic& _distanceSensor; // Reference to the ultrasonic

        Motor& _leftWheel; // Reference to the left wheel motor
        Motor& _rightWheel; // Reference to the right wheel motor

};

#endif // BUD_E_H

