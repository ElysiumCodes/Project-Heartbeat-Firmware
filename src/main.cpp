#include <Arduino.h>
#include <idleState.h>
#include "readSensor.h"
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;

void setup() {
  // Initialize Serial for debugging
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }


  // Initialize the BMP085 sensor
  setupBMP085();
  setupMPU();
  
}

void loop() {
  float data[6] = {0};
  readSensor(data);
  idleState();

  // Print the sensor data
  Serial.print("Temperature: ");  
  Serial.print(data[0]);
  Serial.println(" °C");  
  Serial.print("Pressure: ");
  Serial.print(data[1]);
  Serial.println(" Pa");
  Serial.print("Altitude: ");
  Serial.print(data[2]);
  Serial.println(" m");
}