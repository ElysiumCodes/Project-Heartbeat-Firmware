#include<arduino.h>
#include<readSensor.h>
#include <Adafruit_BMP085.h>

void readSensor() {
  // Read temperature, pressure, and altitude
  float temperature = bmp.readTemperature();
  int32_t pressure = bmp.readPressure();
  float altitude = bmp.readAltitude();

  // Print the sensor readings
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" Pa");

  Serial.print("Altitude: ");
  Serial.print(altitude);
  Serial.println(" m");
}