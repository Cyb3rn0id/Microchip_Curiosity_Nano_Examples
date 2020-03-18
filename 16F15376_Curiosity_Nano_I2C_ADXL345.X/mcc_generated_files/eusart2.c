/**
  EUSART2 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    eusart2.c

  @Summary
    This is the generated driver implementation file for the EUSART2 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides APIs for EUSART2.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.80.0
        Device            :  PIC16F15376
        Driver Version    :  2.1.0
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.10 and above
        MPLAB 	          :  MPLAB X 5.30
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

/**
  Section: Included Files
*/
#include "eusart2.h"

volatile eusart2_status_t eusart2RxLastError;

/**
  Section: EUSART2 APIs
*/

void (*EUSART2_FramingErrorHandler)(void);
void (*EUSART2_OverrunErrorHandler)(void);
void (*EUSART2_ErrorHandler)(void);

void EUSART2_DefaultFramingErrorHandler(void);
void EUSART2_DefaultOverrunErrorHandler(void);
void EUSART2_DefaultErrorHandler(void);

void EUSART2_Initialize(void)
{
    // Set the EUSART2 module to the options selected in the user interface.

    // ABDOVF no_overflow; SCKP Non-Inverted; BRG16 16bit_generator; WUE disabled; ABDEN disabled; 
    BAUD2CON = 0x08;

    // SPEN enabled; RX9 8-bit; CREN enabled; ADDEN disabled; SREN disabled; 
    RC2STA = 0x90;

    // TX9 8-bit; TX9D 0; SENDB sync_break_complete; TXEN enabled; SYNC asynchronous; BRGH hi_speed; CSRC slave; 
    TX2STA = 0x24;

    // SP2BRGL 64; 
    SP2BRGL = 0x40;

    // SP2BRGH 3; 
    SP2BRGH = 0x03;


    EUSART2_SetFramingErrorHandler(EUSART2_DefaultFramingErrorHandler);
    EUSART2_SetOverrunErrorHandler(EUSART2_DefaultOverrunErrorHandler);
    EUSART2_SetErrorHandler(EUSART2_DefaultErrorHandler);

    eusart2RxLastError.status = 0;

}

bool EUSART2_is_tx_ready(void)
{
    return (bool)(PIR3bits.TX2IF && TX2STAbits.TXEN);
}

bool EUSART2_is_rx_ready(void)
{
    return (bool)(PIR3bits.RC2IF);
}

bool EUSART2_is_tx_done(void)
{
    return TX2STAbits.TRMT;
}

eusart2_status_t EUSART2_get_last_status(void){
    return eusart2RxLastError;
}

uint8_t EUSART2_Read(void)
{
    while(!PIR3bits.RC2IF)
    {
    }

    eusart2RxLastError.status = 0;
    
    if(1 == RC2STAbits.OERR)
    {
        // EUSART2 error - restart

        RC2STAbits.CREN = 0; 
        RC2STAbits.CREN = 1; 
    }

    return RC2REG;
}

void EUSART2_Write(uint8_t txData)
{
    while(0 == PIR3bits.TX2IF)
    {
    }

    TX2REG = txData;    // Write the data byte to the USART.
}

char getch(void)
{
    return EUSART2_Read();
}

void putch(char txData)
{
    EUSART2_Write(txData);
}



void EUSART2_DefaultFramingErrorHandler(void){}

void EUSART2_DefaultOverrunErrorHandler(void){
    // EUSART2 error - restart

    RC2STAbits.CREN = 0;
    RC2STAbits.CREN = 1;

}

void EUSART2_DefaultErrorHandler(void){
}

void EUSART2_SetFramingErrorHandler(void (* interruptHandler)(void)){
    EUSART2_FramingErrorHandler = interruptHandler;
}

void EUSART2_SetOverrunErrorHandler(void (* interruptHandler)(void)){
    EUSART2_OverrunErrorHandler = interruptHandler;
}

void EUSART2_SetErrorHandler(void (* interruptHandler)(void)){
    EUSART2_ErrorHandler = interruptHandler;
}


/**
  End of File
*/
