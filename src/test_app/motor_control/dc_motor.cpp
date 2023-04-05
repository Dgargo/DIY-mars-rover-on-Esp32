#include <Arduino.h>

#include "test_app/motor_control/dc_motor.h"
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
void move_sideways(int channel_side[] , int LOW_pin[],int speed1PWM ,int speed2PWM ,int speed3PWM,int* (*get_pwm_values)(int,int,int))
{
  int* pwm_values = get_pwm_values(speed1PWM, speed2PWM, speed3PWM);
  for (int i = 0; i < 6; i++) {
        ledcWrite(Arr_channel_DC_motor[channel_side[i]], pwm_values[i]);
        digitalWrite(LOW_pin[i], LOW);
    }
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
  switch (channel_Num)
  {
  case 0:
    for(int i = 0 ;i<number_channel_DC_motor;i+=2)
    {
      ledcWrite(Arr_channel_DC_motor[i], speed1PWM);
      digitalWrite(Arr_DC_Pin[i+1], LOW);
    }
  break;
  case 1:
    for(int i = 1 ;i<number_channel_DC_motor;i+=2)
    {
      ledcWrite(Arr_channel_DC_motor[i], speed1PWM);
      digitalWrite(Arr_DC_Pin[i-1], LOW);
    }
  break;
  default:
    Serial.println("Invalid channel number");
    break;
  }
}