#include <Arduino.h>
#include "config.h"
#include "debug_app/debug_claculate_value.h"
int speed = 0; // rover speed
int radius = 0; // turning radius

int speed1PWM, speed2PWM, speed3PWM = 0;

int thetaInnerFront, thetaInnerBack, thetaOuterFront, thetaOuterBack = 0;



//calculate radius and speed
void process_steering_and_speed(int radius_coordinate ,int speed_coordinate ,int &radius ,int &speed)
{
  if (radius < 0 || speed < 0 || avgPWM_value < 0 || minPWM_value < 0 || maxPWM_value < 0) {
    Serial.println("incorrect parameters");
    return;
  }

  if (radius_coordinate < minPWM_value || radius_coordinate > maxPWM_value || speed_coordinate < minPWM_value || speed_coordinate > maxPWM_value) {
    Serial.println("incorrect parameters");
    return;
  }

  #ifdef DEBUG
  int data[] = {radius_coordinate,speed_coordinate};
  String data_name[] = {"radius_coor","speed_coor"};
  size_t num_data1 = sizeof(data) / sizeof(data[0]);
  debug_print("radius and speed coor",data,num_data1,data_name);
  #endif

  if(radius_coordinate > avgPWM_value)//Steering right
  {
    radius =map(radius_coordinate,avgPWM_value,maxPWM_value,1400,600);// turining radius from 1400mm to 600mm 
  }
  else if(radius_coordinate < avgPWM_value)//Steering left
  {
    radius =map(radius_coordinate,avgPWM_value,minPWM_value,1400,600);// turining radius from 600mm to 1400mm
  } 
  speed = map(speed_coordinate,avgPWM_value,maxPWM_value,0,100);
 
  #ifdef DEBUG
  int data2[] = {radius,speed};
  String data_name2[] = {"radius","speed"};
  size_t num_data2 = sizeof(data) / sizeof(data[0]);
  debug_print("radius and speed",data2,num_data2,data_name2);
  #endif
}

//calculate DC motor speed
void calculateMotorsSpeed(int speed,int radius,int radius_coordinate,int &speed1PWM , int &speed2PWM , int &speed3PWM) {
  if (speed < 0 || radius < 0 || avgPWM_value < 0) {
    Serial.println("incorrect parameters");
    return;
  }

  int speed1, speed2, speed3 = 0;

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

  speed1PWM = map(round(speed1), 0, 100, 0, 4096);
  speed2PWM = map(round(speed2), 0, 100, 0, 4096);
  speed3PWM = map(round(speed3), 0, 100, 0, 4096);

  #ifdef DEBUG
  int data[] = {speed1PWM,speed2PWM,speed3PWM};
  String data_name[] = {"speed1PWM","speed2PWM","speed3PWM"};
  size_t num_data = sizeof(data) / sizeof(data[0]);
  debug_print("SpeedPWM",data,num_data,data_name);
  #endif
}

// Calculate the angle for each servo for the input turning radius
void calculateServoAngle(int radius ,int d1 , int d2 , int d3,int &thetaInnerFront , int &thetaInnerBack , int &thetaOuterFront , int &thetaOuterBack) {
  float rad = radius;
  float atanInnerFront = atan(d3 / (rad + d1));
  float atanInnerBack = atan(d2 / (rad + d1));
  float atanOuterFront = atan(d3 / (rad - d1));
  float atanOuterBack = atan(d2 / (rad - d1));
  thetaInnerFront = round((atanInnerFront * 180) / M_PI);
  thetaInnerBack = round((atanInnerBack * 180) / M_PI);
  thetaOuterFront = round((atanOuterFront * 180) / M_PI);
  thetaOuterBack = round((atanOuterBack * 180) / M_PI);

  #ifdef DEBUG
  int data[] = {thetaInnerFront,thetaInnerBack,thetaOuterFront,thetaOuterBack};
  String data_name[] = {"InnerFront","InnerBack","OuterFront","OuterBack"};
  size_t num_data = sizeof(data) / sizeof(data[0]);
  debug_print("ServoAngle",data,num_data,data_name);
  #endif
  
}

