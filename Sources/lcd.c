
#include "lcd.h"
#include "derivative.h"

#include "util.h"
#include "delay.h"

#define LCD_PORT     PORTA
#define LCD_DDR      DDRA
#define LCD_DDR_INIT 0xFF

#define LCD_E_MASK   PORTA_BIT4_MASK
#define LCD_RS_MASK  PORTA_BIT5_MASK
#define LCD_RW_MASK  PORTA_BIT6_MASK
#define LCD_BUS_MASK 0x0Fu

#define LCD_E_LO() ( CLR(LCD_PORT, LCD_E_MASK) )
#define LCD_E_HI() ( SET(LCD_PORT, LCD_E_MASK) )

#define LCD_BUS(value) ( FORCE(LCD_PORT, LCD_BUS_MASK, value) )

// select lcd user registers
#define LCD_RS_DR() ( SET(LCD_PORT, LCD_RS_MASK) ) // select data register
#define LCD_RS_IR() ( CLR(LCD_PORT, LCD_RS_MASK) ) // select instruction register

// set lcd R/~W line
#define LCD_RW_WRITE() ( CLR(LCD_PORT, LCD_RW_MASK) ) // write mode
#define LCD_RW_READ()  ( SET(CD_PORT, LCD_RW_MASK) )  // read mode

// lcd commands

#define CLR_DISPLAY 0x01u
#define HOME_CURSOR 0x02u

// command characters
#define LINE_FEED '\n'
#define HOME      '\r'

/* Private Prototypes */

static void lcd_data(unsigned char data);
static void lcd_cmd(unsigned char cmd);

void lcd_init(void)
{
    // set lcd port directions
    SET(LCD_DDR, LCD_DDR_INIT);
    
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
    
}

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
            case LINE_FEED:
                
                break;
            case HOME:
                lcd_cmd(HOME_CURSOR);
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
    char c = *fmt;
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







