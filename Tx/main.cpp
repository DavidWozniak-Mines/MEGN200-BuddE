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
//ANY Data we want to transmit --> sensor values --> I don't like pins
//Structure MUST BE IDENTICAL in both TX and RX

DataPacket data;//data.AnalogCheck
//structure is a class for just variables

//gloabl vars are outside datapacket

WifiPort<DataPacket> WifiSerial;

// Pin data here
int joy1X = A0;
int joy1Y = A1;

int joy2X = A2;
int joy2Y = A3;

int joy1SW = 3;
int joy2SW = 2;

int button1 = 5;
int button2 = 4;

void setup() {
  //DONT USE PIN13 FOR ANY SENSOR OR ACTUATORS

  Serial.begin(115200);  //preferred transmission rate for Arduino UNO R4
  //you need to update in your serial monitor --> select it in your Serial Monitor
  
  matrix.begin();//3.h
  //initializes the ArduinoLEDMatrix CLASS of instance name 'matrix'
  //class creation and utiliziation in the header file --> will be used to turn on one LED when connection is established

  WifiSerial.begin("ssid_GROUP_64_WIFI", "password_PASSWORD", WifiPortType::Transmitter);

  pinMode(joy1SW, INPUT_PULLUP);
  pinMode(joy2SW, INPUT_PULLUP);

  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);


}

void loop() {

  if (WifiSerial.getPortType() == WifiPortType::Transmitter) {
    WifiSerial.autoReconnect();//try and connect

    //Tx stuff below
    while (true) {
      // Get Joy1 Data
      data.joy1.x = analogRead(joy1X);
      data.joy1.y = analogRead(joy1Y);

      data.joy1.sw = digitalRead(joy1SW);

      // Get Joy2 Data
      data.joy2.x = analogRead(joy2X);
      data.joy2.y = analogRead(joy2Y);

      data.joy2.sw = digitalRead(joy2SW);

      // Get button data
      data.button1 = digitalRead(button1);
      data.button2 = digitalRead(button2);

      //Tx stuff above


      if (!WifiSerial.sendData(data))//check and see if connection is established and data is sent
        Serial.println("Wifi Send Problem");//oh no it didn't send --> it will try and re-connect at the start of the loop

    }

    delay(1); // update delay after you get it working to be a smaller number like 10ms to account for WiFi transmission overhead
  }
  
}
