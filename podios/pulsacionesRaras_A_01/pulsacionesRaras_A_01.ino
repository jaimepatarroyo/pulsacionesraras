/*
  Pulsaciones Raras 01
  By: Jaime Patarroyo
  Date: October 1st, 2024
  Based in SparkFun I2C Mux Arduino Library examples by Nathan Seidle 
  and SparkFun Bio Sensor Hub Library examples by Elias Santistevan
*/

#include <Wire.h>

#include <SparkFun_I2C_Mux_Arduino_Library.h>
QWIICMUX myMux;

#include <SparkFun_Bio_Sensor_Hub_Library.h>
// Reset pin and MFIO pin for monitor 1
int resPin1 = 4;
int mfioPin1 = 3;
// Takes address, reset pin, and MFIO pin for monitor 1
SparkFun_Bio_Sensor_Hub bioHub1(resPin1, mfioPin1);
bioData indexFinger;

// Reset pin and MFIO pin for monitor 2
int resPin2 = 6;
int mfioPin2 = 5;
// Takes address, reset pin, and MFIO pin for monitor 2
SparkFun_Bio_Sensor_Hub bioHub2(resPin2, mfioPin2);
bioData middleFinger;


void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Pulsaciones Raras");

  Wire.begin();

  if (myMux.begin() == false) {
    Serial.println("Mux not detected. Freezing...");
    while (1)
      ;
  }
  Serial.println("Mux detected");



  myMux.setPort(0);  // Monitor connected to port 0 in the Mux

  byte currentPortNumber = myMux.getPort();
  Serial.print("CurrentPort: ");
  Serial.println(currentPortNumber);

  Serial.println("Begin scanning for I2C devices");

  int result = bioHub1.begin();
  if (result == 0)  // Zero errors!
    Serial.println("Sensor 1 started!");
  else
    Serial.println("Could not communicate with the sensor 1!");

  Serial.println("Configuring Sensor 1...");
  int error = bioHub1.configBpm(MODE_ONE);  // Configuring just the BPM settings.
  if (error == 0) {                         // Zero errors!
    Serial.println("Sensor 1 configured.");
  } else {
    Serial.println("Error configuring sensor 1.");
    Serial.print("Error: ");
    Serial.println(error);
  }



  myMux.setPort(7);  // Monitor connected to port 7 in the Mux

  currentPortNumber = myMux.getPort();
  Serial.print("CurrentPort: ");
  Serial.println(currentPortNumber);

  Serial.println("Begin scanning for I2C devices");

  result = bioHub2.begin();
  if (result == 0)  // Zero errors!
    Serial.println("Sensor 2 started!");
  else
    Serial.println("Could not communicate with the sensor 2!");

  Serial.println("Configuring Sensor 2...");
  error = bioHub2.configBpm(MODE_ONE);  // Configuring just the BPM settings.
  if (error == 0) {                     // Zero errors!
    Serial.println("Sensor 2 configured.");
  } else {
    Serial.println("Error configuring sensor 2.");
    Serial.print("Error: ");
    Serial.println(error);
  }

  // Data lags a bit behind the sensor, if you're finger is on the sensor when
  // it's being configured this delay will give some time for the data to catch
  // up.
  Serial.println("Loading up the buffer with data....");
  delay(4000);
}

void loop() {
  // Information from the readBpm function will be saved to our "indexFinger"
  // variable.
  myMux.setPort(0);
  indexFinger = bioHub1.readBpm();
  Serial.print("Heartrate1: ");
  Serial.println(indexFinger.heartRate);
  Serial.print("Confidence1: ");
  Serial.println(indexFinger.confidence);
  Serial.print("Oxygen1: ");
  Serial.println(indexFinger.oxygen);
  Serial.print("Status1: ");
  Serial.println(indexFinger.status);
  // Slow it down or your heart rate will go up trying to keep up
  // with the flow of numbers
  delay(250);



  // Information from the readBpm function will be saved to our "middleFinger"
  // variable.
  myMux.setPort(7);
  middleFinger = bioHub1.readBpm();
  Serial.print("Heartrate2: ");
  Serial.println(middleFinger.heartRate);
  Serial.print("Confidence2: ");
  Serial.println(middleFinger.confidence);
  Serial.print("Oxygen2: ");
  Serial.println(middleFinger.oxygen);
  Serial.print("Status2: ");
  Serial.println(middleFinger.status);
  // Slow it down or your heart rate will go up trying to keep up
  // with the flow of numbers
  delay(250);



  delay(1000);
}