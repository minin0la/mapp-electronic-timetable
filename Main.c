/*
 * File:   Main_Program.c
 * Author: Natawat "Minin0la" Hebnak
 *
 * Created on 27 July, 2016, 9:31 AM
 */

#include <xc.h>
#include "lcd.h"
#include "delays.h"
#include "keypad.h"

unsigned char hour, minute, second, hourA, minuteA, hourB, minuteB, hourC, minuteC;

char int_2_char (unsigned char int1)
{
	char char1;
	switch (int1)
	{
		case 0 : char1 = '0' ; break;
		case 1 : char1 = '1' ; break;
		case 2 : char1 = '2' ; break;
		case 3 : char1 = '3' ; break;
		case 4 : char1 = '4' ; break;
		case 5 : char1 = '5' ; break;
		case 6 : char1 = '6' ; break;
		case 7 : char1 = '7' ; break;
		case 8 : char1 = '8' ; break;
		case 9 : char1 = '9' ; break;
		default : char1 = '?' ;
	}
	return(char1);
}

unsigned char char_2_int (char char1)
{
	unsigned char int1;
	switch (char1)
	{
		case '0' : int1 = 0 ; break;
		case '1' : int1 = 1 ; break;
		case '2' : int1 = 2 ; break;
		case '3' : int1 = 3 ; break;
		case '4' : int1 = 4 ; break;
		case '5' : int1 = 5 ; break;
		case '6' : int1 = 6 ; break;
		case '7' : int1 = 7 ; break;
		case '8' : int1 = 8 ; break;
		case '9' : int1 = 9 ; break;
		default : int1 = 0 ;
	}
	return(int1);
}

void interrupt ISR_Timer0_Int()
{
	unsigned char hour10, hour1, minute10, minute1, second10, second1;
	if (INTCONbits.TMR0IF == 1)
	{
		//TMR0H = 0x48;
		//TMR0L = 0xE5;

		second = second + 1;
		if ( second > 59 )
		{
			second = 0;
			minute = minute + 1;
			if ( minute > 59 )
			{
				minute = 0;
				hour = hour + 1;
				if ( hour > 23 )
					hour = 0;
			}
		}

		hour10 = hour / 10;
		hour1 = hour - hour10 * 10;

		minute10 = minute / 10;
		minute1 = minute - minute10 * 10;

		second10 = second / 10;
		second1 = second - second10 * 10;

		lcd_write_cmd(0x80);
		lcd_write_data('T');
		lcd_write_data('i');
		lcd_write_data('m');
		lcd_write_data('e');
		lcd_write_data(' ');
		lcd_write_data('=');
		lcd_write_data(' ');
		lcd_write_data(int_2_char (hour10));
		lcd_write_data(int_2_char (hour1));
		lcd_write_data(':');
		lcd_write_data(int_2_char (minute10));
		lcd_write_data(int_2_char (minute1));
		lcd_write_data(':');
		lcd_write_data(int_2_char (second10));
		lcd_write_data(int_2_char (second1));
					 
		INTCONbits.TMR0IF = 0;
	}
}

void SetupTime() //Program to get current Time
{
	unsigned char msgindex, outchar, ctemp;
	unsigned char hour10, hour1, minute10, minute1, second10, second1;
	char Message[ ] = "Set time hhmmss:    ";

	lcd_write_cmd(0x80);

	for (msgindex = 0; msgindex < 20; msgindex++)
	{
		outchar = Message[msgindex];
		lcd_write_data(outchar);
	}

	lcd_write_cmd(0xC0); // Move cursor to line 2 position 1

	ctemp=getkey(); // waits and get an ascii key number when pressed
	lcd_write_data(ctemp); //display on LCD
	hour10 = char_2_int (ctemp);

	ctemp=getkey();
	lcd_write_data(ctemp);
	hour1 = char_2_int (ctemp);

	ctemp=getkey();
	lcd_write_data(ctemp);
	minute10 = char_2_int (ctemp);

	ctemp=getkey();
	lcd_write_data(ctemp);
	minute1 = char_2_int (ctemp);

	ctemp=getkey();
	lcd_write_data(ctemp);
	second10 = char_2_int (ctemp);

	ctemp=getkey();
	lcd_write_data(ctemp);
	second1 = char_2_int (ctemp);

	hour = hour10 * 10 + hour1;
	minute = minute10 * 10 + minute1;
	second = second10 * 10 + second1;

	delay_ms(500);
	lcd_write_cmd(0x01);
}

void SetupAlarmTimeA() //Program to get Alarm Time for Subject A
{
	unsigned char msgindex, outchar, ctemp;
	unsigned char hour10, hour1, minute10, minute1;    
	char Message[ ] = "Subject A Time hhmm:";
    
    PORTA = 0b00000010; //On LED RA1

	lcd_write_cmd(0x80);

	for (msgindex = 0; msgindex < 20; msgindex++)
	{
		outchar = Message[msgindex];
		lcd_write_data(outchar);
	}

	lcd_write_cmd(0xC0); // Move cursor to line 2 position 1

	ctemp=getkey(); // waits and get an ascii key number when pressed
	lcd_write_data(ctemp); //display on LCD
	hour10 = char_2_int (ctemp);

	ctemp=getkey();
	lcd_write_data(ctemp);
	hour1 = char_2_int (ctemp);

	ctemp=getkey();
	lcd_write_data(ctemp);
	minute10 = char_2_int (ctemp);

	ctemp=getkey();
	lcd_write_data(ctemp);
	minute1 = char_2_int (ctemp);

	hourA = hour10 * 10 + hour1;
	minuteA = minute10 * 10 + minute1;

	delay_ms(500);
	lcd_write_cmd(0x01);
}
void SetupAlarmTimeB() //Program to get Alarm Time for Subject B
{
	unsigned char msgindex, outchar, ctemp;
	unsigned char hour10, hour1, minute10, minute1;    
	char Message[ ] = "Subject B Time hhmm:";
    
    PORTA = 0b00000100; //On LED RA2

	lcd_write_cmd(0x80);

	for (msgindex = 0; msgindex < 20; msgindex++)
	{
		outchar = Message[msgindex];
		lcd_write_data(outchar);
	}

	lcd_write_cmd(0xC0); // Move cursor to line 2 position 1

	ctemp=getkey(); // waits and get an ascii key number when pressed
	lcd_write_data(ctemp); //display on LCD
	hour10 = char_2_int (ctemp);

	ctemp=getkey();
	lcd_write_data(ctemp);
	hour1 = char_2_int (ctemp);

	ctemp=getkey();
	lcd_write_data(ctemp);
	minute10 = char_2_int (ctemp);

	ctemp=getkey();
	lcd_write_data(ctemp);
	minute1 = char_2_int (ctemp);

	hourB = hour10 * 10 + hour1;
	minuteB = minute10 * 10 + minute1;

	delay_ms(500);
	lcd_write_cmd(0x01);
}
void SetupAlarmTimeC() //Program to get Alarm Time for Subject C
{
	unsigned char msgindex, outchar, ctemp;
	unsigned char hour10, hour1, minute10, minute1;    
	char Message[ ] = "Subject C Time hhmm:";
    
    PORTA = 0b00001000; //On LED RA3

	lcd_write_cmd(0x80);

	for (msgindex = 0; msgindex < 20; msgindex++)
	{
		outchar = Message[msgindex];
		lcd_write_data(outchar);
	}

	lcd_write_cmd(0xC0); // Move cursor to line 2 position 1

	ctemp=getkey(); // waits and get an ascii key number when pressed
	lcd_write_data(ctemp); //display on LCD
	hour10 = char_2_int (ctemp);

	ctemp=getkey();
	lcd_write_data(ctemp);
	hour1 = char_2_int (ctemp);

	ctemp=getkey();
	lcd_write_data(ctemp);
	minute10 = char_2_int (ctemp);

	ctemp=getkey();
	lcd_write_data(ctemp);
	minute1 = char_2_int (ctemp);

	hourC = hour10 * 10 + hour1;
	minuteC = minute10 * 10 + minute1;

	delay_ms(500);
	lcd_write_cmd(0x01);
}
void SetupTimerInterruptRegisters()
{
	RCONbits.IPEN =1;	// Bit7 Interrupt Priority Enable Bit
				// 1 Enable priority levels on interrupts
				// 0 Disable priority levels on interrupts		

	INTCONbits.GIEH =1;	// Bit7 Global Interrupt Enable bit
				// When IPEN = 1
				// 1 Enable all high priority interrupts
				// 0 Disable all high priority interrupts 

	T0CON = 0b00000111;	// bit7:0 Stop Timer0
				// bit6:0 Timer0 as 16 bit timer
				// bit5:0 Clock source is internal 
				// bit4:0 Increment on lo to hi transition on TOCKI pin
				// bit3:0 Prescaler output is assigned to Timer0  
				// bit2-bit0:111 1:256 prescaler


	INTCON2 = 0b10000100;	// bit7 :PORTB Pull-Up Enable bit
				//	 1 All PORTB pull-ups are disabled
				// bit2 :TMR0 Overflow Int Priority Bit
				//       1 High Priority
 
	TMR0H = 0x48;		// Initialising TMR0H
	TMR0L = 0xE5;		// Initialising TMR0L for 1 second interrupt
							 
	T0CONbits.TMR0ON = 1;	// Turn on timer
	INTCONbits.TMR0IE = 1;	// bit5 TMR0 Overflow Int Enable bit
				// 0 Disable the TMR0 overflow int

	INTCONbits.TMR0IF = 0;	// bit2 TMR0 Overflow Int Flag bit
				// 0 TMR0 register did not overflow

}

void main(void)   //------------ Main Program  ---------------------------------------------------------------
{
	ADCON1 = 0x0F;
	CMCON = 0x07;
    
	lcd_init();
    TRISA = 0b00000000; //Set PORTAs as outputs
    int AlarmAOff = 0;
    int AlarmBOff = 0;
    int AlarmCOff = 0;

    version();//Show version number
	SetupTime(); //Get Time
	SetupAlarmTimeA(); //Get Alarm Time for Subject A
	SetupAlarmTimeB(); //Get Alarm Time for Subject B
    SetupAlarmTimeC(); //Get Alarm Time for Subject C
	SetupTimerInterruptRegisters();
    
    while(1)
    {
	while(PORTAbits.RA5 == 1)
	{
		if(hour==hourA && minute==minuteA && AlarmAOff == 0)
		{
            PORTA = 0b00000011; //On Buzzer RA0 and LED RA1
		}
		else if(hour==hourB && minute==minuteB && AlarmBOff == 0)
        {
            PORTA = 0b00000101; //On Buzzer RA0 and LED RA2
        }
		else if(hour==hourC && minute==minuteC && AlarmCOff == 0)
        {
            PORTA = 0b00001001; //On Buzzer RA0 and LED RA3
        } 
        else
		{
            PORTA = 0b00000000; //Off Buzzer and All LEDS at start
		}
	}
    while (PORTAbits.RA5 == 0)
    {
       if(hour==hourA && minute==minuteA)
		{
            AlarmAOff = 1; //Set value AlarmAOff to 1
		}
		else if(hour==hourB && minute==minuteB)
        {
            AlarmBOff = 1; //Set value AlarmAOff to 1
        }
		else if(hour==hourC && minute==minuteC)
        {
            AlarmCOff = 1; //Set value AlarmAOff to 1
        } 
        else
		{
            PORTA = 0b00000000; //Off Buzzer and All LEDS at start
		} 
    }
    }
}