
/**
	Stepper Motor Module
	
	@author Natesh Narain
*/

#ifndef STEPPER_H
#define STEPPER_H

typedef enum
{
    STEP_HALF = 1,
    STEP_FULL = 2

}StepMode;

void stepper_init(void);

void stepper_setAngle(unsigned char angle);

void stepper_setStepMode(StepMode mode);

unsigned char stepper_isBusy(void);

#endif
