
/**
    LCD Module Interface
    
    @author Natesh Narain
*/

#ifndef LCD_H
#define LCD_H

void lcd_init(void);

void lcd_putc(char c);
void lcd_puts(char *str);

void lcd_printf(char *fmt, ...);

#endif
