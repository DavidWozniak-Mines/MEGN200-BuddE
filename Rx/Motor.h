#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include <Servo.h> // For control over servo-type motors

class Motor {
    public: 

        // Contructor for the motor class, set up to take in servo type motors
        Motor(Servo& SERVO, bool INVERT) : 
        _servo(SERVO) { // Initialize the reference to the servo

            _invert = INVERT; // Set whether or not the motor is inverted (to account for mirrored servos)
        }

        // Set the speed of the motor to a desired value
        void SetSpeed(int motorSpeed) {
            
            // Give motorSpeed on [-255, 255]
            _motorSpeed = motorSpeed;

            // Remap to continuous servo
            _motorSpeed = map(_motorSpeed, -255, 255, 0, 180);


        }

        // Function to drive the motor, must be called continually for any effect
        void DriveMotor() {


            // if the motor is inverted, remap to spectrum opposite values
            if (_invert) {
                _motorSpeed = map(_motorSpeed, 0, 180, 180, 0);
            }

            _servo.write(_motorSpeed); // Write the current speed of the motor to the servo

            return;

        }

        // Allows continous control of a motor based soley on joystick input value
        void DriveMotorJoy(int joyInput) {

            // Joy input is on the [0, 1023]

            int speedVal = map(joyInput, 0, 1023, -255, 255); // Remap joystick value to be essentially pwm output values

            // Backward Case
            if (speedVal < (-1) *_joyDeadzone) {
                this -> SetSpeed(speedVal); // Set the motor speed to speedval
                this -> DriveMotor(); // Drive the motor on this new speedval

            // Forward Case
            } else if (speedVal > _joyDeadzone) {
                this -> SetSpeed(speedVal);
                this -> DriveMotor();

            // Zero Case
            } else {
                this -> SetSpeed(0);
                this -> DriveMotor();
            }

        }   

        // Function to completely stop the motor, will spin continuously otherwise
        void stopMotor() {

            this -> SetSpeed(0); // Set the speed of the motor to zero
            this -> DriveMotor(); // Drive the motor at speed zero to stop it
        }


    private:

        Servo& _servo; // Reference to the servo motor the class object wraps

        int _motorSpeed = 0; // The speed of the motor, default to zero

        int _joyDeadzone = 8; // The +- deadzone on the joystick, used to prevent movement when joystick is essentialy at zero

        bool _invert; // Keeps track of whether the motor should be inverted. Used to handle mirrored motor configs

};


#endif // MOTOR_H
