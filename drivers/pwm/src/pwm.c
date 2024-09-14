/*
 *   This concrete implementation of the PWM
 *   is for demo purposes only. The focus of this project
 *   is how to test state machines and active objects, hence
 *   this fake hardware driver module.
 */
#include "pwm.h"
#include <stdio.h>

bool PwmInit()
{
    printf("%s() executed\n", __FUNCTION__);
    return true;
}

bool PwmOff()
{
    printf("%s() executed\n", __FUNCTION__);
    return true;
}

bool PwmOn(float percent)
{
    printf("%s(%f) executed\n", __FUNCTION__, percent);
    return true;
}

uint16_t PwmFactoryTest()
{
    printf("%s() executed\n", __FUNCTION__);
    return 1;
}
