
#ifndef MOTORS_H
#define MOTORS_H

typedef enum
{
	MTR_L = 0,
	MTR_R = 2
}Motor;

typedef enum
{
	MTR_STATE_OFF,
	MTR_STATE_FORWARD,
	MTR_STATE_BACKWARD

}MotorState;

void motors_init(void);

void motor_setSpeed(unsigned int speed);

void motor_setDirection(Motor m, MotorState state);

#endif
