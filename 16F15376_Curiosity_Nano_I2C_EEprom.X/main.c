/*
 * PIC16F15376 Curiosity Nano + I2C EEPROM
 * Example
 * WARNING: compatible only with EEproms from 24C32 to up
 * (c)2020 Giovanni Bernardo
 * https://www.settorezero.com
 *
 * Output on USB CDC (UART 9600N81)
 * 
 * Pinout is defined thorough MPLAB Code Configurator:
 * RD0 -> TX2 (CDC)
 * RC3 -> SCL1
 * RC4 -> SDA1
 * RE0 -> LED0
 * RE2 -> SW0
 *
 * HARDWARE CONSIDERATIONS
 *
 * BOARD POWERING
 * Set the PIC16F15376 Curiosity Nano for working at 5V
 * you do this in the project options -> PKOB nano options -> Power
 * (see readme here: https://github.com/Cyb3rn0id/Microchip_Curiosity_Nano_Examples)
 *
 *
 * I2C HARDWARE SETUP
 * Remember to put 2.2K pull-up resistors
 * on SDA1 and SCL1 lines through the VBus line (5V)
 *
 * UART HARDWARE SETUP
 * UART output is on the USB connector of the board since I've used RD0
 * on the EUSART2 that is connected to USB CDC of the debbugger
 */

#pragma warning disable 520 // suppress annoying 'funtion not used' warnings
#pragma warning disable 2053 // suppress annoying 'funtion not used' warnings

// 7-bit EEPROM5 address
// EEPROMs 7bit address is usually 0b1010[A2][A1][A0]
// I've tied A2 (pin 3), A1 (pin 2) and A0 (pin 1) to GND
// so the 7bit address is 0b1010000 (0x50)
// this address will be automatic translated in:
// (0b1010000<<1 | 1) for reading (0xA1)
// (0b1010000<<1) 	 for writing (0xA0)
#define EEPROM_ADDRESS	0x50

#include "mcc_generated_files/mcc.h"
#include "i2c1_eeprom.h"

uint8_t value=0;
uint16_t location=0;
uint8_t retval=0;

void waitButton(void)
    {
    printf("Push SW0 to continue\n\r");
    LED0_SetHigh(); // turn off the led
    while (SW0_GetValue()); // stay blocked util SW0 pressed    
    __delay_ms(100);
    while (!SW0_GetValue());
    LED0_SetLow(); // turn on the led
    }

void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    
    while (1)
        {
        printf("I2C EEprom demo start\n");
        waitButton();
    
        //**********************************************************************
        // SINGLE VALUE WRITE
        //**********************************************************************
        printf("Now I'll write:\n");
    
        value=77;
        location=0;
        printf("value %d in the EEPROM location %d\n",value,location);
        I2C1_EEpromWrite(EEPROM_ADDRESS, location, value);
        __delay_ms(10);
    
        value=15;
        location=1;
        printf("value %d in the EEPROM location %d\n",value,location);
        I2C1_EEpromWrite(EEPROM_ADDRESS, location, value);
        __delay_ms(10);
        
        printf("Write complete\n");
        waitButton();
        
        //**********************************************************************
        // SINGLE VALUE READ
        //**********************************************************************
        printf("Now I'll read those value back from EEprom\n");
        
        location=0;
        retval=0;
        retval=I2C1_EEpromRead(EEPROM_ADDRESS, location);
        printf("Value from location %d is %d\n",location,retval);
        
        location=1;
        retval=0;
        retval=I2C1_EEpromRead(EEPROM_ADDRESS, location);
        printf("Value from location %d is %d\n",location,retval);
        waitButton();
        
        
        //**********************************************************************
        // BLOCK WRITE
        //**********************************************************************
        uint8_t s[16]="Settorezero.com";
        uint8_t s_size=16;
        location=2;
        
        printf("I'll write the data block \"%s\" starting from location %d\n",&s,location);
        I2C1_EEpromWriteBlock(EEPROM_ADDRESS, location, s, s_size);
        printf("Write complete\n");
        waitButton();
        
        //**********************************************************************
        // BLOCK READ
        //**********************************************************************
        uint8_t f[16]="";
        uint8_t f_size=16;
        printf("I'll read back the data block from location %d\n",location);
        I2C1_EEpromReadBlock(EEPROM_ADDRESS, location, f, f_size);
        printf("Read complete\n");
        __delay_ms(100);
        printf("Block obtained:\n");
        uint8_t i=0;
        while (i < f_size)
            {
            printf("%c",f[i++]);
            }
        printf("\nProgram ended\n\r");    
        waitButton();
        }
}
/**
 End of File
*/