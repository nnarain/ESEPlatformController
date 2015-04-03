
/**
    LCD Module Interface
    
    @author Natesh Narain
*/

#ifndef LCD_H
#define LCD_H

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
