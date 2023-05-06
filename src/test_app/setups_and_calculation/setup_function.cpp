#include <Arduino.h>
#include <pwmWrite.h>


#include "config.h"


/**
 * @brief PWM setup for DC motor
 * 
 * This function initializes PWM channels and configures them for use with DC motors.
 * 
 */
void setup_channelPWM_DC()
{
  for(int i = 0 ; i<number_channel_DC_motor  ;i++)
  {
    ledcSetup(i,freq,resolution);
  }
}

/**
 * @brief Set the up PWM Pin DC motor
 * 
 * this function attaches the PWM channels to the GPIO ports of the DC motors
 */
void setup_PWM_Pin_DC()
{
    setup_channelPWM_DC();
    for(int i = 0 ;i<number_channel_DC_motor;i++)
    {
        ledcAttachPin(Arr_DC_Pin[i],i);
    }
}




