
#include "servo.h"
#include "timer.h"
#include "derivative.h"
#include <hidef.h>

#define SERVO_CHNL   2
#define SERVO_VECTOR VectorNumber_Vtimch2

#define DELAY_1US  1
#define DELAY_1MS  (1000 * DELAY_1US)
#define DELAY_20MS (20 * DELAY_1MS)

#define MAX 2400 // pulse with for +90
#define MIN 600  // pulse with for -90

/* Globals */

static unsigned int pulse = 0;

void servo_init(void)
{
	TIMER_CHNL_MAKE_OC(SERVO_CHNL);
	TIMER_SET_OC_ACTION(SERVO_CHNL, TIMER_OC_ACTION_DRIVE_HIGH);
	
	TCHNL(SERVO_CHNL) = TCNT + DELAY_20MS;
	
	TIMER_CHNL_ENABLE_INT(SERVO_CHNL);
}

void servo_angle(unsigned int angle)
{
	unsigned int theta = angle % 180;
	float pulseWidth;
	
	pulseWidth = ((float)theta / 180.0f) * (float)(MAX + MIN);
	
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
		
			TIMER_SET_OC_ACTION(SERVO_CHNL, TIMER_OC_ACTION_DRIVE_LOW);
			TCHNL(SERVO_CHNL) = TCNT + pulse;
			
			state = TIMER_OC_ACTION_DRIVE_LOW;
		
			break;
			
		case TIMER_OC_ACTION_DRIVE_LOW:
		
			TIMER_SET_OC_ACTION(SERVO_CHNL, TIMER_OC_ACTION_DRIVE_HIGH);
			TCHNL(SERVO_CHNL) = TCNT + DELAY_20MS - pulse;
			
			state = TIMER_OC_ACTION_DRIVE_HIGH;
		
			break;
	}
	
	return;
}


