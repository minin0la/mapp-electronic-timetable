// LCD2Lines.c
// Program to test LCD.
// The LCD display with two lines, 24 characters each.
// There are three control lines (RD4:RD6) and four data lines (RD3:RD0).
// RD6 - RS=0 Data represents Command, RS=1 Data represents Character
// RD5 - RW=0 Writing into the LCD module
// RD4 - E =1 Data is latched into LCD module during low to hight transition  

#include <xc.h>
#include "lcd.h"	// Include file is located in the project directory

void main(void)
{
    unsigned char outchar,outchar2,outchar3,outchar4;
    int seconds1 = 0;
    int seconds2 = 0;  
    char Digits[]="0123456789";
    lcd_init();
    while(1)
    {
        lcd_write_cmd(0x80);
        for(seconds2 =0;seconds2<6;seconds2++)
        {
            if(seconds2 == 6)
            {
                seconds2 = 0;
                seconds1++;
              outchar3 = Digits[seconds1];
              outchar4 = Digits[seconds2];
              lcd_write_cmd(0x80);
              lcd_write_data(outchar3); 
              lcd_write_data(outchar4);   
            }else
              outchar3 = Digits[seconds1];
              outchar4 = Digits[seconds2];
              lcd_write_cmd(0x80);
              lcd_write_data(outchar3); 
              lcd_write_data(outchar4);
        }
    }
}						


		

