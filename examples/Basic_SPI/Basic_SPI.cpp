/*
   Basic_SPI.cpp : Displays basic functionaliy of MPU9250 using SPI on Raspberry Pi.

   Copyright (c) 2016 Simon D. Levy

   Adapted from https://github.com/bolderflight/MPU9250/blob/master/examples/Basic_SPI/Basic_SPI.ino

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
   and associated documentation files (the "Software"), to deal in the Software without restriction, 
   including without limitation the rights to use, copy, modify, merge, publish, distribute, 
   sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is 
   furnished to do so, subject to the following conditions:
   The above copyright notice and this permission notice shall be included in all copies or 
   substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
   BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
   DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "MPU9250.h"
#include <stdio.h>
#include <wiringPi.h>


// an MPU9250 object with the MPU-9250 sensor using SPI bus 1, speed 400kHz
MPU9250 IMU(1, 400000);

int beginStatus;

static void setup() {

  // start communication with IMU and 
  // set the accelerometer and gyro ranges.
  // ACCELEROMETER 2G 4G 8G 16G
  // GYRO 250DPS 500DPS 1000DPS 2000DPS
  beginStatus = IMU.begin(ACCEL_RANGE_4G,GYRO_RANGE_250DPS);
}

static void loop() {
  if(beginStatus < 0) {
    delay(1000);
    fprintf(stderr, "IMU initialization unsuccessful\n");
    fprintf(stderr, "Check IMU wiring or try cycling power\n");
    delay(10000);
  }
  else{

    float ax, ay, az, gx, gy, gz;

    // get the accelerometer data (m/s/s)
    IMU.getAccel(&ax, &ay, &az);
  
    // get the gyro data (rad/s)
    IMU.getGyro(&gx, &gy, &gz);
  
    printf("%+6.6f %+6.6f %+6.6f %+6.6f %+6.6f %+6.6f\n", ax, ay, az, gx, gy, gz);

    delay(50);
  }
}

int main(int argc, char ** argv) {

    setup();

    while (true) {
        loop();
    }
}
