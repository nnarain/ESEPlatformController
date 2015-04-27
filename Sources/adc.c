
#include "adc.h"
#include "util.h"

#define ATD_OPTS (ATD_RIGHT_JUSTIFIED | ATD_DATA_UNSIGNED | ATD_ONCE | ATD_SINGLE_CHANNEL)

void adc_init(void)
{
	ATD_ON();
	ATD_FAST_FLAG_CLEAR_ON();
	
	ATD_COMPLETE_INT_DISABLE();
	
	ATD_FIFO_OFF();
	ATD_NUM_CONVERSIONS(ATD_1_CONVERSIONS);
	
	ATD_10BIT_RESOLUTION();
	ATD_SAMPLE_TIME(ATD_4CLK_PER);
	ATD_SET_PRESCALER(4);
}

unsigned int analogRead(channel_t chnl)
{
	ATD_START(ATD_OPTS, chnl & 0x07);

	while(!ATD_EVENT());

	return EXPAND_PORT( ATDDR0H );
}