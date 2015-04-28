/**
	DC Motor Control Module
	
	Set speed and direction of motor
	Use PI Controller for feedback
	
	@author Natesh Narain
*/

#include "motors.h"
#include "timer.h"
#include "pwm.h"
#include "util.h"

#include "derivative.h"

#include "leds.h"

#define MTR_L_EN  4
#define MTR_R_EN  5

#define MTR_DIR_PORT PORTB
#define MTR_DIR_DDR  DDRB
#define MTR_DIR_INIT 0x0F

#define MTR_DIR_MASK 0x03

#define ENCODER_L 0
#define ENCODER_R 1

#define CONTROL_HANDLER VectorNumber_Vtimch5
#define CONTROL_CHNL    5

#define SAMPLE_RATE 500

#define P_GAIN 0
#define I_GAIN 0

static unsigned int setPoint;

static unsigned int encoderRPeriod;
static unsigned int encoderLPeriod;

static unsigned int vaneCountL;
static unsigned int vaneCountR;

void motors_init(void)
{
	// configure motor enables
	PWM_8BIT_MODE();
	
	PWM_SET_PRESCALE(PWM_PRESCALE_128, PWM_PRESCALE_128);
	
	PWM_SET_CLK_SOURCE(MTR_L_EN);
	PWM_SET_CLK_SOURCE(MTR_R_EN);
	
	PWM_SET_POLARITY(MTR_L_EN, PWM_POLARITY_HIGH);
	PWM_SET_POLARITY(MTR_R_EN, PWM_POLARITY_HIGH);
	
	PWM_SET_ALIGN(MTR_L_EN, PWM_LEFT_ALIGN);
	PWM_SET_ALIGN(MTR_R_EN, PWM_LEFT_ALIGN);
	
	PWM_PER_CHNL(MTR_L_EN) = 180;
	PWM_PER_CHNL(MTR_R_EN) = 180;
	
	PWM_ENABLE(BV(MTR_L_EN) | BV(MTR_R_EN));

	// configure motor direction control port
	SET(MTR_DIR_DDR, MTR_DIR_INIT);

	// configure encoder timer channels
    TIMER_CHNL_MAKE_IC(ENCODER_L);
    TIMER_SET_IC_ACTION(ENCODER_L, TIMER_IC_ACTION_RISING_EDGE);
    TIMER_CHNL_ENABLE_INT(ENCODER_L);
    
    TIMER_CHNL_MAKE_IC(ENCODER_R);
    TIMER_SET_IC_ACTION(ENCODER_R, TIMER_IC_ACTION_RISING_EDGE);
    TIMER_CHNL_ENABLE_INT(ENCODER_R);
    
    // configure the control law interrupt 
    TIMER_CHNL_MAKE_OC(CONTROL_CHNL);
    TIMER_SET_OC_ACTION(CONTROL_CHNL, TIMER_OC_ACTION_NO_ACTION);
    TIMER_CHNL_ENABLE_INT(CONTROL_CHNL);
    
    // run the control law handler
    TCHNL(CONTROL_CHNL) = TCNT + SAMPLE_RATE;
}

void motor_setSpeed(unsigned int speed)
{
	unsigned int duty = 100;
	
	// calculate setpoint
	
	// set duty cycle
	PWM_DTY_CHNL(MTR_L_EN) = speed;
	PWM_DTY_CHNL(MTR_R_EN) = speed;
}

void motor_setDirection(Motor m, MotorState state)
{
	FORCE(MTR_DIR_PORT, (MTR_DIR_MASK << m), (state << m));
}

interrupt CONTROL_HANDLER void control_handler(void)
{
	static unsigned int iE = 0; // error integral

	// calculate speed
	
	// get error
	
	// accumulate error ( error integral )
	
	//

	// set next sample time
	TCHNL(CONTROL_CHNL) += SAMPLE_RATE;

	return ;
}

interrupt VectorNumber_Vtimch0 void encoderL_handler(void)
{
    static unsigned int  t1 = 0;
    
    // calculate the period
    encoderLPeriod = TCHNL(ENCODER_L) - t1;
    t1 = TCHNL(ENCODER_L);

	// count number of encoder vanes
	vaneCountL++;

    LED_TGL(LED1_MASK);
    return;
}

interrupt VectorNumber_Vtimch1 void encoderR_handler(void)
{
    static unsigned int  t1 = 0;
    
    // calculate the period
    encoderRPeriod = TCHNL(ENCODER_R) - t1;
    t1 = TCHNL(ENCODER_R);

	// count number of encoder vanes
	vaneCountR++;

    LED_TGL(LED2_MASK);
	return;
}
