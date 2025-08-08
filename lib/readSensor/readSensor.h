#ifndef READ_SENSOR_H
#define READ_SENSOR_H
#include <Adafruit_BMP085.h>
#include "MPU6050_6Axis_MotionApps20.h"
    extern Adafruit_BMP085 bmp;

    void readSensor(float *data);
    void setupBMP085();
    void setupMPU();

#endif // READ_SENSOR_H
