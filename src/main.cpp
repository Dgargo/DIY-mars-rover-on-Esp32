#include <Arduino.h>



#include "config.h"
#include "test_app/task_rover.h"
#include "test_app//setups_and_calculation/setup_function.h"

void setup() {
  Serial.begin(115200);

  setup_channelPWM_DC();
  setup_PWM_Pin_DC();
  
  xTaskCreate(test_move_rover_task,"move rover ", 10000,NULL,1,NULL);
  xTaskCreate(test_move_camera_task,"move camera",4000,NULL,1,NULL);

  vTaskStartScheduler();
}

void loop() {
  // put your main code here, to run repeatedly:
}