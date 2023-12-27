#include <Arduino.h>
#include "Functions.h"
#include "Constants.h"
#include "Structs.h"

#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

void disableWDT() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // Disable brownout detector
  WRITE_PERI_REG(RTC_CNTL_WDTCONFIG0_REG, 0); // Set WDT timeout to longest (approximately 71 minutes)
  WRITE_PERI_REG(RTC_CNTL_WDTCONFIG1_REG, 0); // Disable WDT
}



//Create two tasks for separate cores of Xtensa LX6
TaskHandle_t Task1;
TaskHandle_t Task2;

struct IMU_Values imu_values;

//Task 1 pinned to core0. Mainly for communication interrupts of reciever and speedometer.
void Task1code( void * pvParameters ){
  initializeIMU();
  delay(5000);

  for(;;){

    imu_values = GetIMUvalues();
    delay(50);


  }

}

//Task2code pinned to core1. Mainly for control loop and outputs.
void Task2code( void * pvParameters ){
    
  Serial.begin(9600);

  for(;;){
    sendData(imu_values);
    delay(1);
  }
}

void setup() {
  disableWDT();


//create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(
                    Task1code,   /* Task function. */
                    "Task1",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task1,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */                  
  delay(500); 

  //create a task that will be executed in the Task2code() function, with priority 1 and executed on core 1
  xTaskCreatePinnedToCore(
                    Task2code,   /* Task function. */
                    "Task2",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task2,      /* Task handle to keep track of created task */
                    1);          /* pin task to core 1 */
    delay(500); 

  // Serial.begin(9600);
  // initializeIMU();
  // delay(5000);

    
}

void loop() {
  // imu_values = GetIMUvalues();
  // sendData(imu_values);
  // delay(10);

}