/*
Basic_SPI.ino
Brian R Taylor
brian.taylor@bolderflight.com

Copyright (c) 2017 Bolder Flight Systems

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
#include "main.h"

// an MPU9250 object with the MPU-9250 sensor on SPI bus 0 and chip select pin 10
MPU9250 IMU(SPI,7);
MPU9250 IMU2(SPI,6);

SDCard sd;
int status;
int status2;

unsigned long printTimer,logTimer;

float XAccLog, YAccLog, ZAccLog;
void setup() {
  // serial to display data
  Serial.begin(115200);
  while(!Serial) {}

  // start communication with IMU 
  status = IMU.begin();
  if (status < 0) {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while(1) {}
  }

  status2 = IMU2.begin();
  if (status2 < 0) {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status2);
    while(1) {}
  }

    // setting the accelerometer full scale range to +/-8G 
  IMU.setAccelRange(MPU9250FIFO::ACCEL_RANGE_8G);
  // setting the gyroscope full scale range to +/-500 deg/s
  IMU.setGyroRange(MPU9250FIFO::GYRO_RANGE_500DPS);
  
  // setting the accelerometer full scale range to +/-8G 
  IMU2.setAccelRange(MPU9250FIFO::ACCEL_RANGE_8G);
  // setting the gyroscope full scale range to +/-500 deg/s
  IMU2.setGyroRange(MPU9250FIFO::GYRO_RANGE_500DPS);

  sd.SDCardInitialization();
  Serial.println("Don't move! Calibrating...");
  IMU.xyzCalibrationRoutine();
  IMU2.xyzCalibrationRoutine();

}

void loop() {

  IMU.readSensor();
  IMU2.readSensor();
  // display the data

   XAccLog = IMU.getAccelX_mss() - IMU2.getAccelX_mss();

   YAccLog = IMU.getAccelY_mss() - IMU2.getAccelY_mss();

   ZAccLog = IMU.getAccelZ_mss() - IMU2.getAccelZ_mss();


  if (millis()-printTimer >= 100){
  Serial.println(" ");
  Serial.println("Bed Accelerometer m/s^2: " );
  Serial.print(IMU.getAccelX_mss(),6);
  Serial.print("  ");
  Serial.print(IMU.getAccelY_mss(),6);
  Serial.print("  ");
  Serial.println(IMU.getAccelZ_mss(),6);
  
  Serial.println(" ");
  Serial.println("Top plate Accelerometer m/s^2: ");
  Serial.print(IMU2.getAccelX_mss(),6);
  Serial.print("  ");
  Serial.print(IMU2.getAccelY_mss(),6);
  Serial.print("  ");
  Serial.println(IMU2.getAccelZ_mss(),6);
  printTimer = millis();
  }
//   sd.WriteDataToSD(XAccLog,YAccLog,ZAccLog);
}