/**
	Testing the ESE Platform Controller Code
	
	@author Natesh Narain
*/

#include <hidef.h>
#include "derivative.h"

// include modules
#include "sci.h"
#include "leds.h"
#include "lcd.h"
#include "delay.h"
#include "timer.h"
#include "client.h"
#include "servo.h"
#include "stepper.h"
#include "motors.h"

#include <stdio.h>
#include <string.h>

/* Prototypes */

static void init_modules(void);
static void timer_init(void);

static void sync(void);
static int dispatch(char * packet);

void main(void) 
{
	char packet[20];

	init_modules();

	EnableInterrupts;

	// loop forever
	for(;;)
	{
		// wait for the host to sync
	    sync();
	
		// main packet reading loop
        for(;;)
        {
        	// check for communication errors with the host
            if(!client_comError())
            {
            	// check if there are packets available in the buffer
                if(client_isPacketAvailable())
                {
                	// retrieve the packet from the buffer
                    if(client_getNextPacket(packet))
                    {
                    	// dispatch the packet command
                        if(!dispatch(packet))
                        {
                        	// return to sync mode on error
                        	break;
                        }
                    }
                    else
                    {
                    	// return to sync mode on error
                        break;
                    }
                }
            }
            else
            {
            	// return to sync mode on error
                break;
            }
        }
	}
	
	//
}

static void sync(void)
{
    lcd_clear();
    
	lcd_puts("Syncing...");
	
	client_syncHost();
	
	lcd_clear();
	
	lcd_printf("%s %c%c", "Host Synced", LCD_CHAR_UP, LCD_CHAR_DOWN);
}

static int dispatch(char * packet)
{
	char cmd[5];
	int ret = 1;
	
	if(client_parsePacketCommand(packet, cmd))
	{
		if(strcmp(cmd, PING) == 0)
		{
			client_ping();
		}
		else if(strcmp(cmd, SERVO) == 0)
		{
		    unsigned int angle;;
		    ret = client_parsePacketArguments(packet, "%d", &angle) == 1;
		    
		    if(ret)
		        servo_angle(angle);
		}
		else if(strcmp(cmd, STEP) == 0)
		{
		    unsigned int angle;
		    ret = client_parsePacketArguments(packet, "%d", &angle) == 1;
		    
		    if(ret)
		        stepper_setAngle(angle);
		}
		else if(strcmp(cmd, MTR_SPEED) == 0)
		{
			unsigned int speed;
			ret = client_parsePacketArguments(packet, "%d", &speed) == 1;
			
			if(ret)
				motor_setSpeed(speed);
		}
		else if(strcmp(cmd, MTR_DIR) == 0)
		{
			int mtr;
			MotorState state;
			ret = client_parsePacketArguments(packet, "%d %d", &mtr, &state) == 2;
			
			if(ret)
				motor_setDirection((Motor)(mtr * 2), state);
		}
		else if(strcmp(cmd, ECHO) == 0)
		{
		    char msg[20];
		    ret = client_parsePacketArguments(packet, "%s", msg) == 1;
		    client_echo(msg);
		}
		else
		{
			ret = 0;
		}
	}
	
	return ret;
	
}

static void init_modules(void)
{
	timer_init();
	sci_init();
	servo_init();
	motors_init();
	LEDS_INIT();
	
	lcd_init();
	
	stepper_init();
	stepper_setAngle(90);
}

static void timer_init(void)
{
	TIMER_SET_PRESCALER(TIMER_PRESCALER_8);

	TIMER_DISABLE_ON_FREEZE();
	TIMER_FANCY_FAST_CLEAR();
	
	TIMER_ENABLE();
}