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

//#include <xc.h>
#include "mcc_generated_files/device_config.h"
#include "mcc_generated_files/pin_manager.h"
#include <stdint.h>

// crystal frequency (Hz)
// NOTE: this library is tested up to 32MHz on PIC16F15376
// does not work @32MHz on PIC16F18877 (strange!)
#ifndef _XTAL_FREQ
#define _XTAL_FREQ 24000000
#endif

// display size
#define LCD_ROWS 4
#define LCD_COLS 20

// uncomment this if your lcd uses font 5x10
// (note: majority of lcds uses 5x8 font, so leave this commented)
//#define FONT5x10

// uncomment if lcd backlight pin is I/O-driven
// comment if lcd backlight is hardwired
//#define LCD_BACKLIGHT

// data connections between LCD and Picmicro
// NOTE: Data and RS must be on the same port!
#define	LCD_RS	_LCD_RS_PORT // Register select
#define LCD_RW	_LCD_RW_PORT // Read/Write
#define	LCD_EN	_LCD_EN_PORT // Enable
#define	LCD_D7	_LCD_D7_PORT // LCD data 7
#define	LCD_D6	_LCD_D6_PORT // LCD data 6
#define	LCD_D5	_LCD_D5_PORT // LCD data 5
#define	LCD_D4	_LCD_D4_PORT // LCD data 4
//#define LCD_BL    _LCD_BL_PORT	 // Backlight, can comment if hardwired

// port connections (tristate registers)
#define LCD_TRIS_RS     _LCD_RS_TRIS 
#define LCD_TRIS_RW     _LCD_RW_TRIS 
#define LCD_TRIS_EN     _LCD_EN_TRIS 
#define LCD_TRIS_D7     _LCD_D7_TRIS 
#define LCD_TRIS_D6     _LCD_D6_TRIS 
#define LCD_TRIS_D5     _LCD_D5_TRIS 
#define LCD_TRIS_D4     _LCD_D4_TRIS 
//#define LCD_TRIS_BL   _LCD_BL_TRIS // Backlight, can comment if hardwired

// please don't edit nothing below this line ------------------------

// hd44780 command list
#define LCD_CLEAR       0x01
#define LCD_HOME        0x02
#define LCD_SCROLL_R	0x1E
#define LCD_SCROLL_L	0x18
#define LCD_MOVE_L      0x10
#define LCD_MOVE_R      0x14
#define LCD_CURSOROFF	0x0C
#define LCD_CURSORON	0x0E
#define LCD_CURSORBLINK	0x0F
#define	LCD_OFF         0x08
#define LCD_ON          0x0C
#define LCD_GOCGRAM     0x40
#ifdef FONT5x10
#define	LCD_4BIT1LINES	0x24 // 4bit, 1 row, font 5x10
#define	LCD_4BIT2LINES	0x2C // 4bit, 2 or more rows, font 5x10
#else
#define	LCD_4BIT1LINES	0x20 // 4 bit, 1 row, font 5x8
#define	LCD_4BIT2LINES	0x28 // 4 bit, 2 or more rows, font 5x8
#endif
#define LCD_ENTRYMODE4	0x04 // shift off, decrement address
#define LCD_ENTRYMODE5	0x05 // shift on, decrement address
#define LCD_ENTRYMODE6	0x06 // shift off, increment address
#define LCD_ENTRYMODE7	0x07 // shift on, increment address

// start-rows definitions
#define LCD_ROW1        0x80 // Row 1, Col 1
#define LCD_ROW2        0xC0 // Row 2, Col 1
#if (LCD_COLS==20)
#define LCD_ROW3        0x94 // Row 3, Col 1 (20 columns lcds)
#define LCD_ROW4        0xD4 // Row 4, Col 1 (20 columns lcds)
#else
#define LCD_ROW3        0x90 // Row 3, Col 1 (16 columns lcds)
#define LCD_ROW4        0xD0 // Row 4, Col 1 (16 columns lcds)
#endif

// others
#ifndef ON
#define ON  1
#endif
#ifndef OFF
#define OFF 0
#endif
#define HD44870SZ

// functions prototypes

// high-level functions
extern void LCDInit(void);
extern void LCDGoto(uint8_t row,uint8_t col); // (1-based index!)
extern void LCDClear(void);
extern void LCDBacklight(uint8_t backlight); //ON/OFF (ON=>pin at High level)
extern void LCDPutch(char c);
extern void LCDPutun(uint16_t c);
extern void LCDPutsn(int16_t c);
extern void LCDPuts(const char *s);
extern void LCDCustomChar(uint8_t pos, const uint8_t *b); // pos=0 to 7

// low-level functions - normally not used in your code
extern void _LCDStrobe(void);
extern void _LCDNibbleOut(uint8_t nibble);
extern void _LCDSendByte(uint8_t b);
extern void _LCDCommand(uint8_t cmd);
extern uint8_t _LCDIsBusy(void);