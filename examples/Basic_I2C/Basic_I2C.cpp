/*
   Basic_I2C.cpp

   Adapted by Simon D. Levy from


   Basic_I2C.ino
   Brian R Taylor
   brian.taylor@bolderflight.com
   2016-10-10 

   Copyright (c) 2016 Bolder Flight Systems

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
#include <wiringPi.h>
#include <stdio.h>

MPU9250 IMU(0x68);

int main(int argc, char ** argv)
{

    // start communication with IMU and 
    // set the accelerometer and gyro ranges.
    // ACCELEROMETER 2G 4G 8G 16G
    // GYRO 250DPS 500DPS 1000DPS 2000DPS
    int beginStatus = IMU.begin(ACCEL_RANGE_4G,GYRO_RANGE_250DPS);

    while (true) {

        if(beginStatus < 0) {
            delay(1000);
            printf("IMU initialization unsuccessful\n");
            printf("Check IMU wiring or try cycling power\n");
            delay(10000);
        }

        else{

            int16_t ax, ay, az, gx, gy, gz;

            // get both the accel (m/s/s) and gyro (rad/s) data
            IMU.getMotion6Counts(&ax, &ay, &az, &gx, &gy, &gz);

            // print the data
            printf("%d %d %d %d %d %d %d\n", ax, ay, az, gx, gy, gz);

            // delay a frame
            delay(50);
        }
    }
}
