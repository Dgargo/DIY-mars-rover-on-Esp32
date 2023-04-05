#include <Arduino.h>
//#include <ESP32Servo.h>
//#include <ServoEasing.hpp>
//#include <ServoEasing.h>
#include "config.h"
#include "test_app/setups_and_calculation/calculate_rover.h"
#include "test_app/move_control/move_rover.h"
#include "test_app/motor_control/dc_motor.h"
#include "test_app/motor_control/servo_control.h"
#include "debug_app/debug_claculate_value.h"

void move_rover(int radius_coordinate,int speed_coordinate)
{
  if(radius_coordinate < minPWM_value || radius_coordinate > maxPWM_value || speed_coordinate < minPWM_value || speed_coordinate > maxPWM_value )
  {
    Serial.println("incorrect parameters");
    return;
  }
  Serial.println("______________________________");
  int radius = 0 ;
  int speed  = 0 ;
  int speed1PWM, speed2PWM, speed3PWM = 0;
  int thetaInnerFront, thetaInnerBack, thetaOuterFront, thetaOuterBack = 0;

  int channel_side_front[]={0,2,4,6,8,10};
  int channel_side_back[] ={1,3,5,7,9,11};
  int DC_motor_LOW_pin_front[] = {motorW1_IN2,motorW2_IN2,motorW3_IN2,motorW4_IN1,motorW5_IN1,motorW6_IN1};
  int DC_motor_LOW_pin_back[]  = {motorW1_IN1,motorW2_IN1,motorW3_IN1,motorW4_IN2,motorW5_IN2,motorW6_IN2};

  process_steering_and_speed(radius_coordinate,speed_coordinate,radius,speed);
  calculateMotorsSpeed(speed,radius,radius_coordinate,speed1PWM,speed2PWM,speed3PWM);
  calculateServoAngle(radius,d1,d2,d3,thetaInnerFront,thetaInnerBack,thetaOuterFront,thetaOuterBack);
   // Steer right
   if (radius_coordinate > avgPWM_value) 
   {
    
     move_servo_right(thetaInnerFront,thetaInnerBack,thetaOuterFront,thetaOuterBack);
     #ifdef DEBUG
      Serial.print("move right-");
     #endif
    // DC Motors
    if (speed_coordinate > avgPWM_value) 
    { // Move forward
      
      move_sideways(channel_side_front,DC_motor_LOW_pin_front,speed1PWM,speed2PWM,speed3PWM,get_pwm_values_right);
      #ifdef DEBUG
       Serial.println("forward");
      #endif
    }
    else if (speed_coordinate < avgPWM_value) 
    { // Move backward
      
      move_sideways(channel_side_front,DC_motor_LOW_pin_front,speed1PWM,speed2PWM,speed3PWM,get_pwm_values_right);
      #ifdef DEBUG
       Serial.println("backward");
      #endif
    }
    
   }
   
   // Steer left
  else if (radius_coordinate < avgPWM_value) 
  {
    
    move_servo_left(thetaInnerFront,thetaInnerBack,thetaOuterFront,thetaOuterBack);
    #ifdef DEBUG
     Serial.println("move left-");
    #endif
    // DC Motors
    if (speed_coordinate > avgPWM_value) 
    { // Move forward
      move_sideways(channel_side_front,DC_motor_LOW_pin_front,speed1PWM,speed2PWM,speed3PWM,get_pwm_values_left);
      #ifdef DEBUG
       Serial.println("forward");
      #endif
    }
    else if (speed_coordinate < avgPWM_value) 
    { // Move backward
      move_sideways(channel_side_back,DC_motor_LOW_pin_back,speed1PWM,speed2PWM,speed3PWM,get_pwm_values_left); 
      #ifdef DEBUG
       Serial.println("backward");
      #endif
    }
    
  }
   // Move straight
  else 
  {
    
    move_servo_straight();
    #ifdef DEBUG
      Serial.println("move straight-");
    #endif
    // DC Motors
    if (speed_coordinate > avgPWM_value) 
    {// Forward
      move_straight(speed1PWM,0);
      #ifdef DEBUG
       Serial.println("forward");
      #endif
    }
    else if (speed_coordinate < avgPWM_value) 
    {// Backward
      move_straight(speed1PWM,1);
      #ifdef DEBUG
       Serial.println("backward");
      #endif
    }
    
  }
  #ifdef DEBUG
    Serial.println("move rover sucsesful");
  #endif
  speed_coordinate = avgPWM_value;
  radius_coordinate = avgPWM_value;
}


