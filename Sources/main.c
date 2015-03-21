#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "sci.h"

#define FOREVER for(;;)

void main(void) 
{
  // init the serial port
  init_sci();

	EnableInterrupts;
	
	// write a message
	puts_sci("Hello World");

  FOREVER {
    _FEED_COP(); /* feeds the dog */
  }
}
