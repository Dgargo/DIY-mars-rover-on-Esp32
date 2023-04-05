#include <AccelStepper.h>
#include <pwmWrite.h>

void move_camera_servo(int camera_angle_coordinate,Pwm servoCamTilt );

void move_camera_stepper(int camera_turn_coordinate ,AccelStepper camPanStepper);