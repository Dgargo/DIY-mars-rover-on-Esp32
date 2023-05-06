
// ------ PIN CONFIG ---------------------------------------------------------
//Set DC motor pin
#define motorW1_IN1 GPIO_NUM_15
#define motorW1_IN2 GPIO_NUM_12

#define motorW2_IN1 GPIO_NUM_0
#define motorW2_IN2 GPIO_NUM_4

#define motorW3_IN1 GPIO_NUM_16
#define motorW3_IN2 GPIO_NUM_17

#define motorW4_IN1 GPIO_NUM_5
#define motorW4_IN2 GPIO_NUM_18

#define motorW5_IN1 GPIO_NUM_19
#define motorW5_IN2 GPIO_NUM_21

#define motorW6_IN1 GPIO_NUM_22
#define motorW6_IN2 GPIO_NUM_23

//Set servo pin
#define servoW1_Pin GPIO_NUM_13
#define servoW3_Pin GPIO_NUM_12
#define servoW4_Pin GPIO_NUM_14
#define servoW6_Pin GPIO_NUM_27
#define servo_Cammera_Pin GPIO_NUM_33

#define DEBUG

const int Arr_DC_Pin[]= {motorW1_IN1,motorW1_IN2,motorW2_IN1,motorW2_IN2,motorW3_IN1,motorW3_IN2,motorW4_IN1,motorW4_IN2,motorW5_IN1,motorW5_IN2,motorW6_IN1,motorW6_IN2};
//Set stepper pin 
#define Stepper_Step_Pin GPIO_NUM_26
#define Stepper_Dir_Pin GPIO_NUM_25
//---------------------------------------------------------------------------

//variables for calculating motion
const float d1 = 271; // distance in mm
const float d2 = 278;
const float d3 = 301;
const float d4 = 304;

const int min_radius = 600;
const int max_radius = 1400;
const int avg_radius = 1000;
//------ SERVO CONFIG --------------------------------------------------------------
const int servoW1_straight_poz = 90 ;
const int servoW3_straight_poz = 90 ;
const int servoW4_straight_poz = 90 ;
const int servoW6_straight_poz = 90 ;
//-----------------------------------------------------------------------------------

//------ PWM CONFIG ---------------------------------------------------------
const int freq = 30;//set PWM frequency of 30 Hz for DC Motor
const int number_channel_DC_motor = 12;
const int Arr_channel_DC_motor[] = {0,1,2,3,4,5,6,7,8,9,10,11};
//set 8 bits resolution 
/*
const int resolution = 8;
const int minPWM_value  = 0 ;
const int maxPWM_value  = 256;
const int avgPWM_value  = 128;
*/

//set 10 bits resolution 
/*
const int resolution = 10;
const int minPWM_value  = 0 ;
const int maxPWM_value  = 1024;
const int avgPWM_value  = 512;
*/

//set 12 bits resolution 

const int resolution = 12;
const int minPWM_value  = 0 ;
const int maxPWM_value  = 4096;
const int avgPWM_value  = 2048;


//------ CAMERA CONFIG --------------------------------
const int camera_head_move_delay = 20;
const int camera_head_min_pozition = 35;
const int camera_head_max_pozition = 165;
//----------------------------------------------------





