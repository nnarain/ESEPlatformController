
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
}

void motor_setSpeed(unsigned int speed)
{
	unsigned int duty = 100;
	
	// calculate duty from speed in cm/s
	
	// set duty cycle
	PWM_DTY_CHNL(MTR_L_EN) = speed;
	PWM_DTY_CHNL(MTR_R_EN) = speed;
}

void motor_setDirection(Motor m, MotorState state)
{
	FORCE(MTR_DIR_PORT, (MTR_DIR_MASK << m), (state << m));
}


interrupt VectorNumber_Vtimch0 void encoderL_handler(void)
{
    static unsigned int  t1 = 0;
    
    encoderLPeriod = TCHNL(ENCODER_L) - t1;
    t1 = TCHNL(ENCODER_L);

    LED_TGL(LED1_MASK);
    return;
}

interrupt VectorNumber_Vtimch1 void encoderR_handler(void)
{
    static unsigned int  t1 = 0;
    
    encoderLPeriod = TCHNL(ENCODER_R) - t1;
    t1 = TCHNL(ENCODER_R);

    LED_TGL(LED2_MASK);
	return;
}
