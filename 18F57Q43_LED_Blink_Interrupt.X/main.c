 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.2
 *
 * @version Package Version: 3.1.2
*/

/*
© [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#pragma warning disable 520 // suppress "function not used" warnings
#include "mcc_generated_files/system/system.h"

// Function prototypes
void ISR_TMR0(void); // my own defined interrupt on timer0
// structure used for setting timer0 parameters (defined in tmr0.c)
static const struct TMR_INTERFACE *Timer = &Timer0;

int main(void)
{
    SYSTEM_Initialize();
    // set the callback function for timer interrupt using the structure 
    // instead of the function TMR0_OverflowCallbackRegister
    Timer->TimeoutCallbackRegister(ISR_TMR0); 
    
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts 
    // Use the following macros to: 

    // Enable the Global High Interrupts 
    INTERRUPT_GlobalInterruptHighEnable(); // I've set Timer0 Interrupt as high priority

    // Disable the Global High Interrupts 
    //INTERRUPT_GlobalInterruptHighDisable(); 

    // Enable the Global Low Interrupts 
    //INTERRUPT_GlobalInterruptLowEnable(); 

    // Disable the Global Low Interrupts 
    //INTERRUPT_GlobalInterruptLowDisable(); 
    while(1)
    {
    }    
}

// timer every 4uS defined from TMR0 component in melody
// (I can't go below 4uS even if is possible: if I put 1uS = 0.000001S = 1000nS, interrupt will occur every 4us)
void ISR_TMR0(void)
    {
    static uint32_t i=0;
    i++;
    if (i==125000) //125'000x4uS => 500'000uS => 500mS => 0.5sec
        {
        i=0;
        LED0_Toggle(); // toggle every 0.5S => period 1S => frequency 1Hz
        // IO debug is always the RB4 pin (yes, the same where the button is located)
        // this debug pin is the "GPIO0" pin (DBG2 on the debugger header)
        IO_debug_Toggle(); 
        }
    }