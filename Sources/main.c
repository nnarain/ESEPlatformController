#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "sci.h"
#include "leds.h"
#include "util.h"
#include "delay.h"

#define FOREVER for(;;)


void main(void) 
{
    LEDS_INIT();
    
    LED_ON(LED1);
    LED_OFF(LED2);

    for(;;)
    {
        LED_TGL(LED1 | LED2);
        delay_ms(1000);
    }

   // EnableInterrupts;

    //FOREVER {
    //_FEED_COP(); /* feeds the dog */
   // }
}
