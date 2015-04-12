#include "delay.h"

void delay_ms(word ms)
{
	int i;
	
	// set 1 ms into future
	TC3 = TCNT + 1000;
	
	// enable TCO for OC
	TIMER_CHNL_MAKE_OC(3);
	
	for(i = ms; i >= 0; --i)
	{
		// wait for timer channel 0 event
		while(!TIMER_CHNL_EVENT(3));
		TC3 += 1000;
	}

	// turn off OC on TC0
	CLR_BIT(TIOS, 3);
}

void delay_us(word us)
{
	word i;
	
	// set 1 ms into future
	TC3 = TCNT + 1;
	
	// enable TCO for OC
	TIMER_CHNL_MAKE_OC(3);
	
	for(i = us; i >= 0; --i)
	{
		// wait for timer channel 0 event
		while(!TIMER_CHNL_EVENT(3));
		TC3 += 1;
	}

	// turn off OC on TC0
	CLR_BIT(TIOS, 3);
}
