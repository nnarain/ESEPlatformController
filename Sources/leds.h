
#ifndef LEDS_H
#define LEDS_H

#define LED_PORT      PTS
#define LED1          PTS_PTS2_MASK
#define LED2          PTS_PTS3_MASK

#define LED_DDR       DDRS
#define LED_DDR_INIT  ( DDRS_DDRS2_MASK | DDRS_DDRS3_MASK ) 

#define LEDS_INIT()   SET(LED_DDR, LED_DDR_INIT)

#define LED_ON(mask)  SET(LED_PORT, mask)
#define LED_OFF(mask) CLR(LED_PORT, mask)
#define LED_TGL(mask) TGL(LED_PORT, mask)


#endif
