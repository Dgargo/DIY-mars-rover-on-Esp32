#include <Arduino.h>
#include "config.h"
#include "debug_app/debug_claculate_value.h"
#include "setup_function.h"




/**
 * @brief radius calculation for steering
 *
 * This function calculates the radius based on the input parameter.
 * 
 * if radius_coordinate>avg_PWM : then the radius is set for a right movement.
 * 
 * if radius_coordinate<avg_PWM :  then the radius is set for a left movement.
 * 
 * if radius_coordinate= avg_PWM : then the radius is set to an average value for straight movement.
 * 
 * @param radius_coordinate[in]  from control devise
 * @return radius 
 *
 * @note This function returns -1 if the parameter is false.
 */
int process_steering(int radius_coordinate)
{
 int radius = 0;
 bool check_input = check_input_parameters(3,minPWM_value,maxPWM_value,radius_coordinate);
 if(check_input == false)
  {
    Serial.println("incorrect parameters");
    Serial.println(radius_coordinate);
    return -1;
  }
  else
  {
    #ifdef DEBUG
    int data[] = {radius_coordinate};
    String data_name[] = {"radius_coor"};
    size_t num_data1 = sizeof(data) / sizeof(data[0]);
    debug_print("radius coor",data,num_data1,data_name);
    #endif

    if(radius_coordinate > avgPWM_value)//Steering right
    {
      radius =map(radius_coordinate,avgPWM_value,maxPWM_value,max_radius,min_radius);// turining radius from 1400mm to 600mm 
    }
    else if(radius_coordinate < avgPWM_value)//Steering left
    {
      radius =map(radius_coordinate,avgPWM_value,minPWM_value,min_radius,max_radius);// turining radius from 600mm to 1400mm
    } 
    else
    {
      radius = avg_radius;//setup average radius
    }
    #ifdef DEBUG
    int data2[] = {radius};
    String data_name2[] = {"radius"};
    size_t num_data2 = sizeof(data) / sizeof(data[0]);
    debug_print("radius and speed",data2,num_data2,data_name2);
    #endif
    return radius;
  }
}

/**
 * @brief general speed calculation 
 *
 * This function calculates the speed based on the input parameter
 * 
 * if speed_coordinate>avg_PWM : then the speed is set to move forward.

 * if speed_coordinate<avg_PWM : then the speed is set to move backward.
 * 
 * if speed_coordinate=avg_PWM : then the speed is set to an average value to 
 * 
 * @param speed_coordinate[in] parameter from control device
 * @return speed 
 * 
 * @note This function returns -1 if the parameter is false.
 */
int process_speed(int speed_coordinate)
{
  int speed = 0;
  bool check_input = check_input_parameters(4,minPWM_value,maxPWM_value,speed_coordinate,speed);
  if(check_input == false)
  {
    Serial.println(speed_coordinate);
    Serial.println("incorrect parameters");
    return -1;
  }
  else
  {
    #ifdef DEBUG
    int data[] = {speed_coordinate};
    String data_name[] = {"speed_coor"};
    size_t num_data1 = sizeof(data) / sizeof(data[0]);
    debug_print("speed coor",data,num_data1,data_name);
    #endif

    if(speed_coordinate ==avgPWM_value)
    {
      speed = 0;//stop
    }
    else if(speed_coordinate > avgPWM_value)
    {
      speed = map(speed_coordinate,avgPWM_value,maxPWM_value,0,100);//move forward
    }
    else
    {
      speed = map(speed_coordinate,minPWM_value,avgPWM_value,0,100);//move backward
    }
 
    #ifdef DEBUG
    int data2[] = {speed};
    String data_name2[] = {"speed"};
    size_t num_data2 = sizeof(data) / sizeof(data[0]);
    debug_print("speed",data2,num_data2,data_name2);
    #endif

    return speed;
  }
}
/**
 * @brief calculation DC motor speed in PWM value
 * 
 * This function calculates the speed and converts it into a PWM signal.
 * 
 * The calculations depend on the turning radius of the wheels.
 * 
 * If the radius_coordinate is equal to avg_PWM, then the speed on all wheels will be the same.
 * 
 * Otherwise, the necessary calculations will be performed
 * 
 * @param speed[in]  speed in procent value
 * @param radius[in] radius in  from 600 to 1400 mm
 * @param radius_coordinate[in]   input parameter from control devise
 * 
 * @param speedPWM[out] in PWM value 
 * @param speed1PWM first speed 
 * @param speed2PWM second speed
 * @param speed3PWM third speed
 * 
 * @note exit function if values ​​are not correct
 */
void calculateMotorsSpeed(int speed,int radius,int radius_coordinate,int &speed1PWM , int &speed2PWM , int &speed3PWM) 
{
  int speed1, speed2, speed3 = 0;
  bool check_input = check_input_parameters(5,minPWM_value,maxPWM_value,speed,radius,radius_coordinate); 
  if(check_input == false)
  {
    #ifdef DEBUG
    Serial.println("calculateMotorsSpeed");
    Serial.printf("%d , %d , %d , %d, %d , %d, %d , %d \n",minPWM_value,maxPWM_value,speed,radius,radius_coordinate);
    #endif
    Serial.println("incorrect parameters");
    return ;
  }
  else
  {
    if(speed == 0) //stop
    {
    speed1PWM = 0;
    speed2PWM = 0;
    speed3PWM = 0;
    return;
    }
    // if no steering, all wheels speed is the same - straight move
    if (radius_coordinate == avgPWM_value) 
    {
      speed1 = speed2 = speed3 = speed;
    }
    // when steering, wheels speed depend on the turning radius value
    else 
    {
      speed1 = speed;
    
      speed2 = speed * sqrt(d3*d3 + pow((radius - d1), 2)) / (radius + d4);
    
      speed3 = speed * (radius - d4) / (radius + d4);
    }
    //convert speed to PWM signal value
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
}


/**
 * @brief Calculate the angle for each servo for the input turning radius
 * 
 * This function calculates the angle of rotation for each servo based on the input radius parameter. 
 * 
 * The calculation is performed in two steps: 
 * 
 * first, the angle is calculated in radians,and then it is rounded to the nearest integer value in degrees.
 * 
 * @param radius[in] radius in  from 600 to 1400 mm
 * 
 * @param thetaAngle[out] servo deflection angles
 * @param thetaInnerFront inner front
 * @param thetaInnerBack  inner back
 * @param thetaOuterFront outher front
 * @param thetaOuterBack  outher back
 * 
 * @note exit function if values ​​are not correct
 */
void calculateServoAngle(int radius,int &thetaInnerFront , int &thetaInnerBack , int &thetaOuterFront , int &thetaOuterBack) 
{
  bool check_input = check_input_parameters(3,minPWM_value,max_radius,radius);
  if(check_input == false)
  {
    #ifdef DEBUG
    Serial.println("calculateServoAngle");
    Serial.printf("%d , %d , %d , %d, %d , %d, %d , %d \n",minPWM_value,max_radius,radius);
    #endif
    Serial.println("incorrect parameters");
    return ;
  }
  else
  {
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
  
  
}

