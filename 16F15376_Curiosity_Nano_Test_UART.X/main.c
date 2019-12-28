/*
    Esempio utilizzo UART su PIC16F15376 Curiosity Nano
    By Bernardo Giovanni
    https://www.settorezero.com

    Il PIC16F15376 Curiosity Nano ha la porta seriale CDC
    collegata sui pin RD0 (TX) e RD1 (RX) che possono essere gestiti dalla UART2.
    Di default la UART2 non usa quei pin, per cui nella configurazione
    bisogna cambiarla.
    Se si vuole ridirigere lo STDIO per usare printf, oltre all'apposita
    opzione nella configurazione tramite MCC, includere anche stdio nel main
    altrimenti si genera un errore non definito in compilazione perchè
    non riconosce printf.
    In questo esempio la UART è impostata a 9600,N,8,1
    con oscillatore interno a 32MHz

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
#include <stdio.h> // aggiunto al main per poter usare printf
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
    
    while (1)
    {
        // Add your application code
        if (!SW0_GetValue()) // pulsante premuto
            {
            LED0_SetLow(); // accendo il led
            __delay_ms(80); // ritardo per antirimbalzo
            if (!SW0_GetValue()) // controllo che il pulsante negli 80mS sia ancora premuto
                {
                printf("BUTTON PRESSED\r"); // messaggio su seriale   
                while(!SW0_GetValue()); // rimango bloccato finchè non si rilascia il pulsante
                __delay_ms(100); // ulteriore ritardo per ricominciare il ciclo
                }
        LED0_SetHigh(); // spengo il led
        }
    } // while(1)
}
/**
 End of File
*/
