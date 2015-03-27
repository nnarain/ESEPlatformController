#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "sci.h"
#include "leds.h"
#include "lcd.h"

#include "util.h"
#include "delay.h"

/* Prototypes */

void init_modules(void);


void main(void) 
{
    init_modules();

    for(;;)
    {
        //sci_puts("Natesh Narain\n\r");
        char c = sci_read();
        lcd_putc(c);
        delay_ms(1);
    }

    EnableInterrupts;

    //FOREVER {
    //_FEED_COP(); /* feeds the dog */
   // }
}

void init_modules(void)
{
    LEDS_INIT();
    sci_init();
    lcd_init();
}