#include <Arduino.h>
#include <setBuiltInDiode_test.hpp>
#include <unity.h>
#include "embedded_app/calculate_rover_test.hpp"


void setup() {
  Serial.begin(115200);
  delay(1000);
  UNITY_BEGIN();
  //left 
  RUN_TEST(test_process_steering_left);
  //rigth  
  RUN_TEST(test_process_steering_right);
  //max speed 
  RUN_TEST(test_process_speed_max);
  //min speed 
  RUN_TEST(test_process_speed_min);
  //motor speed steering right max
  RUN_TEST(test_calculate_motors_speed_steering_right_max);
  //motor speed steering left max
  RUN_TEST(test_calculate_motors_speed_steering_left_max);
  //motor speed steering min
  RUN_TEST(test_calculate_motors_speed_steering_min);
  //motor speed straight max
  RUN_TEST(test_calculate_motors_speed_straight_max);
  //motor speed straight max
  RUN_TEST(test_calculate_motors_speed_straight_min);
  //servo angle right
  RUN_TEST(test_calculate_servo_angle_right);
  //servo angle left
  RUN_TEST(test_calculate_servo_angle_left);
}

void loop() {
  
}