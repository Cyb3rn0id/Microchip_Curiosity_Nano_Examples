/* 
 * MAX7219sz PIC lib
 * MAX7219 Library for Microchip(R) PIC(R) Microcontrollers
 * Version: 1.0
 * 
 * This file is part of the MAX7219sz_PIC_lib package:
 * https://github.com/Cyb3rn0id/MAX7219sz_PIC_lib
 * 
 * Copyright (c) 2020 Giovanni Bernardo.
 * https://www.settorezero.com
 * 
 * See Github repository for informations and library usage
 * 
 * LICENSE
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed "AS IS" in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY.  
 * See the GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "MAX7219sz.h"
// required for pin functions and delays
// you must use MPLAB Code Configurator
#include "mcc_generated_files/device_config.h"
#include "mcc_generated_files/pin_manager.h"

//******************************************************************************
// Initializes the MAX7219
//******************************************************************************
void MAX7219_init(void)
    {
    MAX_DAT_SetLow();
    MAX_CLK_SetLow();
    MAX_LAT_SetLow();
    MAX7219_send(TEST,0);
    MAX7219_send(SCANLIMIT, DIGITS-1);
    MAX7219_setNoDecode();
    MAX7219_send(INTENSITY,MAXINTENSITY);
    MAX7219_clear();
    MAX7219_send(SHUTD,1);
    __delay_us(300);
    }

//******************************************************************************
// Sends a byte data to register
//******************************************************************************
void MAX7219_send(uint8_t reg, uint8_t dat)
    {
    uint16_t d=(reg<<8)|dat;
    for (uint8_t i=0; i<16; i++)
        {
        if (d & (0x8000>>i))
            {MAX_DAT_SetHigh();}
        else
            {MAX_DAT_SetLow();}
        MAX_CLK_SetHigh();
        MAX_CLK_SetLow();
        }
    MAX_LAT_SetHigh();
    MAX_LAT_SetLow();    
    }

//******************************************************************************
// Clears MAX7219 shift register in both decode modes
//******************************************************************************
void MAX7219_clear(void)
    {
    for (uint8_t i=0; i<8; i++)
        {
        if (_mode==DECODE)
            {MAX7219_send(i+1,0x0F);}
        else
            {MAX7219_send(i+1,0);}
        }
    }    

//******************************************************************************
// Clears MAX7219 shift register using cursor effect
//******************************************************************************
void MAX7219_clearc(void)
    {
    MAX7219_lclearc(DIGITS);
    }

//******************************************************************************
// Clears MAX7219 shift register using cursor effect until the first printed char
//******************************************************************************
void MAX7219_lclearc(uint8_t startpos)
    {
    for (uint8_t i=_digit; i<startpos+1; i++)
        {
        MAX7219_send(i,UNDERSCORE);
        DELAYCURSOR;
        MAX7219_send(i,0);
        }
    DELAYCURSOR;
    }

//******************************************************************************
// Writes a char on the digit eventually turning on the comma/point
//******************************************************************************
void MAX7219_putch(uint8_t digit, char ch, bool point)
    {
    if (_mode!=NODECODE) MAX7219_setNoDecode();
    // space
    if (ch==' ')
        {
        MAX7219_send(digit,0);
        _digit=digit;
        return;
        }
    // minus
    if (ch=='-')
        {
        MAX7219_send(digit,MINUS);
        _digit=digit;
        return;
        }
    // underscore
    if (ch=='_')
        {
        MAX7219_send(digit,UNDERSCORE);
        _digit=digit;
        return;
        }
    // comma and point
    if ((ch==',') || (ch=='.'))
        {
        MAX7219_send(digit,SEGDOT);
        _digit=digit;
        return;
        }
    
    ch-='0'; // subtract 48
    if (ch<10) // it's a number (0-9)
        {
        MAX7219_numch(digit,ch,point);
        return;
        }
    else // not a number: remember that I've subtracted '0' (48)
        {
        // uppercase letters (ASCII 65 to 90)
        if ((ch>('A'-'0'-1)) && (ch<('Z'-'0'+1)))
            {
            ch-='A'-'0';
            }
        // lowercase letters (ASCII 97 to 122)
        else if ((ch>('a'-'0'-1)) && (ch<('z'-'0'+1)))
            {
            ch-='a'-'0';
            }
        else
            {
            ch=0;
            }
        }
    MAX7219_send(digit,chars[ch]|(point<<7));
    _digit=digit;
    }

//******************************************************************************
// Writes a number from 0 to 9 as char eventually turning on the comma/point
//******************************************************************************
void MAX7219_numch(uint8_t digit, uint8_t n, bool point)
    {
    if (n>9) return;
    if (_mode!=NODECODE) MAX7219_setNoDecode();
    MAX7219_send(digit,numbers[n]|(point<<7));
    _digit=digit;
    }

//******************************************************************************
// Sets the decode mode
//******************************************************************************
void MAX7219_setDecode(void)
    {
    MAX7219_send(DECODEMODE,DECODE);
    _mode=DECODE;
    __delay_ms(1);
    }

//******************************************************************************
// Sets the no-decode mode
//******************************************************************************
void MAX7219_setNoDecode(void)
    {
    MAX7219_send(DECODEMODE,NODECODE);
    _mode=NODECODE;
    __delay_ms(1);
    }

//******************************************************************************
// Sets display brightness from 0(lowest) to 9 (highest)
//******************************************************************************
void MAX7219_setIntensity(uint8_t val)
    {
    if (val>MAXINTENSITY) val=MAXINTENSITY;
    MAX7219_send(INTENSITY,val);
    }

//******************************************************************************
// Turns on the test mode
//******************************************************************************
void MAX7219_test(void)
    {
     MAX7219_send(TEST,1);
    }

//******************************************************************************
// Turns on/off the display
//******************************************************************************
void MAX7219_shutdown(bool yesno)
    {
    MAX7219_send(SHUTD,!yesno);
    }


//******************************************************************************
// Writes a string using (true) or no (false) the cursor effect
//******************************************************************************
void MAX7219_puts(const char *s, bool cursor)
	{
	MAX7219_lputs(s, cursor, DIGITS);
	}

//******************************************************************************
// Writes a string using (true) or no (false) the cursor effect starting from 
// desidered location
//******************************************************************************
void MAX7219_lputs(const char *s, bool cursor, uint8_t startpos)
    {
    MAX7219_clear();
    uint8_t i=0;
    if (startpos>DIGITS) startpos=DIGITS;
	while(*s)
        {
        if (cursor)
            {
            MAX7219_send(startpos-i, UNDERSCORE);
            DELAYCURSOR;
            }
        MAX7219_putch(startpos-i, *s++, false);
        if (cursor) DELAYCURSOR;
        i++;
        if (i==startpos) return; // stop if string reached the end of display
        }
    }

//******************************************************************************
//  Writes an unsigned integer, returns most-left digit used
//******************************************************************************
uint8_t MAX7219_putun(uint32_t num, uint8_t decimals, uint8_t rightspace)
    {
    uint8_t prev_lastn=_lastn; // previous last printed char
    uint8_t t1,i,wrote;
    uint8_t pos=0; // first printed char (the most-left)
    wrote=0;
    uint32_t k;
    for (i=7;i>0;i--)
        {
        switch(i)
            {
            // this switch will consider numbers up to 8 digits
            case 7:
            k=10000000; // number has 8 digits
            break;
            
            case 6:
            k=1000000; // number has 7 digits
            break;
            
            case 5:
            k=100000; // number has 6 digits
            break;

            case 4:
            k=10000; // number has 5 digits
            break;

            case 3:
            k=1000; // number has 4 digits
            break;

            case 2:
            k=100; // number has 3 digits
            break;

            case 1:
            k=10; // number has 2 digits
            break;
            
            // ... and "number has 1 digit" ? See below!
            }
        t1=num/k;
        if((wrote)||(t1!=0)||((i==decimals)&&(t1==0))) // suppress non-significant zeroes
            {
            bool p=(i==decimals)?true:false; // comma/point ?
			MAX7219_numch(i+1+rightspace, t1, p);                
            wrote=1;
            if (pos==0) pos=i+1+rightspace; // position of first printed char
            }
        num-=(t1*k);
        }// end for
    // Number has 1 digit:
    MAX7219_numch(1+rightspace,num,false); // this is also the last printed digit
    // if we're arrived here with pos=0 means that number is only 1 digit
    if (pos==0) pos=1+rightspace; // position of the only char 
    _digit=1; // last position, always 1 in case of numbers
    _lastn=pos;
    // delete previous chars if any
	// this will delete also the minus sign if number become >0
	// since the MAX7219_putsn uses this function
    if (prev_lastn>_lastn)
        {
        for (uint8_t q=prev_lastn; q>_lastn; q--)
            {
            MAX7219_send(q,0);
            }
        }
    return (_lastn);
    }

//******************************************************************************
// Writes an integer, returns most-left digit used
//******************************************************************************
uint8_t MAX7219_putn(int32_t num, uint8_t decimals, uint8_t rightspace)
    {
    uint8_t prev_lastn=_lastn;
    bool sign=false;
    uint8_t pos=0; // first printed char (the most-left)
    if(num<0)
        {
        sign=true;
        num*=-1;
        }
    pos=MAX7219_putun(num, decimals, rightspace);
    if (sign) // add minus sign and update the most-left printed digit
        {
		pos+=1; // this will be the minus sign position, on the left of first printed digit
        MAX7219_send(pos,MINUS);
        }
    _lastn=pos;
    return (_lastn);
    }

//******************************************************************************
// Writes a string using the scrolling effect
//******************************************************************************
void MAX7219_scroll(const char *s, bool appear, bool disappear)
	{
	volatile uint8_t sl=strlen(s);
    char buf[DIGITS]; // buffer that will be printed on display
	char s_temp[SCROLLBUFFER]; // temporary buffer ([spaces]+[s]+[eventually spaces])
	memset(buf, 0, sizeof buf); // fill buffer with null-terminator
	memset(s_temp, ' ', sizeof s_temp); // fill temporary buffer with blank spaces
	if (appear) 
        {s_temp[DIGITS]='\0';} // leaves DIGITS blank spaces at left of string
    else
        {s_temp[0]='\0';} // allows strcat attach s at beginning
    strcat(s_temp,s); // result: [DIGITS spaces]+[s]+'\0'
	volatile uint8_t stl=sl+(DIGITS*appear); // temporary string length
    volatile uint8_t i=0;
    _digit=1;
    // add spaces on the right if length of s is < of number of display digits
	// for left-align a string if is smaller than display
    if (sl<DIGITS) 
		{
		for (i=0; i<(DIGITS-sl); i++)
			{
			s_temp[i+stl]=' ';
			}
		stl+=i;
        s_temp[stl+1]='\0';
        }
    // add further spaces on the right if string must scroll out of the display
    if (disappear) 
        {
        for(i=0; i<DIGITS; i++)
           {
           s_temp[stl+i]=' ';
           }
        stl+=i;
        s_temp[stl+1]='\0';
        }
    // transfer DIGITS bytes from temporary string to the buffer   
	for (uint8_t i=0; i<stl-DIGITS+1; i++)
		{
		for (uint8_t u=0; u<DIGITS; u++)
			{
			buf[u]=s_temp[i+u];
			}
		MAX7219_puts(buf,false);
		DELAYSCROLL;
		}
    // relocate the cursor
    if (disappear) _digit=DIGITS;
	}

//******************************************************************************
// Glowing effect
//******************************************************************************
void MAX7219_glow(uint8_t times)
    {
    for (uint8_t i=0; i<times; i++)
        {
        for (int8_t c=MAXINTENSITY; c>-1; c--)
            {
            MAX7219_setIntensity(c);
            __delay_ms(50);
            }
        MAX7219_shutdown(true);
        __delay_ms(100);
        MAX7219_shutdown(false);
        __delay_ms(50);
        for (int8_t d=0; d<(MAXINTENSITY+1); d++)
            {
            MAX7219_setIntensity(d);
            __delay_ms(50);
            }
        }
    }

//******************************************************************************
// Blinking
//******************************************************************************
void MAX7219_blink(uint8_t times)
    {
    for (uint8_t i=0; i<times; i++)
        {
        MAX7219_shutdown(true);
        DELAYBLINK;
        MAX7219_shutdown(false);
        DELAYBLINK;
        }
    }

// 38911 Basic Bytes Free