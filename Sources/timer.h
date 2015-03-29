
#ifndef TIMER_H
#define TIMER_H

#include "util.h"
#include "derivative.h"

/* Timer Modules Prescalers */

#define TIMER_PRESCALER_1    0x00
#define TIMER_PRESCALER_2    0x01
#define TIMER_PRESCALER_4    0x02
#define TIMER_PRESCALER_8    0x03
#define TIMER_PRESCALER_16   0x04
#define TIMER_PRESCALER_32   0x05
#define TIMER_PRESCALER_64   0x06
#define TIMER_PRESCALER_128  0x07

#define TIMER_PRESCALER_MASK 0x07

#define TIMER_SET_PRESCALER(prescale) \
  CLR(TSCR2, TIMER_PRESCALER_MASK); \
  SET(TSCR2, prescale)

/* Timer System Control */

#define TIMER_ENABLE()              SET(TSCR1, TSCR1_TEN_MASK)
#define TIMER_DISABLE()             CLR(TSCR1, TSCR1_TEN_MASK)

#define TIMER_DISABLE_ON_FREEZE()   SET(TSCR1, TSCR1_TSFRZ_MASK)
#define TIMER_ENABLE_ON_FREEZE()    CLR(TSCR1, TSCR1_TSFRZ_MASK)

#define TIMER_NORMAL_FAST_CLEAR()   CLR(TSCR1, TSCR1_TFFCA_MASK)
#define TIMER_FANCY_FAST_CLEAR()    SET(TSCR1, TSCR1_TFFCA_MASK)

/* Input Capture / Output Compare */

#define TIMER_CHNL_MAKE_OC(chnl)    SET_BIT(TIOS, chnl)
#define TIMER_CHNL_MAKE_IC(chnl)    CLR_BIT(TIOS, chnl)

#define TIMER_CHNL_ENABLE_INT(chnl) SET_BIT(TIE, chnl)

#define TIMER_CHNL_CLR_FLAG(flag)   TFLG1 = BV(flag)

/* Timer Flag Register */

#define TIMER_CHNL_EVENT(chnl)      IS_BIT_SET(TFLG1, chnl)

/*  */

#define TCHNL(chnl) EVAL(TC, chnl)

/* Named Timer Channels */

#define TIMER_CHNL_DELAY 0

/* Prototypes */

void timer_init(void);

#endif














