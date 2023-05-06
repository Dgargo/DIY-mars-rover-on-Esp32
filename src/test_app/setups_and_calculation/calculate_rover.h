
int process_steering(int radius_coordinate);

int process_speed(int speed_coordinate);

void calculateMotorsSpeed(int speed,int radius,int radius_coordinate,int &speed1PWM , int &speed2PWM , int &speed3PWM);

void calculateServoAngle(int radius,int &thetaInnerFront , int &thetaInnerBack , int &thetaOuterFront , int &thetaOuterBack);

