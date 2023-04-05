//calculate radius and speed
void process_steering_and_speed(int radius_coordinate ,int speed_coordinate ,int &radius ,int &speed);

//calculate DC motor speed
void calculateMotorsSpeed(int speed,int radius,int radius_coordinate,int &speed1PWM , int &speed2PWM , int &speed3PWM);

// Calculate the angle for each servo for the input turning radius
void calculateServoAngle(int radius ,int d1 , int d2 , int d3,int &thetaInnerFront , int &thetaInnerBack , int &thetaOuterFront , int &thetaOuterBack);

