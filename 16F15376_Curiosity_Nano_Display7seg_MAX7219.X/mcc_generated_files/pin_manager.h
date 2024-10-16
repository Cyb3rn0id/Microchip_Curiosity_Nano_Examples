/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
        Device            :  PIC16F15376
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.00
        MPLAB 	          :  MPLAB X 5.10	
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set LED0 aliases
#define LED0_TRIS                 TRISAbits.TRISA2
#define LED0_LAT                  LATAbits.LATA2
#define LED0_PORT                 PORTAbits.RA2
#define LED0_WPU                  WPUAbits.WPUA2
#define LED0_OD                   ODCONAbits.ODCA2
#define LED0_ANS                  ANSELAbits.ANSA2
#define LED0_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define LED0_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define LED0_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define LED0_GetValue()           PORTAbits.RA2
#define LED0_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define LED0_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define LED0_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define LED0_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define LED0_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define LED0_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define LED0_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define LED0_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set MAX_DAT aliases
#define MAX_DAT_TRIS                 TRISCbits.TRISC0
#define MAX_DAT_LAT                  LATCbits.LATC0
#define MAX_DAT_PORT                 PORTCbits.RC0
#define MAX_DAT_WPU                  WPUCbits.WPUC0
#define MAX_DAT_OD                   ODCONCbits.ODCC0
#define MAX_DAT_ANS                  ANSELCbits.ANSC0
#define MAX_DAT_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define MAX_DAT_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define MAX_DAT_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define MAX_DAT_GetValue()           PORTCbits.RC0
#define MAX_DAT_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define MAX_DAT_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define MAX_DAT_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define MAX_DAT_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define MAX_DAT_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define MAX_DAT_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define MAX_DAT_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define MAX_DAT_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set MAX_CLK aliases
#define MAX_CLK_TRIS                 TRISCbits.TRISC1
#define MAX_CLK_LAT                  LATCbits.LATC1
#define MAX_CLK_PORT                 PORTCbits.RC1
#define MAX_CLK_WPU                  WPUCbits.WPUC1
#define MAX_CLK_OD                   ODCONCbits.ODCC1
#define MAX_CLK_ANS                  ANSELCbits.ANSC1
#define MAX_CLK_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define MAX_CLK_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define MAX_CLK_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define MAX_CLK_GetValue()           PORTCbits.RC1
#define MAX_CLK_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define MAX_CLK_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define MAX_CLK_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define MAX_CLK_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define MAX_CLK_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define MAX_CLK_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define MAX_CLK_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define MAX_CLK_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set SW0 aliases
#define SW0_TRIS                 TRISCbits.TRISC2
#define SW0_LAT                  LATCbits.LATC2
#define SW0_PORT                 PORTCbits.RC2
#define SW0_WPU                  WPUCbits.WPUC2
#define SW0_OD                   ODCONCbits.ODCC2
#define SW0_ANS                  ANSELCbits.ANSC2
#define SW0_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define SW0_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define SW0_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define SW0_GetValue()           PORTCbits.RC2
#define SW0_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define SW0_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define SW0_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define SW0_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define SW0_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define SW0_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define SW0_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define SW0_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set MAX_LAT aliases
#define MAX_LAT_TRIS                 TRISCbits.TRISC3
#define MAX_LAT_LAT                  LATCbits.LATC3
#define MAX_LAT_PORT                 PORTCbits.RC3
#define MAX_LAT_WPU                  WPUCbits.WPUC3
#define MAX_LAT_OD                   ODCONCbits.ODCC3
#define MAX_LAT_ANS                  ANSELCbits.ANSC3
#define MAX_LAT_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define MAX_LAT_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define MAX_LAT_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define MAX_LAT_GetValue()           PORTCbits.RC3
#define MAX_LAT_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define MAX_LAT_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define MAX_LAT_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define MAX_LAT_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define MAX_LAT_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define MAX_LAT_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define MAX_LAT_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define MAX_LAT_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/