#include <Arduino.h>
#include "config.h"
#include <stdarg.h>
#include <stdbool.h>

//calculate radius
int process_steering(int radius_coordinate )
{
  int radius = 0;
  if(radius_coordinate > avgPWM_value)//Steering right
  {
    radius =map(radius_coordinate,avgPWM_value,maxPWM_value,max_radius,min_radius);// turining radius from 1400mm to 600mm
    return radius; 
  }
  else if(radius_coordinate < avgPWM_value)//Steering left
  {
    radius =map(radius_coordinate,avgPWM_value,minPWM_value,min_radius,max_radius);// turining radius from 600mm to 1400mm
    return radius;
  } 
  else{
    radius = 1000;
    return radius;
  }

}

//calculate speed
int process_speed(int speed_coordinate)
{
    int speed = 0;
    if(speed_coordinate ==avgPWM_value)
    {
      return speed = 0;
    }
    else if(speed_coordinate > avgPWM_value)
    {
      speed = map(speed_coordinate,avgPWM_value,maxPWM_value,0,100);
      return speed; 
    }
    else
    {
      speed = map(speed_coordinate,minPWM_value,avgPWM_value,0,100);
      return speed; 
    }
}

//calculate DC motor speed
int* calculateMotorsSpeed(int speed,int radius,int radius_coordinate) {
  
  int size = 3;
  int* speedPWM_Arr = (int*) malloc(size * sizeof(int));

  int speed1, speed2, speed3 = 0;
  int speed1PWM ,speed2PWM ,speed3PWM =0;
  if(speed == 0) {
    speedPWM_Arr[0] = speed1PWM;
    speedPWM_Arr[1] = speed2PWM;
    speedPWM_Arr[2] = speed3PWM;
    return speedPWM_Arr;
  }
  // if no steering, all wheels speed is the same - straight move
  if (radius_coordinate == avgPWM_value) {
    speed1 = speed2 = speed3 = speed;
  }
  // when steering, wheels speed depend on the turning radius value
  else {
    speed1 = speed;
    speed2 = speed * sqrt(d3*d3 + pow((radius - d1), 2)) / (radius + d4);
    speed3 = speed * (radius - d4) / (radius + d4);
  }

  speed1PWM = map(speed1, 0, 100, minPWM_value, maxPWM_value);
  speed2PWM = map(speed2, 0, 100, minPWM_value, maxPWM_value);
  speed3PWM = map(speed3, 0, 100, minPWM_value, maxPWM_value);
  
  speedPWM_Arr[0] = speed1PWM;
  speedPWM_Arr[1] = speed2PWM;
  speedPWM_Arr[2] = speed3PWM;
  return speedPWM_Arr;
}

int* calculateServoAngle(int radius) {
  int size = 4;
  int* Angle_Arr = (int*) malloc(size * sizeof(int));
  float rad = radius;
  int thetaInnerFront,thetaInnerBack,thetaOuterFront,thetaOuterBack = 0;
  float atanInnerFront = atan(d3 / (rad + d1));
  float atanInnerBack = atan(d2 / (rad + d1));
  float atanOuterFront = atan(d3 / (rad - d1));
  float atanOuterBack = atan(d2 / (rad - d1));
  thetaInnerFront = round((atanInnerFront * 180) / M_PI);
  thetaInnerBack = round((atanInnerBack * 180) / M_PI);
  thetaOuterFront = round((atanOuterFront * 180) / M_PI);
  thetaOuterBack = round((atanOuterBack * 180) / M_PI);
  
  Angle_Arr[0] = thetaInnerFront;
  Angle_Arr[1] = thetaInnerBack;
  Angle_Arr[2] = thetaOuterFront;
  Angle_Arr[3] = thetaOuterBack;
  return Angle_Arr;
}

bool check_input_parameters(int n,...)
{
  va_list args;
    va_start(args, n);
    int min = va_arg(args, int);
    int max = va_arg(args, int);
    for (int i = 0; i < n-2; i++) {
        int num = va_arg(args, int);
        if (num < min || num > max) {
            va_end(args);
            return false;
        }
    }
    va_end(args);
    return true;
}

