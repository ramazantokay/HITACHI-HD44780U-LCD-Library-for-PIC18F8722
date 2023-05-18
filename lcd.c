#include "Includes.h"
#include "lcd.h"

void Pulse(void){
    LCD_EN = 1;
    __delay_us(LCD_PULSE);
    LCD_EN = 0;
    __delay_us(LCD_PULSE);
}

void InitLCD(void) {
    
    LCD_RS = 0;
    LCD_EN = 0;
    LCD_D4 = 0;
    LCD_D5 = 0;
    LCD_D6 = 0;
    LCD_D7 = 0;
    
    TRISB = 0x00; // LCD Control RB2/RB5
    TRISD = 0x00; // LCD Data  RD[4-7]
    
    __delay_ms(20);
    PORTD = 0x30;
    Pulse();
    
    __delay_ms(6);
    PORTD = 0x30;
    Pulse();
    
    __delay_us(300);
    PORTD = 0x30;
    Pulse();
    
    __delay_ms(2);
    PORTD = 0x20;
    Pulse();
        
    lcd_cmd(0x2C); // function set
    lcd_cmd(0x0C); // 1,  Display on/off bit, cursor on/off bit, blink on/off. // current==> Display on, cursor off, blink off.
    lcd_clear();
}

void lcd_cmd(uint8_t cmd){
    // Send 'cmd' as a command to the LCD.
    
    LCD_RS = 0; // command
    
    PORTD = PORTD & 0x0f;
    PORTD = PORTD | (cmd & 0xf0);
    Pulse();
    
    PORTD = PORTD & 0x0f;
    PORTD = PORTD | ((cmd<<4) & 0xf0);
    Pulse();
    
}
void lcd_data(uint8_t data){
    // Send 'data' as data to the LCD.
    
    LCD_RS = 1;
    
    PORTD = PORTD & 0x0f;
    PORTD = PORTD | (data & 0xf0);
    Pulse();
    
    PORTD = PORTD & 0x0f;
    PORTD = PORTD | ((data<<4) & 0xf0);
    Pulse();

}

void CreateChar(uint8_t addr, uint8_t charmap[]) {
  addr &= 0x7; // we only have 8 locations 0-7
  lcd_cmd(0x40 | (addr << 3)); // Set the address for custom char.
  for (int i=0; i<8; i++) {
    lcd_data(charmap[i]); // Write char data.
  }
}

void lcd_clear()
{
    lcd_cmd(LCD_CLEAR); // clear the screen
    lcd_pos_x = 1; lcd_pos_y = 1;
    __delay_ms(2);
}

 void lcd_print_string(char* buf)
 {
     while(*buf)
         lcd_data(*buf++);
 }
 void lcd_cursor_move(uint8_t row, uint8_t col)
 {
    (row == 1) ? lcd_cmd(LCD_ROW_1 + (col - 1)): lcd_cmd(LCD_ROW_2 + (col - 1));
    lcd_pos_x = col;
    lcd_pos_y = row;
 }
 
 void lcd_delay_ms(const int delay_ms)
 {
     for(int i = 0; i < delay_ms; i++) 
         __delay_ms(1);
 }
 
 void lcd_content_shift_right(const int delay)
 {
    lcd_delay_ms(delay);
    lcd_pos_x++;
    lcd_cmd(LCD_CONTENT_MOVE_RIGHT);
 }
 
void lcd_content_shift_left(const int delay)
{
    lcd_delay_ms(delay);
    lcd_pos_x--;
    lcd_cmd(LCD_CONTENT_MOVE_LEFT);
}

void lcd_home()
{
    lcd_cmd(0x02);
    lcd_pos_x = 1; lcd_pos_y = 1;
    __delay_ms(2);
}

void lcd_finish_scroll_text(char *arr, const int delay)
{
    // shifting the array
    char temp = arr[0];
    for (int i=0; i<15; i++)    
        arr[i] = arr[i+1];
    arr[15]=temp;
    // then print again 
    lcd_cursor_move(1,4);
    lcd_print_string("finished");
    lcd_delay_ms(delay);
    lcd_cursor_move(2,1);
    lcd_print_string(arr);
    lcd_cmd(LCD_ON); // cursor off

    
}
