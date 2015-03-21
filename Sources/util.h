
/**
  Bit operation macros
  
  @author Natesh Narain
*/

#ifndef UTIL_H
#define UTIL_H

//! Bit value
#define BV(b) (1 << b)

//! set mask y in x
#define SET(x, y) (x |= y)
//! clear mask y in x
#define CLR(x, y) (x &= ~y)
//! toggle mask y in x
#define TGL(x, y) (x ^= y)

//! set bit y in x
#define SET_BIT(x, y) ( SET( x, BV(y) ) )
//! clear bit y in x
#define CLR_BIT(x, y) ( CLR( x, BV(y) ) )
//! toggle bit y in x
#define TGL_BIT(x, y) ( TGL( x, BV(y) ) )

//! check if mask y is set in x
#define IS_SET(x, y) ( x & y )
//! check if mask y is clear in x
#define IS_CLR(x, y) !( x & y )
//! check if bit y is set in x
#define IS_BIT_SET(x,y) ( IS_SET(x, BV(y)) )
//! check if bit y is clear in x
#define IS_BIT_CLR(x,y) ( IS_CLR(x, BV(y)) )

/* Bit pattern concatenation macros  */

#define BIT_CAT(x, y, bits) ((x<<bits) + y)
#define NIB_CAT(x, y)       ( BIT_CAT(x, y, 4) )
#define BYTE_CAT(x,y)       ( BIT_CAT(x, y, 8) )
#define WORD_CAT(x,y)       ( BIT_CAT(x, y, 16) )

#endif
