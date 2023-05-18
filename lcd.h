#ifndef _LCD_H_
#define	_LCD_H_

#include "Includes.h"

// This is the PIC to LCD pin mapping
#define LCD_RS LATB2
#define LCD_RW LATB3
#define LCD_EN LATB5
#define LCD_D4 LATD4
#define LCD_D5 LATD5
#define LCD_D6 LATD6
#define LCD_D7 LATD7

// This is the LCD instruction mapping list for our program, check more detail
//      about LDC instruction list on page.24
// will be added more instruciton later

#define LCD_ROW_1 0x80 // selects 1.line of LCD
#define LCD_ROW_2 0xC0 // selects 2.line of LCD

#define LCD_CLEAR 0x01 // clears the LCD
#define LCD_ON  0x0C // Display on, cursor off, blink off.
#define LCD_OFF 0x08 // Display off

#define LCD_CURSOR_ON 0x0A // only cursor bit is set
#define LCD_CURSOR_BLINK 0x09 // only blinking of cursor position bit is set

#define LCD_CURSOR_MOVE_RIGHT 0x14 // move entire display to right by 1 step
#define LCD_CURSOR_MOVE_LEFT 0x10 // move entire display to left by 1 step

#define LCD_CONTENT_MOVE_RIGHT 0x1C // move cursor right by 1 step
#define LCD_CONTENT_MOVE_LEFT 0x18 // move cursor left by 1 step

// stores the cursor position in the LCD, variables can take these values, x[1-16] y[1-2]
uint8_t lcd_pos_x = 1, lcd_pos_y = 1;

//uint8_t predefined_loc = 0;

// Pulse time for the E pin.
#define LCD_PULSE 30

// Predefined set of characters.
volatile char PREDEFINED_CHAR[] = " abcdefghijklmnopqrstuvwxyz0123456789";
int PREDEFINED_CHAR_LENGTH = 37;


// Container to display text of LCD
#define DISPLAY_BUFFER_SIZE 17
char DISPLAY_BUFFER[DISPLAY_BUFFER_SIZE];
int DISPLAY_BUFFER_CHAR_SELECTOR[DISPLAY_BUFFER_SIZE];



// A custom character is defined as an array of 8 bytes.
// Each bytes' least significant 5 bits are used to draw
// custom characters to the LCD.
// Example custom character definition.
uint8_t fullHeart[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000,
};

// Implementation of below functions are provided in lcd.c

// Pulse the E pin of the LCD.
void Pulse(void);
// Properly initialize the LCD.
void InitLCD(void);
// Create a custom character and store it in the LCD's memory.
// First argument is the address to store the character. It can
// take values between 0 and 7 (for 8 custom characters). Second
// argument is the character data. See the fullHeart array above.
// When you send the address as 'data' to the LCD, the custom
// character stored at that address is displayed.
void CreateChar(uint8_t address, uint8_t* charmap);

/*
 * sends a command (instruction) to LCD
 * @param cmd instruction to be sent
 */
void lcd_cmd(uint8_t cmd);

/*
 * sends data to LCD
 * @param data the data to be sent 
 */

void lcd_data(uint8_t data);

/*
 * prints string on LCD
 * @param buf string to be printed
 */
void lcd_print_string(char* buf);

/*
 * clears the LCD and sets the DDRAM address to 0
 * and sets cursor position to (1,1)
 */
void lcd_clear();

/*
 * sets the cursor position (1,1) and DDRAM address to 0, and 
 * it doesn't change DDRAM contents i.e text in the LCD will not change 
 */

void lcd_home();

/*
 * set the cursor location in the LCD
 * @param row specify the display line [1-2]
 * @param col specify a cell [1-16]
 */
 
void lcd_cursor_move(uint8_t row, uint8_t col);

/*
 *  a helper delay function for shifting functions. 
 *  @param delay_ms delay amount in microsecond
 */
void lcd_delay_ms(const int delay_ms);

/*
 * move entire display to right
 * @param delay after delay ms, the display shift right by 1 step
 */
void lcd_content_shift_right(const int delay);

/*
 * move entire display to left
 * @param delay after delay ms, the display shift left by 1 step
 */

void lcd_content_shift_left(const int delay);

/*
 * this is for text scroll mode (TSM)
 * scroll the text on the second line of the LCD.
 * @param arr the text array to scroll
 * @param delay defines scroll delay
 */
void lcd_finish_scroll_text(char *arr, const int delay);

#endif	/* _LCD_H_ */

