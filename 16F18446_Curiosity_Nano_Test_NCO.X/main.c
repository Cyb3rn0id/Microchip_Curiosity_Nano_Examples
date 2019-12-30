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
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
        Device            :  PIC16F18446
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
#include <stdint.h>

// il modulo NCO1 ottiene il valore di frequenza da impostare
// mediante un numero a 24 bit inserito nei 3 registri
// NCO1 INCrement (LOW, HIGH e UPPER)
void setNCOincrement(uint32_t val)
    {
    NCO1INCL=(uint8_t)val;
    NCO1INCH=(uint8_t)(val>>=8);
    NCO1INCU=(uint8_t)(val>>=8);
    }
/*
                         Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    // questo valore sar� incrementato ad ogni pressione
    // del pulsante. L'ho messo allo stesso valore iniziale 
    // impostato nei settaggi del modulo NCO.
    // in modalit� FDC (Fixed Duty Cycle), con FOSC=32MHz
    // questo valore causa un overflow del registro di accumulo
    // ogni 495uS (vedi formula al paragrafo "NCO Operation" del datasheet)
    // producendo un'onda quadra alla frequenza di 1007Hz
    static uint32_t NCOval=0x42;
    while (1)
        {
        // Add your application code
        if (!SW0_GetValue())
            {
            LED0_SetLow();
            __delay_ms(80);
            if(!SW0_GetValue())
                {
                setNCOincrement(NCOval++);
                }
            __delay_ms(100);
            LED0_SetHigh();
            while(!SW0_GetValue());
            }
        }
}
/**
 End of File
*/