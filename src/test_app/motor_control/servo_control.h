#include "pwmWrite.h"

void servo_setup(Pwm servo ,int servo_Pin);

//trent == 0  - servo_straight_poz - deflection_angle
//trent == 1  - servo_straight_poz + deflection_angle
void servo_move(Pwm servo ,int servo_pin,int servo_straight_poz,int deflection_angle ,bool trend );

//reload function for straight move
void servo_move(Pwm servo ,int servo_pin,int servo_straight_poz);

//move all servo in one direction
void servo_move_all(Pwm servoW1,Pwm servoW3 ,Pwm servoW4 ,Pwm servoW6,int thetaInnerFront,int thetaInnerBack,int thetaOuterFront,int thetaOuterBack,int trent1,int trent3,int trent4,int trent6);

//reload for straight move
void servo_move_all(Pwm servoW1,Pwm servoW3 ,Pwm servoW4 ,Pwm servoW6);

//Move servo right
void move_servo_right(int thetaInnerFront,int thetaInnerBack,int thetaOuterFront,int thetaOuterBack);

//Move servo left
void move_servo_left(int thetaInnerFront,int thetaInnerBack,int thetaOuterFront,int thetaOuterBack);

//Move servo straight
void move_servo_straight();