#include <Arduino.h>

#include "config.h"

//set arr arr for right move
int* get_pwm_values_right(int speed1PWM, int speed2PWM, int speed3PWM) {
    static int pwm_values[6];
    pwm_values[0] = speed1PWM;
    pwm_values[1] = speed1PWM;
    pwm_values[2] = speed1PWM;
    pwm_values[3] = speed2PWM;
    pwm_values[4] = speed3PWM;
    pwm_values[5] = speed2PWM;
    return pwm_values;
}

//set arr arr for left move
int* get_pwm_values_left(int speed1PWM, int speed2PWM, int speed3PWM) {
    static int pwm_values[6];
    pwm_values[0] = speed2PWM;
    pwm_values[1] = speed3PWM;
    pwm_values[2] = speed2PWM;
    pwm_values[3] = speed1PWM;
    pwm_values[4] = speed1PWM;
    pwm_values[5] = speed1PWM;
    return pwm_values;
}

//move DC motor 
int* move_sideways_return_pwm(int channel_side[] , int LOW_pin[],int speed1PWM ,int speed2PWM ,int speed3PWM,int* (*get_pwm_values)(int,int,int))
{
  
  int* pwm_values = get_pwm_values(speed1PWM, speed2PWM, speed3PWM);
  for (int i = 0; i < 6; i++) {
        ledcWrite(Arr_channel_DC_motor[channel_side[i]], pwm_values[i]);
        digitalWrite(LOW_pin[i], LOW);
    }
  return pwm_values;
}

//move DC motors at the  straight motion
//front Channel_num == 0
//back Channel_num == 1
void move_straight(int speed1PWM,int channel_Num)
{
  if(channel_Num < 0 || channel_Num >= 2) {
    Serial.println("Invalid channel number");
    return;
  }

  int Arr_channel_DC_motor_front[] = {0,2,4,6,8,10};
  int Arr_channel_DC_motor_back[]  = {1,3,5,7,9,11};

  int Arr_DC_pin_LOW_front[] = {motorW1_IN2,motorW2_IN2,motorW3_IN2,motorW4_IN2,motorW5_IN2,motorW6_IN2};
  int Arr_DC_pin_LOW_back[]  = {motorW1_IN1,motorW2_IN1,motorW3_IN1,motorW4_IN1,motorW5_IN1,motorW6_IN1};
  int size = sizeof(Arr_channel_DC_motor_front) / sizeof(Arr_channel_DC_motor_front[0]);
  switch (channel_Num)
  {
  case 0:
    for(int i = 0 ;i<size;i+=2)
    {
      ledcWrite(Arr_channel_DC_motor_front[i], speed1PWM);
      digitalWrite(Arr_DC_pin_LOW_front[i], LOW);
    }
  break;
  case 1:
    for(int i = 1 ;i<size;i+=2)
    {
      ledcWrite(Arr_channel_DC_motor_back[i], speed1PWM);
      digitalWrite(Arr_DC_pin_LOW_back[i], LOW);
    }
  break;
  default:
    Serial.println("Invalid channel number");
    break;
  }
}