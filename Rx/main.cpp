#include <Arduino.h>

#include "Motor.h" // For control over robots motors
#include "WifiPort3.h" // For wifi connection between R4s
#include "Joystick.h" // To upack joystick objects
#include "Ultrasonic.h" // To enable ultrasonic sensing
#include "BudE.h" // For the robots control logic


// A structure, similar to our servo and stepper motors, but this one conatins variables to be transmitted
// Any variable you want to transmit/recieve must be initalized in the DataPacket structure
struct DataPacket {
  int AnalogCheck;  //an initial check to show successful transmission

  Joystick joy1;
  Joystick joy2;

  bool button1;
  bool button2;

};

// Create dataPacket Object
DataPacket data;

// Create wifiSerial Object
WifiPort<DataPacket> WifiSerial;

Servo leftServo; // Initialize left servo
Servo rightServo; // Initialize right servo

Motor left(leftServo, true); // Initialize left motor, inverted
Motor right(rightServo, false); // Initialize right motor, noninverted

// Initialize ultrasonic sensor on correct pins for the BudDE
int echo = 4; 
int trigger = 3;

Ultrasonic ultrasonic(trigger, echo);


void setup() {
  //DONT USE PIN13 FOR ANY SENSOR OR ACTUATORS

  Serial.begin(115200);  //preferred transmission rate for Arduino UNO R4
  //you need to update in your serial monitor --> select it in your Serial Monitor

  matrix.begin();//3.h
  //initializes the ArduinoLEDMatrix CLASS of instance name 'matrix'
  //class creation and utiliziation in the header file --> will be used to turn on one LED when connection is established

  WifiSerial.begin("ssid_GROUP_64_WIFI", "password_PASSWORD", WifiPortType::Receiver);

  ultrasonic.begin(); // Start up the ultrasonic sensor

  leftServo.attach(13); // Set the left motor to pin 13
  rightServo.attach(12); // Set the right motor to pin 12

}

BudE budE(left, right, ultrasonic); // Initialize the BuddE robot using the above motors/ultrasonic

void loop() {

  while (!(WifiSerial.getPortType() == WifiPortType::Receiver && WifiSerial.checkForData())) {
    
    // Do Nothing if Wifi is Not Connected

  } 

    data = WifiSerial.getData(); //received and unpack data structure

    budE.ManualDrive(data.joy1.y, data.joy2.y); // If wifi is connect default the robot to manual drive

    if (data.joy1.sw == LOW) { // If the joystick button is pressed, initiate the auton mode

        budE.AutonDrive();

    }


  delay(1); // account for WiFi transmission overhead

}

