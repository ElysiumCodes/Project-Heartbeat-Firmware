#include <Arduino.h>
#include <idleState.h>
#include <readSensor.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;
void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }

  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    while (1) delay(10);
  } 

  Serial.println("BMP085 sensor initialized successfully.");
}

void loop() {
  readSensor();
  idleState();
}