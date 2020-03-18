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
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.80.0
        Device            :  PIC16F15376
        Driver Version    :  2.11
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

// get/set MAX_LAT aliases
#define MAX_LAT_TRIS                 TRISCbits.TRISC2
#define MAX_LAT_LAT                  LATCbits.LATC2
#define MAX_LAT_PORT                 PORTCbits.RC2
#define MAX_LAT_WPU                  WPUCbits.WPUC2
#define MAX_LAT_OD                   ODCONCbits.ODCC2
#define MAX_LAT_ANS                  ANSELCbits.ANSC2
#define MAX_LAT_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define MAX_LAT_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define MAX_LAT_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define MAX_LAT_GetValue()           PORTCbits.RC2
#define MAX_LAT_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define MAX_LAT_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define MAX_LAT_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define MAX_LAT_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define MAX_LAT_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define MAX_LAT_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define MAX_LAT_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define MAX_LAT_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set RC3 procedures
#define RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define RC3_GetValue()              PORTCbits.RC3
#define RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define RC3_SetPullup()             do { WPUCbits.WPUC3 = 1; } while(0)
#define RC3_ResetPullup()           do { WPUCbits.WPUC3 = 0; } while(0)
#define RC3_SetAnalogMode()         do { ANSELCbits.ANSC3 = 1; } while(0)
#define RC3_SetDigitalMode()        do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set RC4 procedures
#define RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RC4_GetValue()              PORTCbits.RC4
#define RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define RC4_SetPullup()             do { WPUCbits.WPUC4 = 1; } while(0)
#define RC4_ResetPullup()           do { WPUCbits.WPUC4 = 0; } while(0)
#define RC4_SetAnalogMode()         do { ANSELCbits.ANSC4 = 1; } while(0)
#define RC4_SetDigitalMode()        do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set RD0 procedures
#define RD0_SetHigh()            do { LATDbits.LATD0 = 1; } while(0)
#define RD0_SetLow()             do { LATDbits.LATD0 = 0; } while(0)
#define RD0_Toggle()             do { LATDbits.LATD0 = ~LATDbits.LATD0; } while(0)
#define RD0_GetValue()              PORTDbits.RD0
#define RD0_SetDigitalInput()    do { TRISDbits.TRISD0 = 1; } while(0)
#define RD0_SetDigitalOutput()   do { TRISDbits.TRISD0 = 0; } while(0)
#define RD0_SetPullup()             do { WPUDbits.WPUD0 = 1; } while(0)
#define RD0_ResetPullup()           do { WPUDbits.WPUD0 = 0; } while(0)
#define RD0_SetAnalogMode()         do { ANSELDbits.ANSD0 = 1; } while(0)
#define RD0_SetDigitalMode()        do { ANSELDbits.ANSD0 = 0; } while(0)

// get/set RD1 procedures
#define RD1_SetHigh()            do { LATDbits.LATD1 = 1; } while(0)
#define RD1_SetLow()             do { LATDbits.LATD1 = 0; } while(0)
#define RD1_Toggle()             do { LATDbits.LATD1 = ~LATDbits.LATD1; } while(0)
#define RD1_GetValue()              PORTDbits.RD1
#define RD1_SetDigitalInput()    do { TRISDbits.TRISD1 = 1; } while(0)
#define RD1_SetDigitalOutput()   do { TRISDbits.TRISD1 = 0; } while(0)
#define RD1_SetPullup()             do { WPUDbits.WPUD1 = 1; } while(0)
#define RD1_ResetPullup()           do { WPUDbits.WPUD1 = 0; } while(0)
#define RD1_SetAnalogMode()         do { ANSELDbits.ANSD1 = 1; } while(0)
#define RD1_SetDigitalMode()        do { ANSELDbits.ANSD1 = 0; } while(0)

// get/set LED0 aliases
#define LED0_TRIS                 TRISEbits.TRISE0
#define LED0_LAT                  LATEbits.LATE0
#define LED0_PORT                 PORTEbits.RE0
#define LED0_WPU                  WPUEbits.WPUE0
#define LED0_OD                   ODCONEbits.ODCE0
#define LED0_ANS                  ANSELEbits.ANSE0
#define LED0_SetHigh()            do { LATEbits.LATE0 = 1; } while(0)
#define LED0_SetLow()             do { LATEbits.LATE0 = 0; } while(0)
#define LED0_Toggle()             do { LATEbits.LATE0 = ~LATEbits.LATE0; } while(0)
#define LED0_GetValue()           PORTEbits.RE0
#define LED0_SetDigitalInput()    do { TRISEbits.TRISE0 = 1; } while(0)
#define LED0_SetDigitalOutput()   do { TRISEbits.TRISE0 = 0; } while(0)
#define LED0_SetPullup()          do { WPUEbits.WPUE0 = 1; } while(0)
#define LED0_ResetPullup()        do { WPUEbits.WPUE0 = 0; } while(0)
#define LED0_SetPushPull()        do { ODCONEbits.ODCE0 = 0; } while(0)
#define LED0_SetOpenDrain()       do { ODCONEbits.ODCE0 = 1; } while(0)
#define LED0_SetAnalogMode()      do { ANSELEbits.ANSE0 = 1; } while(0)
#define LED0_SetDigitalMode()     do { ANSELEbits.ANSE0 = 0; } while(0)

// get/set SW0 aliases
#define SW0_TRIS                 TRISEbits.TRISE2
#define SW0_LAT                  LATEbits.LATE2
#define SW0_PORT                 PORTEbits.RE2
#define SW0_WPU                  WPUEbits.WPUE2
#define SW0_OD                   ODCONEbits.ODCE2
#define SW0_ANS                  ANSELEbits.ANSE2
#define SW0_SetHigh()            do { LATEbits.LATE2 = 1; } while(0)
#define SW0_SetLow()             do { LATEbits.LATE2 = 0; } while(0)
#define SW0_Toggle()             do { LATEbits.LATE2 = ~LATEbits.LATE2; } while(0)
#define SW0_GetValue()           PORTEbits.RE2
#define SW0_SetDigitalInput()    do { TRISEbits.TRISE2 = 1; } while(0)
#define SW0_SetDigitalOutput()   do { TRISEbits.TRISE2 = 0; } while(0)
#define SW0_SetPullup()          do { WPUEbits.WPUE2 = 1; } while(0)
#define SW0_ResetPullup()        do { WPUEbits.WPUE2 = 0; } while(0)
#define SW0_SetPushPull()        do { ODCONEbits.ODCE2 = 0; } while(0)
#define SW0_SetOpenDrain()       do { ODCONEbits.ODCE2 = 1; } while(0)
#define SW0_SetAnalogMode()      do { ANSELEbits.ANSE2 = 1; } while(0)
#define SW0_SetDigitalMode()     do { ANSELEbits.ANSE2 = 0; } while(0)

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