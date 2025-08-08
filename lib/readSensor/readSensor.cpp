#include<arduino.h>
#include<readSensor.h>
#include <Adafruit_BMP085.h>
#include "I2Cdev.h"

MPU6050 mpu;

bool dmpReady = false;
uint8_t devStatus;
uint16_t packetSize;
uint16_t fifoCount;
uint8_t fifoBuffer[64];

Quaternion q;
VectorFloat gravity;
float ypr[3];

void setupBMP085() {
  // Initialize the BMP085 sensor
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    while (1) delay(10);
  } 
  Serial.println("BMP085 sensor initialized successfully.");
}

void setupMPU() {
  Wire.begin();
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed");
    while (1);
  }

  devStatus = mpu.dmpInitialize();

  if (devStatus == 0) {
    mpu.setDMPEnabled(true);
    dmpReady = true;
    packetSize = mpu.dmpGetFIFOPacketSize();
    Serial.println("DMP ready!");
  } else {
    Serial.print("DMP Init failed (code ");
    Serial.print(devStatus);
    Serial.println(")");
  }
}

void readSensor(float *out){
  out[0] = out[1] = out[2] = out[3] = out[4] = out[5] = -1.0f;

  if (!dmpReady) return;

  fifoCount = mpu.getFIFOCount();
  if (fifoCount < packetSize) return;
    
    out[0] = bmp.readTemperature(); // °C
    out[1] = bmp.readPressure();    // Pa
    out[2] = bmp.readAltitude();    // m

  // Read the DMP data
  mpu.getFIFOBytes(fifoBuffer, packetSize);
  mpu.dmpGetQuaternion(&q, fifoBuffer);
  mpu.dmpGetGravity(&gravity, &q);
  mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

  out[3] = ypr[0] * 180 / M_PI; // Yaw
  out[4] = ypr[1] * 180 / M_PI; // Pitch
  out[5] = ypr[2] * 180 / M_PI; // Roll
}