#include <Arduino.h>
#include <Motor.h>

#include "WifiPort3.h"
#include "Joystick.h"
#include "Ultrasonic.h"


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

Motor motor1(5,4,3);
Motor motor2(9,8,6);

int echo = 13;
int trigger = 12;

Ultrasonic ultrasonic(trigger, echo);

void setup() {
  //DONT USE PIN13 FOR ANY SENSOR OR ACTUATORS

  Serial.begin(115200);  //preferred transmission rate for Arduino UNO R4
  //you need to update in your serial monitor --> select it in your Serial Monitor

  matrix.begin();//3.h
  //initializes the ArduinoLEDMatrix CLASS of instance name 'matrix'
  //class creation and utiliziation in the header file --> will be used to turn on one LED when connection is established

  WifiSerial.begin("ssid_GROUP_64_WIFI", "password_PASSWORD", WifiPortType::Receiver);

  ultrasonic.begin();
}

void loop() {

 
  while (!(WifiSerial.getPortType() == WifiPortType::Receiver && WifiSerial.checkForData())) {
    
    // If connection is lost, info user and wait for connection
    Serial.println("Connection Interuption");
    delay(10);

    // If Connection is lost, stop all motor movement
    motor1.stopMotor();
    motor2.stopMotor();
  } 

    data = WifiSerial.getData();//received and unpack data structure

    motor1.DriveMotorJoy(data.joy1.x);
    motor2.DriveMotorJoy(data.joy2.x);
  

    Serial.print("Ultrasonic Distance: ");
    Serial.println(ultrasonic.readDistanceCM());

  delay(1); // update delay after you get it working to be a smaller number like 10ms to account for WiFi transmission overhead
  
}

