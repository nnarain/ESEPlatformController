
/**
	Servo Module 
	
	@author Natesh Narain
*/

#include "servo.h"
#include "timer.h"
#include "derivative.h"
#include <hidef.h>

#define SERVO_CHNL   2
#define SERVO_VECTOR VectorNumber_Vtimch2

#define DELAY_1US  1
#define DELAY_1MS  (1000 * DELAY_1US)
#define DELAY_20MS (20 * DELAY_1MS)

#define PULSE_MAX 2400.0f // pulse width for +90
#define PULSE_MIN 600.0f  // pulse width for -90

#define ANGLE_MAX 180.0f
#define ANGLE_MIN 0 

#define ANGLE_INIT 30

/* Globals */

// servo pulse width
static unsigned int pulse = 0;

void servo_init(void)
{
	// make an output compare
	TIMER_CHNL_MAKE_OC(SERVO_CHNL);
	
	// trigger the servo cycle to start in 20ms and drive high
	TIMER_SET_OC_ACTION(SERVO_CHNL, TIMER_OC_ACTION_DRIVE_HIGH);
	TCHNL(SERVO_CHNL) = TCNT + DELAY_20MS;
	
	servo_angle(ANGLE_INIT);
	
	// enable interrupts for the servo's timer channel
	TIMER_CHNL_ENABLE_INT(SERVO_CHNL);
}

void servo_angle(unsigned int angle)
{
	// limit angle to 180
	unsigned int theta = angle % 180;
	float pulseWidth;
	
	// scale range [0, 180] to [600, 2400]
	pulseWidth = ( ((angle - ANGLE_MIN) / (ANGLE_MAX - ANGLE_MIN)) * (PULSE_MAX - PULSE_MIN) ) + PULSE_MIN;
	
	DisableInterrupts;
	{
		pulse = (unsigned int)pulseWidth;
	}
	EnableInterrupts;
}

interrupt SERVO_VECTOR void servo_handler(void)
{
	static unsigned char state = TIMER_OC_ACTION_DRIVE_HIGH;
	
	switch(state)
	{
		case TIMER_OC_ACTION_DRIVE_HIGH:
		
			// go low after the pulse duration
			TIMER_SET_OC_ACTION(SERVO_CHNL, TIMER_OC_ACTION_DRIVE_LOW);
			TCHNL(SERVO_CHNL) = TCNT + pulse;
			
			state = TIMER_OC_ACTION_DRIVE_LOW;
		
			break;
			
		case TIMER_OC_ACTION_DRIVE_LOW:
		
			// go high after the 20ms period completes
			TIMER_SET_OC_ACTION(SERVO_CHNL, TIMER_OC_ACTION_DRIVE_HIGH);
			TCHNL(SERVO_CHNL) = TCNT + DELAY_20MS - pulse;
			
			state = TIMER_OC_ACTION_DRIVE_HIGH;
		
			break;
	}
	
	return;
}


