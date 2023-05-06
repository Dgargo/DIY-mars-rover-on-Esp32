#include <Arduino.h>
#include <setBuiltInDiode_test.hpp>
#include <unity.h>
//#include "embedded_app/calculate_rover_test.hpp"
#include "embedded_app/motor_app/dc_motor_test.hpp"

void setup() {
  Serial.begin(115200);
  delay(1000);
  UNITY_BEGIN();
  /*
  #pragma region Calculate
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

  RUN_TEST(test_check_input_parameters_true);

  RUN_TEST(test_check_input_parameters_false);
  #pragma endregion Calculate 
  */
  #pragma region DC_motor 
  RUN_TEST(test_get_pwm_values_right_one);
  RUN_TEST(test_get_pwm_values_right_two);
  RUN_TEST(test_get_pwm_values_left_one);
  RUN_TEST(test_get_pwm_values_left_two);

  RUN_TEST(test_move_sideways_right_front_one);
  RUN_TEST(test_move_sideways_right_front_two);

  RUN_TEST(test_move_sideways_right_front_pin_one);
  RUN_TEST(test_move_sideways_right_front_pin_two);
  RUN_TEST(test_move_sideways_right_front_pin_three);
  #pragma endregion DC_motor
}

void loop() {
  
}