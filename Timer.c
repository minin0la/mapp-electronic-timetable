/*
 * File:   Timer.c
 *
 */


#include <xc.h>
#include "delays.h"
void main(void)
{

	TRISB=0b11110000;	//RB3 to RB0 are connected DIG3 to DIG0 active high
						//RB5 is connected to a switch

	TRISD=0b00000000;	//RD7 to RD0 are connected to segment LEDs active high
    
    int i;
    int seconds = 0;
    int mins = 0;
    int digits[10]=
    {
        0b01111111,//0
        0b00000110,//1
        0b01011011,//2
        0b01001111,//3
        0b01100110,//4
        0b01101101,//5
        0b01111101,//6
        0b00000111,//7
        0b01111111,//8
        0b01100111,//9
    }; //declare 'seconds'
		
	while(1)			//repeat 
	{
        delay_ms(100);
        for(seconds=0;seconds<10;seconds++)
        {
        PORTB = 0b00000001;
        PORTD = digits[seconds];
        delay_ms(1000);
        PORTB = 0b00000010;
        PORTD = digits[mins];
        delay_ms(1000);
        if(seconds > 10)
        {
            seconds = 0;
            mins = mins+1;
        }
        } 
	}
}
