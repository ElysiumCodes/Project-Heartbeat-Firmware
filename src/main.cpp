#include <Arduino.h>
#include <idleState.h>
#include <readSensor.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_MPU6050.h>

Adafruit_BMP085 bmp;
Adafruit_MPU6050 mpu;

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

  if (!mpu.begin()) {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    while (1) delay(10);
  }
  Serial.println("MPU6050 sensor initialized successfully.");

}

void loop() {
  readSensor();
  idleState();

  sensors_event_t accel, gyro, temp;
  mpu.getEvent(&accel, &gyro, &temp);
  Serial.print("Accelerometer X: ");
  Serial.print(accel.acceleration.x);
  Serial.print(" m/s^2, Y: ");
  Serial.print(accel.acceleration.y);
  Serial.print(" m/s^2, Z: ");
  Serial.print(accel.acceleration.z);
  Serial.println(" m/s^2"); 
  Serial.print("Gyro X: ");
  Serial.print(gyro.gyro.x);
  Serial.print(" rad/s, Y: ");
  Serial.print(gyro.gyro.y);
  Serial.print(" rad/s, Z: ");
  Serial.print(gyro.gyro.z);
  Serial.println(" rad/s");

}