/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.78
        Device            :  PIC16F15376
        Driver Version    :  2.00
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

#include "mcc_generated_files/mcc.h"
#include "hd44780sz.h"
#pragma warning disable 520 // suppress "function not used" warnings

// encoder ticks management
uint8_t cpVar=0; // counter used for counting ticks for increment (every CCOUNT ticks => var increment by 1)
uint8_t cnVar=0;  // counter used for counting ticks for dencrement (every CCOUNT ticks => var increment by 1)
#define CCOUNT 3

// encoder rotation management
bool EncoderState=false; // true=dir and pulse at same level
bool EncAntibounce=false; // encoder rotation antibounce
uint8_t EncTimer=0;
#define ENCTIMERESTART  4

// menu pages
uint8_t menu_page=0; // actual menu page (0-based index)
#define MENUPAGES 2 // total pages

// variables
uint16_t var=50; // first var
#define MAXVAR  100 // max value for first var
const char var1name[]="First variable      "; // number of chars=display chars per row
uint16_t var2=100; // second var
#define MAXVAR2 200 // max value for second var
const char var2name[]="Second variable     ";


// Interrupt on change for:
// RC2 (any)
// RC3 (any)
// RC4 (negative)
// in pin_manager (inizialize) are activated interrupts for port Cx:
// IOCCN (active for negative edge on port C)
// IOCCP (active for positive edge on port C)
// both IOCCN and IOCCP for any change
// then you check IOCCF for each port (interrupt flag)

void Encoder_Pulse_ISR(void)
    {
    if (EncAntibounce) return; // antibounce routine in progress: please wait
    
    // disable interrupts on encoder pulse/dir 
    IOCCNbits.IOCCN2 = 0;
    IOCCPbits.IOCCP2 = 0;
    IOCCNbits.IOCCN3 = 0;
    IOCCPbits.IOCCP3 = 0;
    
    // encoder rotated clockwise (Pulse interrupt)
    if (ENC_PUL_LAT==ENC_DIR_LAT) 
        {
        cnVar=0;
        if (false==EncoderState)
            {
            cpVar++; // increment number of tick counted
            if (cpVar==CCOUNT) // ticks have reached thresold: action!
                {
                // change var depending on page displayed
                switch (menu_page)
                    {
                    case 0: // page 1, I must increment first variable
                        var++;
                        if (var>MAXVAR) var=MAXVAR;   
                        break;
                        
                    case 1: // page 2, I must increment second variable
                        var2++;
                        if (var2>MAXVAR2) var=MAXVAR2;   
                        break;
                        
                    default:
                        break;
                    }
                cpVar=0; // reset ticks
                }
            }
    EncoderState=true;
    }
  else // encoder rotated anti-clockwise
    {
        cpVar=0;
        if (EncoderState) 
        {
            cnVar++;
            if (cnVar==CCOUNT)
                {
                switch (menu_page)
                    {
                    case 0:
                        if (var) var--; 
                        break;
                        
                    case 1:
                        if (var2) var2--; 
                        break;
                        
                    default:
                        break;
                    }
                cnVar=0;
                }
        }
      EncoderState=false;   
  }
   EncAntibounce=true;
}

void Encoder_Dir_ISR(void)
{
    if (EncAntibounce) return;
    
    IOCCNbits.IOCCN2 = 0;
    IOCCPbits.IOCCP2 = 0;
    IOCCNbits.IOCCN3 = 0;
    IOCCPbits.IOCCP3 = 0;
       
    if (ENC_PUL_LAT==ENC_DIR_LAT) // encoder rotated counter-clockwise (Pulse interrupt)
     {
        cpVar=0;
        if (false==EncoderState)
            {
            cnVar++;
            if (cnVar==CCOUNT)
                {
                switch (menu_page)
                    {
                    case 0:
                        if (var) var--; 
                        break;
                        
                    case 1:
                        if (var2) var2--; 
                        break;
                        
                    default:
                        break;
                    }
                cnVar=0;
                }
           }
    EncoderState=true;      
    }
  else // encoder rotated clockwise
    {
        cnVar=0;
        if (EncoderState) 
        {
            cpVar++;
            if (cpVar==CCOUNT)
                {
                
                // change var depending page
                switch (menu_page)
                    {
                    case 0:
                        var++;
                        if (var>MAXVAR) var=MAXVAR;   
                        break;
                        
                    case 1:
                        var2++;
                        if (var2>MAXVAR2) var=MAXVAR2;   
                        break;
                        
                    default:
                        break;
                    }
                
                cpVar=0;
                }
        }
      EncoderState=false;   
      
  }
   EncAntibounce=true;
}

void Timer0_ISR(void)
    {
    if (EncAntibounce)
        {
        EncTimer++;
        if (EncTimer>=ENCTIMERESTART)
            {
            EncTimer=0;
            EncAntibounce=false;
            IOCCNbits.IOCCN2 = 1;
            IOCCPbits.IOCCP2 = 1;
            IOCCNbits.IOCCN3 = 1;
            IOCCPbits.IOCCP3 = 1;
            }
        }
    }

void main(void)
    {
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    //RD4-RD5-RD6-RD7 = data
    //RS=RB4
    //RW=RD2
    //EN=RD3
    
    if (ENC_PUL_LAT==ENC_DIR_LAT) EncoderState=true;
    
    IOCCF2_SetInterruptHandler(*Encoder_Pulse_ISR);
    IOCCF3_SetInterruptHandler(*Encoder_Dir_ISR);
    TMR0_SetInterruptHandler(*Timer0_ISR);
    
    LCDInit();
    LCDPuts(" Menu using Encoder ");
    LCDGoto(2,1);
    LCDPuts("www.settorezero.com ");
    
    while (1)
        {
        
        // encoder button pressed (same as SW0) => change menu page
        if (!ENC_BUT_GetValue())
            {
            __delay_ms(80);
            while (!ENC_BUT_GetValue()) {continue;} // stay until button is released
            menu_page++; // next page
            if (menu_page==MENUPAGES) // total number of pages reached
                {
                menu_page=0; // return at first page
                }
            }

        // change writings depending on actual page
        switch(menu_page)
            {
            case 0:
                LCDGoto(3,1);
                LCDPuts(var1name);
                LCDGoto (4,1);
                LCDPuts("Value: ");
                LCDPutun(var);
                LCDPuts("     ");
                break;
            
            case 1:
                LCDGoto(3,1);
                LCDPuts(var2name);
                LCDGoto (4,1);
                LCDPuts("Value: ");
                LCDPutun(var2);
                LCDPuts("     ");
                break;
            
            default:
                break;
            }
        
        }
}