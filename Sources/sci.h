
/**
	Serial Communication Interface
	
	@author Natesh Narain
*/

#ifndef SCI_H
#define SCI_H

#include "util.h"
#include "derivative.h"

#define SCI_TDRE IS_SET(SCISR1, SCISR1_TDRE_MASK)
#define SCI_TC   IS_SET(SCISR1, SCISR1_TC_MASK  )
#define SCI_RDRF IS_SET(SCISR1, SCISR1_RDRF_MASK)
#define SCI_NF   IS_SET(SCISR1, SCISR1_NF_MASK  )
#define SCI_FE   IS_SET(SCISR1, SCISR1_FE_MASK  )
#define SCI_PF   IS_SET(SCISR1, SCISR1_PF_MASK  )

/**
  Initialize the serial port
*/
void sci_init(void);

/**
*/
void sci_write(char c);

/**
  Write n bytes from buff to the serial port
  
  @param buff
    source buffer
    
   @param n
    number of bytes to write
*/
void sci_writen(char *buff, unsigned int n);

/**
  read a byte from the serial port
*/
char sci_read(void);

/**
*/
void sci_puts(char *str);

#endif
