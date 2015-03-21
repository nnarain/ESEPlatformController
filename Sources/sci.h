
#ifndef SCI_H
#define SCI_H


/**
  Initialize the serial port
*/
void init_sci(void);

/**
*/
void write_sci(char c);

/**
  Write n bytes from buff to the serial port
  
  @param buff
    source buffer
    
   @param n
    number of bytes to write
*/
void writen_sci(char *buff, unsigned int n);

/**
  read a byte from the serial port
*/
char read_sci();

/**
*/
void puts_sci(char *str);

#endif
