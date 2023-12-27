#include <Arduino.h>
#include "Structs.h"
#include "Constants.h"

void sendData(struct IMU_Values imu){
    if(Serial.available()){
        switch(Serial.read()){
            case 49:
                Serial.println(imu.CurrentOrientation.PitchAngle);
                break;
            case 50:
                Serial.println(imu.CurrentOrientation.RollAngle);
                break;
            case 51:
                Serial.println(imu.CurrentOrientation.YawAngle);
                break;
            default:
                break;
        }
    }
    // Serial.print("Pitch: ");
    // Serial.print(imu.CurrentOrientation.PitchAngle);
    // Serial.print("\t");
    // Serial.print("Roll: ");
    // Serial.print(imu.CurrentOrientation.RollAngle);
    // Serial.print("\t");
    // Serial.print("Yaw: ");
    // Serial.println(imu.CurrentOrientation.YawAngle);
}