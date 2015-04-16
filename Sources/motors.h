
/**
    DC Motor Control Module
    
    @author Natesh Narain
*/

#ifndef MOTORS_H
#define MOTORS_H

// motor selection
typedef enum
{
	MTR_L = 0,
	MTR_R = 2
}Motor;

// motor state
typedef enum
{
	MTR_STATE_OFF,
	MTR_STATE_FORWARD,
	MTR_STATE_BACKWARD

}MotorState;

/**
    Initialize the motor ports
*/
void motors_init(void);

/**
    Set the motor speedin centimeter per second
*/
void motor_setSpeed(unsigned int speed);

/**
    Set the motor direction
    
    @param m 
        Either the left or right motor
        
    @param state
        The updated motor state
*/
void motor_setDirection(Motor m, MotorState state);

#endif
