/*
 * PIC16F15376 Curiosity Nano + ADXL345 I2C Accelerometer
 * Example
 * (c)2020 Giovanni Bernardo
 * https://www.settorezero.com
 *
 * Output on USB CDC (UART 9600N81)
 * Output on 7-Segment display controlled by MAX7219
 * 
 * Accelerometer Breakout board I've used:
 * https://www.sparkfun.com/products/9836
 * 
 *
 * Pinout is defined thorough MPLAB Code Configurator:
 * RD0 -> TX2 (CDC)
 * RD1 -> RX2 (CDC)
 * RC3 -> SCL1
 * RC4 -> SDA1
 * RC0 -> MAX7219 data
 * RC1 -> MAX7219 clock
 * RC2 -> MAX7219 latch (data/!cs)
 *
 * the MAX7219 library used is my one:
 * (https://github.com/Cyb3rn0id/MAX7219sz_PIC_lib)
 *
 * HARDWARE CONSIDERATIONS
 *
 * BOARD POWERING
 * Set the PIC16F15376 Curiosity Nano for working at 3.3V
 * you do this in the project options -> PKOB nano options -> Power
 * (see readme here: https://github.com/Cyb3rn0id/Microchip_Curiosity_Nano_Examples)
 *
 * ACCELEROMETER POWERING
 * The ADXL345 runs at 3.3V, so you can power it using the VTG pin on the board
 *
 * MAX7219 POWERING
 * If you use the MAX7219 for output reading, since this works at 5V
 * you can power it from the VBUS pin on the board, there is no need
 * to translate logic levels since 3.3V logic levels from the microcontroller
 * are good for the MAX7219.
 *
 * I2C HARDWARE SETUP
 * Remember to put 4.7K pull-up resistors
 * on SDA1 and SCL1 lines through the 3.3V line
 *
 * UART HARDWARE SETUP
 * UART output is on the USB connector of the board since I've used RD0 and RD1
 * on the EUSART2 that is connected to USB CDC of the debbugger
 */
#pragma warning disable 520 // suppress annoying 'funtion not used' warnings
#pragma warning disable 2053 // suppress annoying 'funtion not used' warnings

// 7-bit ADXL345 address with 'alternate address' pin (pin 12) tied to GND
// (SDO pin on the breakout board by sparkfun)
// this address will be automatic translated in:
// (0x53<<1 | 1) for reading (0xA7)
// (0x53<<1) 	 for writing (0xA6)
#define ADXL_ADDRESS	0x53

#include <stdlib.h> // used only for abs function
#include "mcc_generated_files/mcc.h"
// MCC creates this example files, we'll use them
#include "mcc_generated_files/examples/i2c1_master_example.h"
#include "MAX7219sz.h"

uint8_t readBuffer[6]; // I2C reading buffer
// axis values
int16_t x=0;
int16_t y=0;
int16_t z=0;

// previous axis values
int16_t px=0;
int16_t py=0;
int16_t pz=0;

void main(void)
{
    SYSTEM_Initialize();
    MAX7219_init(); 
    // Start ADXL345
    // by putting bit 3 (ASLEEP) of ACT_TAP_STATUS register (0x2D), to 1
	// there is no need to change ADXL_ADDRESS to 8bit for reading and writing
	// since MCC library make this and accepts only the 7bit address
    I2C1_Write1ByteRegister(ADXL_ADDRESS, 0x2D, 0x08);
    
	uint8_t m=0; // used for display visualization
    int16_t d=0; // used to display actual selected axis value
    while (1)
        {
        static uint8_t i=32; // 32 consecutive readings
        while(i--)
			{
			I2C1_ReadDataBlock(ADXL_ADDRESS,0x32,readBuffer,6);
			x+=(int16_t)(readBuffer[1] << 8 | readBuffer[0]);   
			y+=(int16_t)(readBuffer[3] << 8 | readBuffer[2]);
			z+=(int16_t)(readBuffer[5] << 8 | readBuffer[4]);
			__delay_ms(2);
			}
        // division by 32 (2^5 : right shift by 5 pos)
        x>>=5;
        y>>=5;
        z>>=5;
        
        // report values on the UART
        printf("x=%d y=%d z=%d\r",x,y,z);
        
        // don't update axis value if difference is only 1 unit
        // respect the previous value. I do this for value visualized
        // on display to make values appear more stable
        if (abs(x-px)==1) {x=px;} else {px=x;}
        if (abs(z-pz)==1) {z=pz;} else {pz=z;}
        if (abs(y-py)==1) {y=py;} else {py=y;}
        
		// which axis to visualize on the display
		// I'll write A,b,c instead of x,y,z since are more readable
        switch (m)
            {
            case 0: // x
                d=x;
                MAX7219_putch(8,'a',false);
                break;
                
            case 1: // y
                d=y;
                MAX7219_putch(8,'b',false);
                break;
                
            case 2: // z
                d=z;
                MAX7219_putch(8,'c',false);
                break;
            }
		// write the axis value I've transferred in the 'd' variable
        MAX7219_putn(d,0,0); 
        
        // reset values for next readings
        x=0;
        y=0;
        z=0;
        i=32;
        
        // change display visualization on SW0 pressure
        if (!SW0_GetValue())
            {
            __delay_ms(80);
            while (!SW0_GetValue()) {continue;}
                m++;
                if (m>2) m=0;
            }
        
    }
}
