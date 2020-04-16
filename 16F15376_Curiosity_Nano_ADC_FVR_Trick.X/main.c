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
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.0
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
#pragma warning disable 520

#include "mcc_generated_files/mcc.h"

uint16_t Vbat=0;
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    while (1)
    {
     ADC_SelectChannel(channel_FVR_BUF1);
     ADC_StartConversion(); // ADCON0bits.ADGO = 1;
     
     while (!ADC_IsConversionDone()) {continue;} // !ADCON0bits.ADGO
     Vbat=ADC_GetConversionResult(); // (ADRESH << 8) + ADRESL)
     
    /*
     * ADC module on this PIC is 10bit
     * So will return values from 0 to 1023 (1024 steps)
     * Powering the PIC at 4.2V from a Lipo ad using VDD as positive reference
     * we'll have 4.2/1024 = 4.102mv/bit
     * and so, since the FVR is set to 1024mV, reading on FVR will
     * give a value of 1024/4.102 = 250
     * 
     * If VDD lower to 2.8V, the new reference of ADC is 2.8V
     * so now the resolution of ADC module will be:
     * 2.8/1024 = 2.734mv/bit
     * Now the reading of 1024mV from FVR will be:
     * 1024/2.734 = 375
     */
      
     printf("Reading of 1024mv from FVR is: %d\n", Vbat);

     if (Vbat>375)
        {
        LED0_SetLow(); // turn ON the led
        }
     else
        {
        LED0_SetHigh(); // turn OFF the led
        }
    
    __delay_ms(500);
    __delay_ms(500);
    __delay_ms(500);
    __delay_ms(500);
    }
}
/**
 End of File
*/