
#include "motors.h"
#include "timer.h"

#include "derivative.h"

#include "leds.h"

void motors_init(void)
{
    TIMER_CHNL_MAKE_IC(0);
    TIMER_SET_IC_ACTION(0, TIMER_IC_ACTION_RISING_EDGE);
    
    TIMER_CHNL_ENABLE_INT(0);
}

interrupt VectorNumber_Vtimch0 void motor_handler(void)
{
    LED_TGL(LED1_MASK);
    
    (void)TC0;

    return;
}
