#include <Arduino.h>
#include <pwmWrite.h>

#include <config.h>

//PWM setup for DC motor
void setup_channelPWM_DC()
{
  for(int i = 0 ; i<number_channel_DC_motor  ;i++)
  {
    ledcSetup(i,freq,resolution);
  }
}
//PWM setup pin DC motor
void setup_PWM_Pin_DC()
{
    setup_channelPWM_DC();
    for(int i = 0 ;i<number_channel_DC_motor;i++)
    {
        ledcAttachPin(Arr_DC_Pin[i],i);
    }
}


