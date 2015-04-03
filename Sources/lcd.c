
#include "lcd.h"
#include "derivative.h"

#include "util.h"
#include "delay.h"

#include <stdio.h>

#define LCD_PORT     PORTA 
#define LCD_DDR      DDRA
#define LCD_DDR_INIT 0xFF

#define LCD_E_MASK   PORTA_BIT4_MASK
#define LCD_RS_MASK  PORTA_BIT5_MASK
#define LCD_RW_MASK  PORTA_BIT6_MASK
#define LCD_BUS_MASK 0x0Fu

#define LCD_BUSY_MASK 0x80

#define LCD_E_LO() ( CLR(LCD_PORT, LCD_E_MASK) )
#define LCD_E_HI() ( SET(LCD_PORT, LCD_E_MASK) )

#define LCD_BUS(value) ( FORCE(LCD_PORT, LCD_BUS_MASK, value) )

// select lcd user registers
#define LCD_RS_DR() ( SET(LCD_PORT, LCD_RS_MASK) ) // select data register
#define LCD_RS_IR() ( CLR(LCD_PORT, LCD_RS_MASK) ) // select instruction register

// set lcd R/~W line
#define LCD_RW_WRITE() ( CLR(LCD_PORT, LCD_RW_MASK) ) // write mode
#define LCD_RW_READ()  ( SET(LCD_PORT, LCD_RW_MASK) )  // read mode

// lcd commands and configuration

#define LCD_CMD_SET_DDRAM    BV(7)
#define LCD_DDRAM_MASK       0x7F

#define LCD_CMD_SET_CGRAM    BV(6)
#define LCD_CGRAM_LOC(loc)   ( ( (loc) & 0x07 ) << 3 )
#define LCD_CGRAM_ROW(r)     ( (r) & 0x07 )
#define LCD_CGRAM_DATA_MASK  0x1F

#define LCD_CMD_FUNCTION     BV(5)
#define LCD_2_LINE           BV(3)
#define LCD_1_LINE           (0)
#define LCD_FONT_5X10        BV(2)
#define LCD_FONT_5X7         (0)
#define LCD_MODE_8BIT        BV(4)
#define LCD_MODE_4BIT        (0)

#define LCD_CMD_CURSOR       BV(4)
#define LCD_CURSOR_SHIFT_L   0x00
#define LCD_CURSOR_SHIFT_R   0x04

#define LCD_CMD_DISPLAY      BV(3)
#define LCD_DISPLAY_ON       BV(2)
#define LCD_DISPLAY_OFF      (0)
#define LCD_CURSOR_ON        BV(1)
#define LCD_CURSOR_OFF       (0)
#define LCD_BLINK_ON         BV(0)
#define LCD_BLINK_OFF        (0)

#define LCD_CMD_ENTRY        BV(2)
#define LCD_INCREMENT_CURSOR BV(1)
#define LCD_DECREMENT_CURSOR (0)
#define LCD_SHIFT_WINDOW_ON  BV(0)
#define LCD_SHIFT_WINDOW_OFF (0)

#define LCD_CMD_CLR_DISPLAY  0x01
#define LCD_CMD_HOME_CURSOR  0x02

// escape characters
#define ESC_LINE_FEED '\n'
#define ESC_HOME      '\r'

/* Private Prototypes */

static void lcd_data(unsigned char data);
static void lcd_cmd(unsigned char cmd);

static unsigned char lcd_read(void);

static void lcd_wait(void);

// create a custom character in CG RAM
static void lcd_cgram(char * buffer, char rows, char loc);

/* custom character data */

// Up Arrow
static char upArrow[8] = 
{
	0b00000100,
	0b00001110,
	0b00011111,
	0b00000100,
	0b00000100,
	0b00000100,
	0b00000100,
	0b00000000
};

static char heart[8] = 
{
	0b00000000,
	0b00001010,
	0b00011111,
	0b00011111,
	0b00011111,
	0b00001110,
	0b00000100,
	0b00000000
};

static char smile[8] = 
{
	0b00000000,
	0b00000000,
	0b00001010,
	0b00000000,
	0b00010001,
	0b00001110,
	0b00000000,
	0b00000000
};

static char person[8] = 
{
	0b00000100,
	0b00001010,
	0b00000100,
	0b00010101,
	0b00001110,
	0b00000100,
	0b00001010,
	0b00001010
};

/**
	Initialize the LCD in 4-bit 2 Line mode 
*/
void lcd_init(void)
{
    // set lcd port directions
    SET(LCD_DDR, LCD_DDR_INIT);
    
    // wait 20 ms for power to initialize
    delay_ms(20);
    
    // set to 4-bit mode
    LCD_E_HI();
    LCD_BUS( 0x03 ); // wake up and sync
    LCD_E_LO();
    
    delay_ms(5);
    
    LCD_E_HI();
    LCD_BUS(0x03); // wake up and sync
    LCD_E_LO();
    
    delay_ms(1);
    
    LCD_E_HI();
    LCD_BUS(0x03); // wake and sync
    LCD_E_LO();
    
    LCD_E_HI();
    LCD_BUS(0x02); // wake and sync - go to 4-bit mode
    LCD_E_LO();
    
    delay_ms(2);
    
    // configure display
    lcd_cmd(LCD_CMD_FUNCTION | LCD_MODE_4BIT | LCD_2_LINE | LCD_FONT_5X7);
    lcd_cmd(LCD_CMD_DISPLAY | LCD_DISPLAY_OFF);
    
    lcd_clear();
    
    lcd_cmd(LCD_CMD_ENTRY | LCD_INCREMENT_CURSOR | LCD_SHIFT_WINDOW_OFF);
    lcd_cmd(LCD_CMD_DISPLAY | LCD_DISPLAY_ON | LCD_CURSOR_ON | LCD_BLINK_ON);
    
    delay_ms(2);
    
    // generate custom characters
    lcd_cgram(upArrow, 8, LCD_CHAR_UP);
    lcd_cgram(heart,   8, LCD_CHAR_HEART);
    lcd_cgram(smile,   8, LCD_CHAR_SMILE);
    lcd_cgram(person,  8, LCD_CHAR_PERSON);
}

// write a character to the display
void lcd_putc(char c)
{
    lcd_data(c);
}

void lcd_puts(char *str)
{
    while(*str)
    {
        switch(*str)
        {
            case ESC_LINE_FEED:
                lcd_cmd(LCD_CMD_SET_DDRAM | 0x40);
                break;
                
            case ESC_HOME:
                lcd_cmd(LCD_CMD_HOME_CURSOR);
                break;
                
            default:
                lcd_putc(*str);
                break;
        }
        
        str++;
    }
}

void lcd_printf(char *fmt, ...)
{
    va_list args;
    char buffer[32 + 1];
    
    va_start(args, fmt);
    vsprintf(buffer, fmt, args);
    va_end(args);
    
    lcd_puts(buffer);
}

void lcd_clear(void)
{
	lcd_cmd(LCD_CMD_CLR_DISPLAY);
}

static void lcd_cgram(char * buffer, char rows, char loc)
{
	char n;
	for(n = 0; n < rows; ++n)
	{
		lcd_cmd(LCD_CMD_SET_CGRAM | LCD_CGRAM_LOC(loc) | LCD_CGRAM_ROW(n));
		lcd_data(buffer[n] & LCD_CGRAM_DATA_MASK);
	}
	
    //
    lcd_cmd(LCD_CMD_HOME_CURSOR);
}

static void lcd_data(unsigned char data)
{
    // e clock low
    LCD_E_LO();
    
    // select to write to the data register
    LCD_RS_DR();
    
    // write mode
    LCD_RW_WRITE();
    
    // e clock high
    LCD_E_HI();
    
    // write the high nybble of data to the lcd
    LCD_BUS(HIGH_NYB(data));
    
    // e clock low
    LCD_E_LO();
    
    // e clock high
    LCD_E_HI();
    
    LCD_BUS(LOW_NYB(data));
    
    // e clock low
    LCD_E_LO();
    
    // delay
    delay_ms(2);
}


static void lcd_cmd(unsigned char cmd)
{
    // e clock low
    LCD_E_LO();
    
    // select to write to the data register
    LCD_RS_IR();
    
    // write mode
    LCD_RW_WRITE();
    
    // e clock high
    LCD_E_HI();
    
    // write the high nybble of data to the lcd
    LCD_BUS(HIGH_NYB(cmd));
    
    // e clock low
    LCD_E_LO();
    
    // e clock high
    LCD_E_HI();
    
    LCD_BUS(LOW_NYB(cmd));
    
    // e clock low
    LCD_E_LO();
    
    // delay
    delay_ms(2);
}

static void lcd_wait(void)
{
	while(lcd_read() & 0x80);
}

static unsigned char lcd_read(void)
{
	unsigned char data;
	
	// set LCD port bus as inputs
	CLR(LCD_DDR, LCD_BUS_MASK);
	
	LCD_E_LO();
	LCD_RS_IR();
	LCD_RW_READ();
	
	LCD_E_HI();
	data = (LCD_PORT & 0xF0);
	LCD_E_LO();
	
	LCD_E_HI();
	data |= (LCD_PORT & 0x0F);
	LCD_E_LO();
	
	SET(LCD_DDR, LCD_BUS_MASK);
	
	return data;
}






