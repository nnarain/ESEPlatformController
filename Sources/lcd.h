
/**
    LCD Module Interface
    
    @author Natesh Narain
*/

#ifndef LCD_H
#define LCD_H

#define LCD_CHAR_UP     2
#define LCD_CHAR_HEART  3
#define LCD_CHAR_SMILE  4 
#define LCD_CHAR_PERSON 5
#define LCD_CHAR_DOWN   6

/**
	Initialize the LCD Display
*/
void lcd_init(void);

/**
	Write a character to the display
*/
void lcd_putc(char c);

/**
	Write a string to the display
*/
void lcd_puts(char *str);

/**
	Write a format string to the display
*/
void lcd_printf(char *fmt, ...);

/**
	Clear the display
*/
void lcd_clear(void);

#endif
