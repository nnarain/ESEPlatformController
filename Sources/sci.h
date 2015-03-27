
#ifndef SCI_H
#define SCI_H


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
