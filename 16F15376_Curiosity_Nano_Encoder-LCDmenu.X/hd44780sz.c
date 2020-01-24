/*
 * HD44780SZ
 * Library for alphanumeric LCD based on Hitachi HD44780 controller
 * or compatible (hitachi HD66702, Samsung KS0066, Samsung KS0070,
 * Sanyo LC7985, Epson SED1278, OKI MSM6222, Sunplus SPLC7800)
 * in 4bits mode
 *
 * Module:              hd44780sz.h
 * Version:             1.01
 * Release date:        06/01/2020
 * Dependencies:        none
 * Compiler:            Microchip XC family
 * MCU:                 PICmicro
 * Pins needed:         7 (+1)
 * Peripheral needed:   digital I/Os
 * Author:              Bernardo Giovanni
 * Website:             http://www.settorezero.com
 * Email:               settorezero@gmail.com
 *
 * YOU MAY NOT DISTRIBUTE OR SELL THIS CODE OR PART
 * OF IT WITHOUT AUTHOR'S EXPLICIT AUTHORIZATION
 *
 * E' FATTO DIVIETO ASSOLUTO DI RIDISTRIBUIRE  O VENDERE
 * QUESTO CODICE O SUE PARTI SENZA L'AUTORIZZAZIONE
 * ESPLICITA DELL'AUTORE
 *
 * WARRANTY:
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * WE ARE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE.
 * 
 * L'utilizzatore dichiara di aver letto il disclaimer al seguente
 * indirizzo prima di procedere all'utilizzo di questo codice:
 * http://www.settorezero.com/wordpress/info/disclaimer/
 * 
 * Special thanks to:
 * Andrea Bonzini (author of Poor's LCD Interface)
 * Sergio Fiocco (for distribution of Andrea Bonzini's library)
 * Gabriel Rapetti (for hints about Busy Flag)
 *
 * -----------------------------------------------------------------------------
 * REVISION LOG
 * 1.01 (06-Jan-2020)
 * -added ifndef for crystal frequency (using MCC is already declared 
 *  in device_config)
 * -changed LCDPuts and LCDPutch type from uint8_t to char
 * 
 * 1.00 (2014)
 * -first release (fork from andrea bonzini+Fisertek) adapted for XC8 compiler
 *  and with busy flag check for higher compatibility with all PICs/LCDs
 */

#include "hd44780sz.h"

// initialize hd44780 controller using 4-bit interface
void LCDInit(void)
    {
    // make tristate registers as outputs
    LCD_TRIS_RS=0;
    LCD_TRIS_RW=0;
    LCD_TRIS_EN=0;
    LCD_TRIS_D7=0;
    LCD_TRIS_D6=0;
    LCD_TRIS_D5=0;
    LCD_TRIS_D4=0;
    #ifdef LCD_BACKLIGHT
    LCD_TRIS_BL=0;
    #endif
    // control lines at startup
    LCD_RS=0;
    LCD_RW=0;
    LCD_EN=0;
    __delay_ms(60); // power-up delay
    _LCDNibbleOut(0b0011); // function set
    __delay_ms(10); // wait more than 4.1mS
    _LCDStrobe();
    __delay_us(200); // wait more than 100uS
    _LCDStrobe();
    __delay_us(5);
    _LCDNibbleOut(0b0010); // interface set to 4bit
    // from this moment we can check the busy flag
    while (_LCDIsBusy());
    // set number of display lines and font
    #if (LCD_ROWS==1)
    _LCDCommand(LCD_4BIT1LINES);
    #else
    _LCDCommand(LCD_4BIT2LINES);
    #endif
    _LCDCommand(LCD_OFF);
    _LCDCommand(LCD_CLEAR);
    _LCDCommand(LCD_ENTRYMODE6);
    _LCDCommand(LCD_ON);
    }// LCDInit

// set cursor to row and column specified (1-based index!)
void LCDGoto(uint8_t row,uint8_t col)
    {
    if (row>LCD_ROWS)
        {
        row=LCD_ROWS;
        }
    if (col>LCD_COLS)
        {
        col=LCD_COLS;
        }

    switch(row)
        {
        case 1:
        _LCDCommand((LCD_ROW1-1U)+col);
        break;

        case 2:
        _LCDCommand((LCD_ROW2-1U)+col);
        break;

        case 3:
        _LCDCommand((LCD_ROW3-1U)+col);
        break;

        case 4:
        _LCDCommand((LCD_ROW4-1U)+col);
        break;
        }
    }// LCDGoto

// clear display
void LCDClear(void)
    {
    _LCDCommand(LCD_CLEAR);
    }// LCDClear

// turns on/off backlight if backlight pin is I/O-driven
#ifdef LCD_BACKLIGHT
void LCDBacklight(unsigned char backlight)
    {
    if (backlight==ON)
        {
        LCD_BL=1;
        }
    else
        {
        LCD_BL=0;
        }
    }// LCDBacklight
#endif

// write a single char on the display
void LCDPutch(char c)
    {
    LCD_RS=1;
    _LCDSendByte((uint8_t)c);
    }// LCDPutch

// write an unsigned integer
void LCDPutun(uint16_t c)
    {
    uint8_t t1,i,wrote;
    uint16_t k;
    wrote=0;
    for (i=4;i>=1;i--)
        {
        switch(i)
            {
            case 4:
            k=10000;
            break;

            case 3:
            k=1000;
            break;

            case 2:
            k=100;
            break;

            case 1:
            k=10;
            break;
            }
        t1=c/k;
        if((wrote)||(t1!=0))
            {
            LCDPutch(t1+'0');
            wrote=1;
            }

        c-=(t1*k);
        }// end for
    LCDPutch((uint8_t)(c+'0'));
    }//LCDPutun

// write a signed integer
void LCDPutsn(int16_t c)
    {
    if(c<0)
        {
        LCDPutch('-');
        c*=(-1);
        }
    LCDPutun((uint16_t)c);
    }//L LCDPutsn

// write a string
void LCDPuts(const char *s)
    {
    while(*s)
        {
        LCDPutch(*s++);
        }
    }// LCDPuts

// set a custom char in the ram position
void LCDCustomChar(uint8_t pos, const uint8_t *b)
    {
    if (pos>7) {return;}
    uint8_t u;
    _LCDCommand(LCD_OFF);
    _LCDCommand(LCD_GOCGRAM+(pos*8U));
    for (u=0; u<8U; u++)
        {
        LCDPutch((uint8_t)b[u]);
        }
    _LCDCommand(LCD_CLEAR);
    _LCDCommand(LCD_ON);
    }// LCDCustomChar

// low-level functions

// pulse on the enable line
void _LCDStrobe(void)
    {
    LCD_EN=1;
    __delay_us(2);
    LCD_EN=0;
    }// _LCDSTrobe

// send 4-bit to lcd
void _LCDNibbleOut (uint8_t nibble)
    {
    // check bit 7 (or bit 3)
    if (nibble & 0b10000000)
        {
        LCD_D7=1;
        }
    else
        {
        LCD_D7=0;
        }
    // check bit 6 (or bit 2)
    if (nibble & 0b01000000)
        {
        LCD_D6=1;
        }
    else
        {
        LCD_D6=0;
        }
    // check bit 5 (or bit 1)
    if (nibble & 0b00100000)
    	{
        LCD_D5=1;
        }
    else
        {
        LCD_D5=0;
        }
    //check bit 4 (or bit 0)
    if (nibble & 0b00010000)
        {
        LCD_D4=1;
        }
    else
        {
        LCD_D4=0;
        }
    __delay_us(1);
    _LCDStrobe();
    }// _LCDNibbleOut

// send 1 byte to lcd
void _LCDSendByte (uint8_t b)
    {
    while (_LCDIsBusy());
    _LCDNibbleOut(b);
    b <<= 4;
    _LCDNibbleOut(b);
    }// _LCDSendByte

// send command to lcd (1 byte with RS at low logic level)
void _LCDCommand (uint8_t cmd)
    {
    LCD_RS=0;
    _LCDSendByte(cmd);
    } // _LCDCommand

// return the busy flag
uint8_t _LCDIsBusy(void)
    {
    static uint8_t busyFlag;
    static uint8_t tempRS;
    // set data lines as input
    LCD_TRIS_D7=1;
    LCD_TRIS_D6=1;
    LCD_TRIS_D5=1;
    LCD_TRIS_D4=1;
    tempRS = LCD_RS; // actual register select value
    LCD_RW=1; // read mode
    LCD_RS=0; // command mode
    LCD_EN=1; // read bits 4-7 (bit7 = busy status)
    __delay_us(1);
    busyFlag=LCD_D7; // read busy flag
    LCD_EN=0;
    __delay_us(1);
    _LCDStrobe();
    // set data lines as output
    LCD_TRIS_D7=0;
    LCD_TRIS_D6=0;
    LCD_TRIS_D5=0;
    LCD_TRIS_D4=0;
    LCD_RW=0; // back to write mode
    LCD_RS=tempRS; // restore previous register select value
    return (busyFlag);
    }// _LCDIsBusy