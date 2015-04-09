
/**
    SPI Module
    
    @author Natesh Narain
*/

#ifndef SPI_H
#define SPI_H

#include "util.h"
#include "derivative.h"

/* Enable and Disable the SPI System */

#define SPI_ENABLE()  SET(SPICR1, SPICR1_SPE_MASK)
#define SPI_DISABLE() CLR(SPICR1, SPICR1_SPE_MASK)

/* SPI Baud rate */
#define SPI_SET_BAUD(sppr, spr) FORCE( SPIBR, 0x77, ((spi) << 4) | (spr) )

/* Master \ Slave Mode */

#define SPI_MASTER_MODE() SET(SPICR1, SPICR1_MSTR_MASK)
#define SPI_SLAVE_MODE()  CLR(SPICR1, SPICR1_MSTR_MASK)

/* Bit Order */

#define SPI_MSB_FIRST CLR(SPICR1, SPICR1_LSBFE_MASK)
#define SPI_LSB_FIRST SET(SPICR1, SPICR1_LSBFE_MASK)

/* SPI Clock Polarity */

#define SPI_CLK_POLARITY_HIGH() CLR(SPICR1, SPICR1_CPOL_MASK)
#define SPI_CLK_POLARITY_LOW()  SET(SPICR1, SPICR1_CPOL_MASK)

/* SPI Clock Phase */

#define SPI_CLK_PHASE_ODD()  CLR(SPICR1, SPICR1_CPHA_MASK)
#define SPI_CLK_PHASE_EVEN() SET(SPICR1, SPICR1_CPHA_MASK)


/* SPI Prototypes */

void spi_putc(char c);

char spi_getc(void);

#endif
