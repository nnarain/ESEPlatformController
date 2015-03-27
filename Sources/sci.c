
#include <hidef.h>
#include "derivative.h"

#include "sci.h"
#include "util.h"

#define CLK  8000000L
#define BAUD 9600

#define SCI_DIVISOR ( CLK / 16 / BAUD )

#define RTS PTP_PTP0_MASK
#define CTS PTP_PTP1_MASK

void sci_init(void)
{
  // set baud rate divisor
  SCIBD = SCI_DIVISOR;
  //SCIBD = 52;
  
  // set N81 Serial Data
  SCICR1 = 0;
  
  // enable RX and TX
  SET(SCICR2, SCICR2_RE_MASK | SCICR2_TE_MASK);
}

void sci_write(char c)
{
  while(IS_CLR(SCISR1, SCISR1_TDRE_MASK));
  SCIDRL = c;
}

char sci_read()
{
  while(IS_CLR(SCISR1, SCISR1_RDRF_MASK));
  return SCIDRL;
}

void sci_writen(char *buff, unsigned int n)
{
  unsigned int i;
  for(i = 0; i < n; ++i)
  {
    sci_write(buff[i]);
  }
}

void sci_puts(char *str)
{
  while(*str)
  {
    sci_write(*str++);
  }
}

