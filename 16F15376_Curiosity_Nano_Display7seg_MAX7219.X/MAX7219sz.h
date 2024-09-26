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

#define DIGITS			8 // number of digits
#define MAXINTENSITY	9 // maximum value of intensity

#define SCROLLBUFFER    80
#define DELAYCURSOR 	__delay_ms(30)
#define DELAYSCROLL		__delay_ms(190)
#define DELAYBLINK      __delay_ms(400)

// MAX 7219 registers
#define NO_OP       0x00
#define DIG0        0x01
#define DIG1        0x02
#define DIG2        0x03
#define DIG3        0x04
#define DIG4        0x05
#define DIG5        0x06
#define DIG6        0x07
#define DIG7        0x08
#define DECODEMODE  0x09    // DECODE, NODECODE
#define INTENSITY   0x0A	// 0-9
#define SCANLIMIT   0x0B    // register accepts 0 to 7
#define SHUTD       0x0C	// 0-1
#define TEST        0x0F	// 0-1

// values
#define DECODE      0xFF
#define NODECODE    0x00

// segments values
#define SEGA        0b01000000
#define SEGB        0b00100000
#define SEGC        0b00010000
#define SEGD        0b00001000
#define SEGE        0b00000100
#define SEGF        0b00000010
#define SEGG        0b00000001
#define SEGDOT		0b10000000

uint8_t _mode=NODECODE; // keep in mind decode mode
uint8_t _digit=DIGITS; // keep in mind last written digit for strings
uint8_t _lastn=1; // keep in mind the most-left written digit for numbers

// Font I've defined for the no-decode mode
uint8_t chars[]={
    SEGA|SEGB|SEGC|SEGE|SEGF|SEGG,      // A
    SEGC|SEGD|SEGE|SEGF|SEGG,           // b
    SEGD|SEGE|SEGG,                     // c (C=SEGA|SEGF|SEGE|SEGD)
    SEGB|SEGC|SEGD|SEGE|SEGG,           // d
    SEGA|SEGD|SEGE|SEGF|SEGG,           // E
    SEGA|SEGE|SEGF|SEGG,                // F
    SEGA|SEGC|SEGD|SEGE|SEGF,           // G
    SEGC|SEGE|SEGF|SEGG,                // h
    SEGC,                               // i (I=SEGB|SEGC)
    SEGB|SEGC|SEGD|SEGE,                // J
    SEGB|SEGC|SEGE|SEGF|SEGG,           // K
    SEGF|SEGE|SEGD,                     // L
    SEGA|SEGF|SEGB|SEGE|SEGC,           // M (looks like a N)
    SEGG|SEGE|SEGC,                     // n
    SEGC|SEGE|SEGD|SEGG,                // o
    SEGA|SEGB|SEGE|SEGF|SEGG,           // P
    SEGA|SEGF|SEGB|SEGG|SEGC,           // q
    SEGE|SEGG,                          // r
    SEGA|SEGF|SEGG|SEGC|SEGD,           // S
    SEGF|SEGG|SEGE|SEGD,                // t
    SEGE|SEGD|SEGC,                     // u
    SEGF|SEGE|SEGD|SEGC|SEGB,           // v (looks like a U)
    0,                                  // W (no way to render)
    0,                                  // X (no way to render)
    SEGF|SEGB|SEGG|SEGC|SEGD,           // Y
    SEGA|SEGB|SEGG|SEGE|SEGD            // Z (equal to 2)
    };

// Numbers for nodecode mode
uint8_t numbers[]={
    SEGA|SEGB|SEGC|SEGD|SEGE|SEGF,      // 0
    SEGB|SEGC,                          // 1
    SEGA|SEGB|SEGG|SEGE|SEGD,           // 2
    SEGA|SEGB|SEGG|SEGC|SEGD,           // 3
    SEGF|SEGG|SEGB|SEGC,                // 4
    SEGA|SEGF|SEGG|SEGC|SEGD,           // 5
    SEGA|SEGF|SEGG|SEGE|SEGC|SEGD,      // 6
    SEGA|SEGB|SEGC,                     // 7
    SEGA|SEGB|SEGC|SEGD|SEGE|SEGF|SEGG, // 8
    SEGA|SEGB|SEGF|SEGG|SEGC|SEGD       // 9
    };

// Other symbols
#define UNDERSCORE  SEGD
#define MINUS       SEGG
#define GRADE       SEGA|SEGF|SEGB|SEGG
#define CELSIUS     SEGA|SEGF|SEGE|SEGD
#define HBIG        SEGF|SEGB|SEGG|SEGE|SEGC

// function prototypes
extern void MAX7219_init(void); // Initializes MAX7219
extern void MAX7219_send(uint8_t reg, uint8_t dat); // Sends byte data to register
extern void MAX7219_clear(void); // Clears MAX7219 shift register in both decode modes
extern void MAX7219_clearc(void); // Clears MAX7219 shift register using a cursor effect
extern void MAX7219_lclearc(uint8_t startpos); // Clears MAX7219 shift register using a cursor effect arriving at position defined by startpos
extern void MAX7219_putch(uint8_t digit, char ch, bool point); // Writes a char on the digit eventually turning on the comma/decimal point
extern void MAX7219_numch(uint8_t digit, uint8_t n, bool point); // Writes a number from 0 to 9 as char eventually turning on the comma/decimal point
extern void MAX7219_setDecode(void); // Sets the decode mode
extern void MAX7219_setNoDecode(void); // Sets the no-decode mode
extern void MAX7219_setIntensity(uint8_t val); // Sets display brightness from 0(lowest) to MAXINTENSITY (highest)
extern void MAX7219_test(void); // Turns on the test mode
extern void MAX7219_shutdown(bool yesno); // Turns on/off the display visualization
extern void MAX7219_puts(const char *s, bool cursor); // Writes a string using (true) or no (false) the cursor effect
extern void MAX7219_lputs(const char *s, bool cursor, uint8_t startpos); // Writes a string using (true) or no (false) the cursor effect, starting from startpos
extern uint8_t MAX7219_putun(uint32_t num, uint8_t decimals, uint8_t rightspace); // Writes an unsigned integer, returns most-left digit used
extern uint8_t MAX7219_putn(int32_t num, uint8_t decimals, uint8_t rightspace); // Writes an integer, returns most-left digit used
extern void MAX7219_scroll(const char *s, bool appear, bool disappear); // Writes a string using the scrolling effect
extern void MAX7219_glow(uint8_t times); // Glows the display
extern void MAX7219_blink(uint8_t times); // Blinks the display
