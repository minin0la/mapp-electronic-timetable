/*
 * File:   version.c
 * Author: minin0la
 *
 * Created on 10 August, 2016, 12:15 PM
 */


#include <xc.h>
#include "lcd.h"

void version(void) //Program to show program version
{
	unsigned char msgindex, outchar;
	char Version[ ] = "ETT Version 1.3a     ";

	lcd_write_cmd(0x80);

	for (msgindex = 0; msgindex < 20; msgindex++)
	{
		outchar = Version[msgindex];
		lcd_write_data(outchar);
	}
}
