
#include <hidef.h>
#include "derivative.h"

#include "sci.h"
#include "util.h"

#define CLK  8000000L
#define BAUD 9600

#define SCI_DIVISOR ( CLK / 16 / BAUD )

void init_sci()
{
  // set baud rate divisor
  SCIBD = SCI_DIVISOR;
  
  // set N81 Serial Data
  SCICR1 = 0;
  
  // enable RX and TX
  SET(SCICR2, SCICR2_RE_MASK | SCICR2_TE_MASK);
}

void write_sci(char c)
{
  while(IS_CLR(SCISR1, SCISR1_TDRE_MASK));
  SCIDRL = c;
}

char read_sci()
{
  while(IS_CLR(SCISR1, SCISR1_RDRF_MASK));
  return SCIDRL;
}

void writen_sci(char *buff, unsigned int n)
{
  unsigned int i;
  for(i = 0; i < n; ++i)
  {
    write_sci(buff[i]);
  }
}

void puts_sci(char *str)
{
  while(*str)
  {
    write_sci(*str++);
  }
}

