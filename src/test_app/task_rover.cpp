#include <Arduino.h>
#include <AccelStepper.h>
#include <pwmWrite.h>

#include "test_app/task_rover.h"
#include "test_app/move_control/move_rover.h"
#include "test_app//move_control/move_camera.h"
#include "config.h"

//Start move
//1 turn  servos right
//2 turn  servos left
//3 move straight front
//4 move staight back
//5 move right front
//6 move right back
//7 move left front
//8 move left back
const int speed_coordinates[] = {avgPWM_value, maxPWM_value, maxPWM_value, minPWM_value, maxPWM_value, minPWM_value, maxPWM_value, minPWM_value};
const int radius_coordinates[] = {maxPWM_value, minPWM_value, avgPWM_value, avgPWM_value, maxPWM_value, maxPWM_value, minPWM_value, minPWM_value};
const int move_position_delays[] = {5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000};

//Move camera
const int camera_angle_coordinate[] ={maxPWM_value,minPWM_value};
const int camera_turn_coordinate[] = {maxPWM_value,minPWM_value};
const int move_camera_delays[] = {5000,5000};

void test_move_rover_task(void *pvParameters)
{
    int num_moves = sizeof(speed_coordinates) / sizeof(speed_coordinates[0]);
    while(true)
    {
        for(int i = 0; i < num_moves; i++)
        {
            move_rover(radius_coordinates[i], speed_coordinates[i]);
            vTaskDelay(move_position_delays[i]);
        }
    }
    
    vTaskDelete(NULL);
}

void test_move_camera_task(void *pvParameters)
{
    AccelStepper camPanStepper(1, Stepper_Step_Pin , Stepper_Dir_Pin);  //(Type:driver, STEP, DIR) - Stepper1
    Pwm servoCamTitl;
    servoCamTitl.attach(servo_Cammera_Pin);
    int num_moves = sizeof(camera_angle_coordinate) / sizeof(camera_angle_coordinate[0]);
    while(true)
    {
        for(int i = 0 ;i<num_moves;i++)
        {
            move_camera_servo(camera_angle_coordinate[i],servoCamTitl);
            vTaskDelay(move_camera_delays[i]);
            move_camera_stepper(camera_turn_coordinate[i],camPanStepper);
            vTaskDelay(move_camera_delays[i]);
        }
    }
    
    vTaskDelete(NULL);
}


