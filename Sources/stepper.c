
/**
	Stepper Motor Module 
	
	@author Natesh Narain
*/

#include "stepper.h"
#include "timer.h"
#include "util.h"
#include "derivative.h"
#include "adc.h"

#define STEPPER_PORT     PTT

#define STEPPER_DDR      DDRT
#define STEPPER_DDR_INIT 0xF0

#define STEP_MASK        0x07

#define STEPPER_CHNL     4

#define LIMIT_R          7
#define LIMIT_L          6

// stepper coil pattern
static char stepTable[8] = 
{
    0x80,
    0xA0,
    0x20,
    0x60,
    0x40,
    0x50,
    0x10,
    0x80
};
static char idx = 0;

static unsigned int stepsTo180;
static unsigned int stepSpeed = 5000;

static unsigned int currentCount = 0;

/* Private Prototypes */

static void stepper_home(void);

/*************************************************************************/

void stepper_init(void)
{
    // set pins 4 - 7 on the port to outcapture and set no output action
    // to configure as GPIO
    TIMER_CHNL_MAKE_OC(4);
    TIMER_CHNL_MAKE_OC(5);
    TIMER_CHNL_MAKE_OC(6);
    TIMER_CHNL_MAKE_OC(7);
    
    TIMER_SET_OC_ACTION(4, TIMER_OC_ACTION_NO_ACTION);
    TIMER_SET_OC_ACTION(5, TIMER_OC_ACTION_NO_ACTION);
    TIMER_SET_OC_ACTION(6, TIMER_OC_ACTION_NO_ACTION);
    TIMER_SET_OC_ACTION(7, TIMER_OC_ACTION_NO_ACTION);
    
    SET(STEPPER_DDR, STEPPER_DDR_INIT);
    
    // initialize the limit switch ports
    
    // set as digital GPIO
    ADC_SET_DIGITAL(LIMIT_L);
    ADC_SET_DIGITAL(LIMIT_R);
    
    // set as input
    CLR(DDRAD, BV(LIMIT_L) | BV(LIMIT_R));
    
    // home the stepper 
    stepper_home();
    
    //
    TIMER_CHNL_ENABLE_INT(STEPPER_CHNL);
}

/**
	Count the steps between the 2 limit switches and center the stepper
*/
static void stepper_home(void)
{
	// find the first limit switch
	
	// step in the opposite direction to find the next switch
	
	// record number of steps between the limits
}

interrupt VectorNumber_Vtimch4 void stepper_handler(void)
{

    unsigned char pattern = stepTable[idx];
    
    FORCE(STEPPER_PORT, 0xF0, pattern);
    
    idx = (idx + 1) & STEP_MASK;
    
    TCHNL(STEPPER_CHNL) += stepSpeed;

    return;
}