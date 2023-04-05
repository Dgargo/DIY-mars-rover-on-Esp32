#include <Arduino.h>

#include "config.h"
#include "test_app/motor_control/servo_control.h"



void servo_setup(Pwm servo ,int servo_Pin)
{
  servo.attach(servoW1_Pin);
}

//trent == 0  - servo_straight_poz - deflection_angle
//trent == 1  - servo_straight_poz + deflection_angle
void servo_move(Pwm servo ,const int servo_pin,int servo_straight_poz,int deflection_angle ,int trend )
{
    servo_setup(servo,servo_pin);
    int new_angle;
    switch(trend)
    {
    case(0):
        new_angle = servo_straight_poz - deflection_angle;
        for(int i = servo_straight_poz ;i >= new_angle;i--)
        {
            servo.writeServo(servo_pin,i);
            vTaskDelay(20);
        }
        break;
    case(1):
        new_angle = servo_straight_poz + deflection_angle;
        for(int i = servo_straight_poz ;i <= new_angle;i++)
        {
            servo.writeServo(servo_pin,i);
            vTaskDelay(20);
        }
        break;
    default:
        Serial.print("error angle");
        break;
    }
}

//reload function for straight move
void servo_move(Pwm servo ,int servo_pin,int servo_straight_poz)
{
    servo_setup(servo,servo_pin);
    servo.writeServo(servo_pin,servo_straight_poz);
    vTaskDelay(20);
}

//move all servo in one direction
void servo_move_all(Pwm servoW1,Pwm servoW3 ,Pwm servoW4 ,Pwm servoW6,int thetaInnerFront,int thetaInnerBack,int thetaOuterFront,int thetaOuterBack,int trent1,int trent3,int trent4,int trent6)
{
    servo_move(servoW1,servoW1_Pin,servoW1_straight_poz,thetaInnerFront,trent1);
    servo_move(servoW3,servoW3_Pin,servoW3_straight_poz,thetaInnerBack,trent3);
    servo_move(servoW4,servoW4_Pin,servoW4_straight_poz,thetaOuterFront,trent4);
    servo_move(servoW6,servoW6_Pin,servoW6_straight_poz,thetaOuterBack,trent6);
}

//reload for straight move
void servo_move_all(Pwm servoW1,Pwm servoW3 ,Pwm servoW4 ,Pwm servoW6)
{
    servo_move(servoW1,servoW1_Pin,servoW1_straight_poz);
    servo_move(servoW3,servoW3_Pin,servoW3_straight_poz);
    servo_move(servoW4,servoW4_Pin,servoW4_straight_poz);
    servo_move(servoW6,servoW6_Pin,servoW6_straight_poz);
}
//Move servo right
void move_servo_right(int thetaInnerFront,int thetaInnerBack,int thetaOuterFront,int thetaOuterBack)
{
    Pwm servoW1;
    Pwm servoW3;
    Pwm servoW4;
    Pwm servoW6;
    servo_move_all(servoW1,servoW3,servoW4,servoW6,thetaInnerFront,thetaInnerBack,thetaOuterFront,thetaOuterBack,1,0,1,0);
    
}

//Move servo left
void move_servo_left(int thetaInnerFront,int thetaInnerBack,int thetaOuterFront,int thetaOuterBack)
{
    Pwm servoW1;
    Pwm servoW3;
    Pwm servoW4;
    Pwm servoW6;
    servo_move_all(servoW1,servoW3,servoW4,servoW6,thetaInnerFront,thetaInnerBack,thetaOuterFront,thetaOuterBack,0,1,0,1);
}

//Move servo straight
void move_servo_straight()
{
    Pwm servoW1;
    Pwm servoW3;
    Pwm servoW4;
    Pwm servoW6;
    servo_move_all(servoW1,servoW3,servoW4,servoW6);
}