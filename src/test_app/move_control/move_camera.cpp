
#include <Arduino.h>

#include "config.h"
#include "test_app/move_control/move_camera.h"
#include "debug_app/debug_claculate_value.h"


void move_camera_servo(int camera_angle_coordinate,Pwm servoCamTilt )
{
  if(camera_angle_coordinate < minPWM_value || camera_angle_coordinate > maxPWM_value) {
    Serial.println("Invalid input");
    return;
  }
  int camTilt = avgPWM_value;
  
  if (camera_angle_coordinate < avgPWM_value) {
    if (camTilt > camera_head_min_pozition) {
      camTilt--;
      vTaskDelay(camera_head_move_delay);
    }
  } else if (camera_angle_coordinate > avgPWM_value) {
    if (camTilt < camera_head_max_pozition) {
      camTilt++;
      vTaskDelay(camera_head_move_delay);
    }
  }

  camTilt = map(camTilt, maxPWM_value, minPWM_value, camera_head_min_pozition, camera_head_max_pozition);
  servoCamTilt.writeServo(servo_Cammera_Pin,camTilt);
  #ifdef DEBUG
   int data[] = {camTilt};
   String data_name[] = {"camTilt"};
   size_t num_data = sizeof(data) / sizeof(data[0]);
   debug_print("camera servo",data,num_data,data_name);
  #endif
}
 
void move_camera_stepper(int camera_turn_coordinate,AccelStepper camPanStepper)
{
  if(camera_turn_coordinate < minPWM_value || camera_turn_coordinate > maxPWM_value) {
    Serial.println("Invalid input");
    return;
  }

  int camPan = 0;
  if (camera_turn_coordinate >= (avgPWM_value/2) && camera_turn_coordinate  < avgPWM_value) {
    camPan = map(camera_turn_coordinate, (avgPWM_value/2), avgPWM_value, 400, 0);
  }
  else if (camera_turn_coordinate > avgPWM_value && camera_turn_coordinate <= maxPWM_value) {
    camPan = map(camera_turn_coordinate, avgPWM_value, maxPWM_value, 0, -400);
  }
  else {
    camPan = 0;
  }
  camPanStepper.setSpeed(camPan);    // Camera pan
  camPanStepper.run();
  #ifdef DEBUG
   int data[] = {camPan};
   String data_name[] = {"camPan"};
   size_t num_data = sizeof(data) / sizeof(data[0]);
   debug_print("camera stepper",data,num_data,data_name);
  #endif

}