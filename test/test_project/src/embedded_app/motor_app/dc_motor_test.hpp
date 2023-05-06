#include <unity.h>

#include "dc_motor.hpp"

void test_get_pwm_values_right_one()
{
 int speed1PWM = 100;
 int speed2PWM = 100;
 int speed3PWM = 100;
 int expected[6] = {100,100,100,100,100,100};
 int actual[6];
 int size = sizeof(actual) / sizeof(actual[0]);
 int *actual_ptr = get_pwm_values_right(speed1PWM,speed2PWM,speed3PWM);

 for (int i = 0; i < size; i++) {
    actual[i] = actual_ptr[i];
    }
 TEST_ASSERT_EQUAL_INT_ARRAY(expected,actual,size);

}

void test_get_pwm_values_right_two()
{
 int speed1PWM = 0;
 int speed2PWM = 0;
 int speed3PWM = 0;
 int expected[6] = {0,0,0,0,0,0};
 int actual[6];
 int size = sizeof(actual) / sizeof(actual[0]);
 int *actual_ptr = get_pwm_values_right(speed1PWM,speed2PWM,speed3PWM);

 for (int i = 0; i < size; i++) {
    actual[i] = actual_ptr[i];
    }
 TEST_ASSERT_EQUAL_INT_ARRAY(expected,actual,size);

}

void test_get_pwm_values_left_one()
{
 int speed1PWM = 10;
 int speed2PWM = 10;
 int speed3PWM = 10;
 int expected[6] = {10,10,10,10,10,10};
 int actual[6];
 int size = sizeof(actual) / sizeof(actual[0]);
 int *actual_ptr = get_pwm_values_left(speed1PWM,speed2PWM,speed3PWM);

 for (int i = 0; i < size; i++) {
    actual[i] = actual_ptr[i];
    }
 TEST_ASSERT_EQUAL_INT_ARRAY(expected,actual,size);

}

void test_get_pwm_values_left_two()
{
 int speed1PWM = 1000;
 int speed2PWM = 1000;
 int speed3PWM = 1000;
 int expected[6] = {1000,1000,1000,1000,1000,1000};
 int actual[6];
 int size = sizeof(actual) / sizeof(actual[0]);
 int *actual_ptr = get_pwm_values_left(speed1PWM,speed2PWM,speed3PWM);

 for (int i = 0; i < size; i++) {
    actual[i] = actual_ptr[i];
    }
 TEST_ASSERT_EQUAL_INT_ARRAY(expected,actual,size);

}
/**
 * !!!GPIO HIGH at boot  : 1,3,5,14,15 
 * 
 */
void test_move_sideways_right_front_one()
{
  int channel_side_front[]={0,2,4,6,8,10};
  int DC_motor_LOW_pin_front[] = {motorW1_IN2,motorW2_IN2,motorW3_IN2,motorW4_IN1,motorW5_IN1,motorW6_IN1};
  int DC_motor_LOW_pin_sideways_front[] = {motorW1_IN2,motorW2_IN2,motorW3_IN2,motorW4_IN1,motorW5_IN1,motorW6_IN1};
  int DC_motor_LOW_pin_sideways_back[]  = {motorW1_IN1,motorW2_IN1,motorW3_IN1,motorW4_IN2,motorW5_IN2,motorW6_IN2};
  int speed1PWM = 150;
  int speed2PWM = 150;
  int speed3PWM = 150;
  int expected[6] = {150,150,150,150,150,150};
  int actual[6];
  int size = sizeof(actual) / sizeof(actual[0]);
  int *actual_ptr = move_sideways_return_pwm(channel_side_front,DC_motor_LOW_pin_sideways_back,speed1PWM,speed2PWM,speed3PWM,get_pwm_values_right);

 for (int i = 0; i < size; i++) {
    actual[i] = actual_ptr[i];
    }
  TEST_ASSERT_EQUAL_INT_ARRAY(expected,actual,size);
}

void test_move_sideways_right_front_two()
{
  int channel_side_front[]={0,2,4,6,8,10};
  int DC_motor_LOW_pin_sideways_front[] = {motorW1_IN2,motorW2_IN2,motorW3_IN2,motorW4_IN1,motorW5_IN1,motorW6_IN1};
  int speed1PWM = 200;
  int speed2PWM = 200;
  int speed3PWM = 200;
  int expected[6] = {200,200,200,200,200,200};
  int actual[6];
  int size = sizeof(actual) / sizeof(actual[0]);
  int *actual_ptr = move_sideways_return_pwm(channel_side_front,DC_motor_LOW_pin_sideways_front,speed1PWM,speed2PWM,speed3PWM,get_pwm_values_right);

 for (int i = 0; i < size; i++) {
    actual[i] = actual_ptr[i];
    }
  TEST_ASSERT_EQUAL_INT_ARRAY(expected,actual,size);
}

void test_move_sideways_right_front_pin_one()
{
  int channel_side_front[]={0,2,4,7,9,11};
  int DC_motor_LOW_pin_sideways_front[] = {motorW1_IN2,motorW2_IN2,motorW3_IN2,motorW4_IN1,motorW5_IN1,motorW6_IN1};
  int speed1PWM = 200;
  int speed2PWM = 200;
  int speed3PWM = 200;
  int expected[6] = {200,200,200,200,200,200};
  int actual[6];
  int size = sizeof(actual) / sizeof(actual[0]);
  int *actual_ptr = move_sideways_return_pwm(channel_side_front,DC_motor_LOW_pin_sideways_front,speed1PWM,speed2PWM,speed3PWM,get_pwm_values_right);

  for (int i = 0; i < size; i++) {
    actual[i] = actual_ptr[i];
    }
  for (int i = 0; i < 3; i++)
  {
    TEST_ASSERT_EQUAL(LOW,digitalRead(DC_motor_LOW_pin_sideways_front[i]));
  }
  digitalWrite(GPIO_NUM_5,LOW);
  TEST_ASSERT_EQUAL(HIGH,digitalRead(GPIO_NUM_5));  
}

void test_move_sideways_right_front_pin_two()
{
  int channel_side_front[]={0,2,4,7,9,11};
  int DC_motor_LOW_pin_sideways_front[] = {motorW1_IN2,motorW2_IN2,motorW3_IN2,motorW4_IN1,motorW5_IN1,motorW6_IN1};
  int speed1PWM = 200;
  int speed2PWM = 200;
  int speed3PWM = 200;
  int expected[6] = {200,200,200,200,200,200};
  int actual[6];
  int size = sizeof(actual) / sizeof(actual[0]);
  int *actual_ptr = move_sideways_return_pwm(channel_side_front,DC_motor_LOW_pin_sideways_front,speed1PWM,speed2PWM,speed3PWM,get_pwm_values_right);

  for (int i = 0; i < size; i++) {
    actual[i] = actual_ptr[i];
    }
  
  TEST_ASSERT_EQUAL(LOW,digitalRead(GPIO_NUM_5));

}

void test_move_sideways_right_front_pin_three()
{
  int channel_side_front[]={0,2,4,6,8,10};
  int DC_motor_LOW_pin_sideways_front[] = {motorW1_IN2,motorW2_IN2,motorW3_IN2,motorW4_IN1,motorW5_IN1,motorW6_IN1};
  int speed1PWM = 200;
  int speed2PWM = 200;
  int speed3PWM = 200;
  int expected[6] = {200,200,200,200,200,200};
  int actual[6];
  int size = sizeof(actual) / sizeof(actual[0]);
  int *actual_ptr = move_sideways_return_pwm(channel_side_front,DC_motor_LOW_pin_sideways_front,speed1PWM,speed2PWM,speed3PWM,get_pwm_values_right);

  for (int i = 0; i < size; i++) {
    actual[i] = actual_ptr[i];
    }
   
  TEST_ASSERT_EQUAL(HIGH,digitalRead(GPIO_NUM_15));
  
}

