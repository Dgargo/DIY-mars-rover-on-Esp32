
#include <unity.h>
#include <stdio.h>

#include "embedded_app/calculate_rover.hpp"

//radius test
void test_process_steering_right()
{
    int radius_coordinate = maxPWM_value;
    int expected = min_radius; 
    int actual =  process_steering(radius_coordinate);
    TEST_ASSERT_EQUAL_INT32(expected, actual);
}

void test_process_steering_left()
{
    int radius_coordinate = minPWM_value;
    int expected = max_radius; 
    int actual =  process_steering(radius_coordinate);
    TEST_ASSERT_EQUAL_INT32(expected, actual);
}

//speed test
void test_process_speed_max()
{
    int speed_coordinate = maxPWM_value;
    int expected = 100;
    int actual = process_speed(speed_coordinate);
    TEST_ASSERT_EQUAL_INT32(expected,actual);
}
void test_process_speed_min()
{
    int speed_coordinate = 0;
    int expected = 0;
    int actual = process_speed(speed_coordinate);
    TEST_ASSERT_EQUAL_INT32(expected,actual);
}


void test_calculate_motors_speed_steering_right_max()
{
    int radius_coordinate = maxPWM_value;
    int radius = process_steering(radius_coordinate);
    int speed = 100;
    int expected[] = {maxPWM_value,2007,1310};
    int actual[3];
    int size = sizeof(actual) / sizeof(actual[0]);
    int *actual_ptr = calculateMotorsSpeed(speed,radius,radius_coordinate);
    for (int i = 0; i < size; i++) {
    actual[i] = actual_ptr[i];
    }

    TEST_ASSERT_EQUAL_INT_ARRAY(expected,actual,size);
     free(actual_ptr);
}

void test_calculate_motors_speed_steering_left_max()
{
    int radius_coordinate = minPWM_value;
    int radius = process_steering(radius_coordinate);
    int speed = 100;
    int expected[] = {maxPWM_value,2785,2621};
    int actual[3];
    int size = sizeof(actual) / sizeof(actual[0]);
    int *actual_ptr = calculateMotorsSpeed(speed,radius,radius_coordinate);
    for (int i = 0; i < size; i++) {
    actual[i] = actual_ptr[i];
    }

    TEST_ASSERT_EQUAL_INT_ARRAY(expected,actual,size);
    free(actual_ptr);
}

void test_calculate_motors_speed_steering_min()
{
    int radius_coordinate = maxPWM_value;
    int radius = process_steering(radius_coordinate);
    int speed = 0;
    int expected[] = {0,0,0};
    int actual[3];
    int size = sizeof(actual) / sizeof(actual[0]);
    int *actual_ptr = calculateMotorsSpeed(speed,radius,radius_coordinate);
    for (int i = 0; i < size; i++) {
    actual[i] = actual_ptr[i];
    }
    TEST_ASSERT_EQUAL_INT_ARRAY(expected,actual,size);
     free(actual_ptr);
}


void test_calculate_motors_speed_straight_max()
{
    int radius_coordinate = avgPWM_value;
    int radius = process_steering(radius_coordinate);
    int speed = 100;
    int expected[] = {maxPWM_value,maxPWM_value,maxPWM_value};
    int actual[3];
    int size = sizeof(actual) / sizeof(actual[0]);
    int *actual_ptr = calculateMotorsSpeed(speed,radius,radius_coordinate);
    for (int i = 0; i < size; i++) {
    actual[i] = actual_ptr[i];
    }
    TEST_ASSERT_EQUAL_INT_ARRAY(expected,actual,size);
    free(actual_ptr);
}

void test_calculate_motors_speed_straight_min()
{
    int radius_coordinate = avgPWM_value;
    int radius = process_steering(radius_coordinate);
    int speed = 0;
    int expected[] = {0,0,0};
    int actual[3];
    int size = sizeof(actual) / sizeof(actual[0]);
    int *actual_ptr = calculateMotorsSpeed(speed,radius,radius_coordinate);
    for (int i = 0; i < size; i++) {
    actual[i] = actual_ptr[i];
    }
    TEST_ASSERT_EQUAL_INT_ARRAY(expected,actual,size);
    free(actual_ptr);
}

void test_calculate_servo_angle_right()
{
    int radius_coordinate = maxPWM_value;
    int radius = process_steering(radius_coordinate);
    int expected[] = {19,18,42,40};
    int actual[4];
    int size = sizeof(actual) / sizeof(actual[0]);
    int *actual_ptr = calculateServoAngle(radius);
    for (int i = 0; i < size; i++) {
    actual[i] = actual_ptr[i];
    }
    TEST_ASSERT_EQUAL_INT_ARRAY(expected,actual,size);
    free(actual_ptr);
}

void test_calculate_servo_angle_left()
{
    int radius_coordinate = min_radius;
    int radius = process_steering(radius_coordinate);
    int expected[] = {10,9,15,14};
    int actual[4];
    int size = sizeof(actual) / sizeof(actual[0]);
    int *actual_ptr = calculateServoAngle(1400);
    for (int i = 0; i < size; i++) {
    actual[i] = actual_ptr[i];
    }
    TEST_ASSERT_EQUAL_INT_ARRAY(expected,actual,size);
    free(actual_ptr);
}