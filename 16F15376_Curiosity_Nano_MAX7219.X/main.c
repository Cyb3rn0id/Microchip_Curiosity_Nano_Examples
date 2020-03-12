/* 
 * DEMO for MAX7219sz PIC lib version 1.0
 * 
 * This file is part of the MAX7219sz_PIC_lib package:
 * https://github.com/Cyb3rn0id/MAX7219sz_PIC_lib
 * 
 * Copyright (c) 2020 Giovanni Bernardo.
 * https://www.settorezero.com
 * 
 * This DEMO was made for the PIC16F18446 Curiosity Nano
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

#pragma warning disable 520 // suppress annoying "function not used" warnings

#include "mcc_generated_files/mcc.h"
#include "MAX7219sz.h"

void main(void)
    {
    // initialize the device
    SYSTEM_Initialize();
    
    // turn on the test mode
    MAX7219_test();
    __delay_ms(1000);
    // init the MAX7219
    MAX7219_init(); 
    
    while (1)
    {
    // blinking effect on a underscore
    MAX7219_putch(8,'_',false);
    MAX7219_blink(5);
    MAX7219_clear();
    
    // simple texts
    // the "true" will make the function use the cursor effect
    MAX7219_puts("7219demo",true);
    __delay_ms(1000);
    
    // this function will erase the digits using the cursor effect
    // from the most-right digit used to the first char on the left
    MAX7219_clearc();
    
    MAX7219_puts("by.........",true);
    __delay_ms(1000);
    MAX7219_clearc();
    
    // if you can notice: the clearc function will start the cursor
    // from the second 'i', not from the most right digit!
    MAX7219_puts("Gianni",true);
    __delay_ms(1000);
    MAX7219_clearc();
    
    // print some integers
    MAX7219_puts("integers",true);
    __delay_ms(1000);
    MAX7219_clearc();
    
    MAX7219_putn(-31581,0,0);
    __delay_ms(1000);
    
    // this number uses less digits than previous one, but function
    // will automagically delete unused chars without performing
    // a display clear
    MAX7219_putn(-1,0,0); 
    __delay_ms(1000);
    
    // this is the lowest number you can show on an 8-digit display
    MAX7219_putn(-9999999,0,0); 
    __delay_ms(1000);
        
    // another case of less digits number respect than previous one 
    MAX7219_putn(12,0,0);
    __delay_ms(1000);
        
    // the biggest number you can show on an 8-digit display
    MAX7219_putn(99999999,0,0); 
    __delay_ms(1000);
    
    // a simple counter. Notice I've not used a clear function
    // for erasing the display, since previous function had used a number
    // and this function will also use a number
    for (uint8_t i=0; i<21; i++)
        {
        MAX7219_putun(i,0,0);
        __delay_ms(100);
        }
    __delay_ms(1000);
    
    // let's try some fixed-point decimal numbers
    MAX7219_puts("decimals",true);
    __delay_ms(1000);
    MAX7219_clearc();
    
    // I want to write -9.231
    // since this number has 3 decimals, I'll multiply
    // it by 1000 and then set 3 decimals:
    // -9231 => my number
    // 3 => my number must have 3 decimals
    // 0 => no spaces at right
    MAX7219_putn(-9231,3,0); 
    __delay_ms(1000);
    
    // this will write 0.1
    // 0.1 transformed in integer: multiply by 10=>1
    // 1 decimal, 0 spaces at right
    MAX7219_putn(1,1,0); 
    __delay_ms(1000);
    
    // this will weite 3.14 => 314 with 2 decimals
    MAX7219_putn(314,2,0);
    __delay_ms(1000);
    
    // this will write -0.02 => -2 with 2 decimals
    MAX7219_putn(-2,2,0);
    __delay_ms(1000);
    
    // example of right space
    // I can use for writing a symbol
    MAX7219_puts("symbol",true);
    __delay_ms(1000);
    MAX7219_clearc();
    
    // those 3 instructions will write 24.1°C
    MAX7219_putun(241,1,2);
    MAX7219_send(2,GRADE);
    MAX7219_send(1,CELSIUS); 
    
    __delay_ms(1000);
    __delay_ms(1000);
    
    MAX7219_clearc();
    
    // flash-fading using intensity register
    MAX7219_puts("flashing",true);
    MAX7219_glow(5);
    MAX7219_clearc();
	
    // scroller functions
    MAX7219_puts("scroller",true);
    __delay_ms(1000);
    MAX7219_clearc();
    
    // the string will appear from right and will completely disappear from right to left
    MAX7219_scroll("this is a scrolling demonstration...   settorezero.com",true,true);
    MAX7219_clear();
    
    // example: the string will appear immediately and will completely disappear from right to left
    // if defined the string in an array
    const char ex1[]="scrollout";
    // the puts will use only the first 8 (DIGITS) chars
    // I've included the puts function only for giving you the time to read 
    MAX7219_puts(ex1,true); 
    __delay_ms(1000);
    // this will scroll the string
    // second parameter=false: the first 8 (DIGITS) chars will appear immediately
    // third parameter=true: the string will go out of the display
    MAX7219_scroll(ex1,false,true);
    MAX7219_clear();
    
    // example: the string will appear immediately and will stop at last chars
    // I've put the first 8 chars of example string, with a pause
    // only for giving some time for reading
    const char ex[]="scroll and stop";
    MAX7219_puts(ex,true); // this will print only the first 8 chars
    __delay_ms(1000);
    
    // this will scroll the string
    // second parameter=false: the first 8 (DIGITS) chars will appear immediately
    // third parameter: the last 8 (DIGITS) chars will remain visualized
    MAX7219_scroll(ex,false,false);
    __delay_ms(1000);
    
    MAX7219_clear();
    } // while
}
