
//set arr arr for right move
int* get_pwm_values_right(int speed1PWM, int speed2PWM, int speed3PWM);

//set arr arr for left move
int* get_pwm_values_left(int speed1PWM, int speed2PWM, int speed3PWM);

//move DC motor 
void move_sideways(int channel_side[] , int LOW_pin[],int speed1PWM ,int speed2PWM ,int speed3PWM,int* (*get_pwm_values)(int,int,int));

//move DC motors at the  straight motion
//front Channel_num == 0
//back Channel_num == 1
void move_straight(int speed1PWM,int channel_Num);