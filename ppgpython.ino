/*
  ProtoCentral MAX86150 Breakout Board

  https://github.com/protocentral/protocentral_max86150

  Written by: Ashwin Whitchurch (support@protocentral.com)

  Outputs PPG values from the Red LED.

  Place your finger on the two ECG pads to see your ECG waveform in realtime

  Hardware Connections (Breakout
  board to Arduino):
  -5V = 5V
  -GND = GND
  -SDA = A4 (or SDA)
  -SCL = A5 (or SCL)
  -INT = Not connected

  See the output on the Arduino Plotter utlity by:
  1) Program the code to your Arduino
  2) Place your left hand finger and the right hand finger on the two ECG electrode pads
  3) In the Arduino IDE, Open Tools->'Serial Plotter'
  4) Make sure the drop down is set to 115200 baud
  5) See your ECG and heartbeat

  This code is released under the [MIT License](http://opensource.org/licenses/MIT).
*/
#include <WiFi.h>
 
const char* ssid = "tiger";
const char* password =  "anuragta";
#include <Wire.h>
#include "max86150.h"

const uint16_t port = 8090;
const char * host = "192.168.130.24" ;//192.168.43.178";//192.168.43.204"  192.168.130.24;

MAX86150 max86150Sensor;

#define debug Serial      //Uncomment this line if you're using an Uno or ESP
//#define debug SerialUSB //Uncomment this line if you're using a SAMD21

uint16_t ppgunsigned16;

uint16_t zerv;

void setup()
{
    debug.begin(115200);
    debug.println("MAX86150 Basic Readings Example");

    // Initialize sensor
    if (max86150Sensor.begin(Wire, I2C_SPEED_FAST) == false)
    {
        debug.println("MAX86150 was not found. Please check wiring/power. ");
        while (1);
    }

    max86150Sensor.setup(); //Configure sensor

   
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }
 
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
 
}

void loop()
{
    if(max86150Sensor.check()>0)
    {
      zerv = (uint16_t) (max86150Sensor.getFIFORed()>>2);
      //  debug.println(ppgunsigned16);
       //zerv = (int16_t) (max86150Sensor.getFIFOECG()>>2);
       delay(10);
//       onev = (int16_t) (max86150Sensor.getFIFOECG()>>2);
//       delay(10);
//       twov = (int16_t) (max86150Sensor.getFIFOECG()>>2);
//       delay(10);
//       threev = (int16_t) (max86150Sensor.getFIFOECG()>>2);
////       delay(10);
//       fourv = (int16_t) (max86150Sensor.getFIFOECG()>>2);
////       delay(10);
//       fivev = (int16_t) (max86150Sensor.getFIFOECG()>>2);
////       delay(10);
//       sixv = (int16_t) (max86150Sensor.getFIFOECG()>>2);
////       delay(10);
//       sevv = (int16_t) (max86150Sensor.getFIFOECG()>>2);
////       delay(10);
//       eigv = (int16_t) (max86150Sensor.getFIFOECG()>>2);
////       delay(10);
//       ninv = (int16_t) (max86150Sensor.getFIFOECG()>>2);
//        //debug.println(ecgsigned16);
        
    }
String zer= (String)zerv;
//String one= (String)onev;
//String two= (String)twov;
//String three= (String)threev;
//String four= (String)fourv;
//String five= (String)fivev;
//String six= (String)sixv;
//String sev= (String)sevv;
//String eig= (String)eigv;
//String nin= (String)ninv;

    WiFiClient client;
 
    if (!client.connect(host, port)) {
 
        Serial.println("Connection to host failed");
 
        delay(1000);
        return;
    }
 
    Serial.println("Connected to server successful!");
 
    //client.print("Hello from ESP32!");
    client.print(zer);   //+",");//+one+","+two+","+three+","+four+","+five+","+six+","+sev+","+eig+","+nin);
 
    Serial.println("Disconnecting...");
    client.stop();
 
    delay(10);
}
