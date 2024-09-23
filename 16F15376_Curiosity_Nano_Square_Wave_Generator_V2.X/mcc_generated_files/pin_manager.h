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
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.78
        Device            :  PIC16F15376
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.05 and above
        MPLAB 	          :  MPLAB X 5.20	
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

// get/set channel_ANA0 aliases
#define channel_ANA0_TRIS                 TRISAbits.TRISA0
#define channel_ANA0_LAT                  LATAbits.LATA0
#define channel_ANA0_PORT                 PORTAbits.RA0
#define channel_ANA0_WPU                  WPUAbits.WPUA0
#define channel_ANA0_OD                   ODCONAbits.ODCA0
#define channel_ANA0_ANS                  ANSELAbits.ANSA0
#define channel_ANA0_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define channel_ANA0_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define channel_ANA0_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define channel_ANA0_GetValue()           PORTAbits.RA0
#define channel_ANA0_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define channel_ANA0_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define channel_ANA0_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define channel_ANA0_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define channel_ANA0_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define channel_ANA0_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define channel_ANA0_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define channel_ANA0_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set SW1 aliases
#define SW1_TRIS                 TRISBbits.TRISB4
#define SW1_LAT                  LATBbits.LATB4
#define SW1_PORT                 PORTBbits.RB4
#define SW1_WPU                  WPUBbits.WPUB4
#define SW1_OD                   ODCONBbits.ODCB4
#define SW1_ANS                  ANSELBbits.ANSB4
#define SW1_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define SW1_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define SW1_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define SW1_GetValue()           PORTBbits.RB4
#define SW1_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define SW1_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define SW1_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define SW1_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define SW1_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define SW1_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define SW1_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define SW1_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set _LCD_RW aliases
#define _LCD_RW_TRIS                 TRISBbits.TRISB5
#define _LCD_RW_LAT                  LATBbits.LATB5
#define _LCD_RW_PORT                 PORTBbits.RB5
#define _LCD_RW_WPU                  WPUBbits.WPUB5
#define _LCD_RW_OD                   ODCONBbits.ODCB5
#define _LCD_RW_ANS                  ANSELBbits.ANSB5
#define _LCD_RW_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define _LCD_RW_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define _LCD_RW_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define _LCD_RW_GetValue()           PORTBbits.RB5
#define _LCD_RW_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define _LCD_RW_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define _LCD_RW_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define _LCD_RW_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define _LCD_RW_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define _LCD_RW_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define _LCD_RW_SetAnalogMode()      do { ANSELBbits.ANSB5 = 1; } while(0)
#define _LCD_RW_SetDigitalMode()     do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set _LCD_EN aliases
#define _LCD_EN_TRIS                 TRISCbits.TRISC0
#define _LCD_EN_LAT                  LATCbits.LATC0
#define _LCD_EN_PORT                 PORTCbits.RC0
#define _LCD_EN_WPU                  WPUCbits.WPUC0
#define _LCD_EN_OD                   ODCONCbits.ODCC0
#define _LCD_EN_ANS                  ANSELCbits.ANSC0
#define _LCD_EN_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define _LCD_EN_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define _LCD_EN_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define _LCD_EN_GetValue()           PORTCbits.RC0
#define _LCD_EN_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define _LCD_EN_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define _LCD_EN_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define _LCD_EN_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define _LCD_EN_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define _LCD_EN_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define _LCD_EN_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define _LCD_EN_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set ENC_PUL aliases
#define ENC_PUL_TRIS                 TRISCbits.TRISC2
#define ENC_PUL_LAT                  LATCbits.LATC2
#define ENC_PUL_PORT                 PORTCbits.RC2
#define ENC_PUL_WPU                  WPUCbits.WPUC2
#define ENC_PUL_OD                   ODCONCbits.ODCC2
#define ENC_PUL_ANS                  ANSELCbits.ANSC2
#define ENC_PUL_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define ENC_PUL_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define ENC_PUL_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define ENC_PUL_GetValue()           PORTCbits.RC2
#define ENC_PUL_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define ENC_PUL_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define ENC_PUL_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define ENC_PUL_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define ENC_PUL_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define ENC_PUL_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define ENC_PUL_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define ENC_PUL_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set ENC_DIR aliases
#define ENC_DIR_TRIS                 TRISCbits.TRISC3
#define ENC_DIR_LAT                  LATCbits.LATC3
#define ENC_DIR_PORT                 PORTCbits.RC3
#define ENC_DIR_WPU                  WPUCbits.WPUC3
#define ENC_DIR_OD                   ODCONCbits.ODCC3
#define ENC_DIR_ANS                  ANSELCbits.ANSC3
#define ENC_DIR_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define ENC_DIR_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define ENC_DIR_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define ENC_DIR_GetValue()           PORTCbits.RC3
#define ENC_DIR_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define ENC_DIR_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define ENC_DIR_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define ENC_DIR_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define ENC_DIR_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define ENC_DIR_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define ENC_DIR_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define ENC_DIR_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set ENC_BUT aliases
#define ENC_BUT_TRIS                 TRISCbits.TRISC4
#define ENC_BUT_LAT                  LATCbits.LATC4
#define ENC_BUT_PORT                 PORTCbits.RC4
#define ENC_BUT_WPU                  WPUCbits.WPUC4
#define ENC_BUT_OD                   ODCONCbits.ODCC4
#define ENC_BUT_ANS                  ANSELCbits.ANSC4
#define ENC_BUT_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define ENC_BUT_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define ENC_BUT_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define ENC_BUT_GetValue()           PORTCbits.RC4
#define ENC_BUT_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define ENC_BUT_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define ENC_BUT_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define ENC_BUT_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define ENC_BUT_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define ENC_BUT_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define ENC_BUT_SetAnalogMode()      do { ANSELCbits.ANSC4 = 1; } while(0)
#define ENC_BUT_SetDigitalMode()     do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set RD2 procedures
#define RD2_SetHigh()            do { LATDbits.LATD2 = 1; } while(0)
#define RD2_SetLow()             do { LATDbits.LATD2 = 0; } while(0)
#define RD2_Toggle()             do { LATDbits.LATD2 = ~LATDbits.LATD2; } while(0)
#define RD2_GetValue()              PORTDbits.RD2
#define RD2_SetDigitalInput()    do { TRISDbits.TRISD2 = 1; } while(0)
#define RD2_SetDigitalOutput()   do { TRISDbits.TRISD2 = 0; } while(0)
#define RD2_SetPullup()             do { WPUDbits.WPUD2 = 1; } while(0)
#define RD2_ResetPullup()           do { WPUDbits.WPUD2 = 0; } while(0)
#define RD2_SetAnalogMode()         do { ANSELDbits.ANSD2 = 1; } while(0)
#define RD2_SetDigitalMode()        do { ANSELDbits.ANSD2 = 0; } while(0)

// get/set _LCD_RS aliases
#define _LCD_RS_TRIS                 TRISDbits.TRISD3
#define _LCD_RS_LAT                  LATDbits.LATD3
#define _LCD_RS_PORT                 PORTDbits.RD3
#define _LCD_RS_WPU                  WPUDbits.WPUD3
#define _LCD_RS_OD                   ODCONDbits.ODCD3
#define _LCD_RS_ANS                  ANSELDbits.ANSD3
#define _LCD_RS_SetHigh()            do { LATDbits.LATD3 = 1; } while(0)
#define _LCD_RS_SetLow()             do { LATDbits.LATD3 = 0; } while(0)
#define _LCD_RS_Toggle()             do { LATDbits.LATD3 = ~LATDbits.LATD3; } while(0)
#define _LCD_RS_GetValue()           PORTDbits.RD3
#define _LCD_RS_SetDigitalInput()    do { TRISDbits.TRISD3 = 1; } while(0)
#define _LCD_RS_SetDigitalOutput()   do { TRISDbits.TRISD3 = 0; } while(0)
#define _LCD_RS_SetPullup()          do { WPUDbits.WPUD3 = 1; } while(0)
#define _LCD_RS_ResetPullup()        do { WPUDbits.WPUD3 = 0; } while(0)
#define _LCD_RS_SetPushPull()        do { ODCONDbits.ODCD3 = 0; } while(0)
#define _LCD_RS_SetOpenDrain()       do { ODCONDbits.ODCD3 = 1; } while(0)
#define _LCD_RS_SetAnalogMode()      do { ANSELDbits.ANSD3 = 1; } while(0)
#define _LCD_RS_SetDigitalMode()     do { ANSELDbits.ANSD3 = 0; } while(0)

// get/set _LCD_D4 aliases
#define _LCD_D4_TRIS                 TRISDbits.TRISD4
#define _LCD_D4_LAT                  LATDbits.LATD4
#define _LCD_D4_PORT                 PORTDbits.RD4
#define _LCD_D4_WPU                  WPUDbits.WPUD4
#define _LCD_D4_OD                   ODCONDbits.ODCD4
#define _LCD_D4_ANS                  ANSELDbits.ANSD4
#define _LCD_D4_SetHigh()            do { LATDbits.LATD4 = 1; } while(0)
#define _LCD_D4_SetLow()             do { LATDbits.LATD4 = 0; } while(0)
#define _LCD_D4_Toggle()             do { LATDbits.LATD4 = ~LATDbits.LATD4; } while(0)
#define _LCD_D4_GetValue()           PORTDbits.RD4
#define _LCD_D4_SetDigitalInput()    do { TRISDbits.TRISD4 = 1; } while(0)
#define _LCD_D4_SetDigitalOutput()   do { TRISDbits.TRISD4 = 0; } while(0)
#define _LCD_D4_SetPullup()          do { WPUDbits.WPUD4 = 1; } while(0)
#define _LCD_D4_ResetPullup()        do { WPUDbits.WPUD4 = 0; } while(0)
#define _LCD_D4_SetPushPull()        do { ODCONDbits.ODCD4 = 0; } while(0)
#define _LCD_D4_SetOpenDrain()       do { ODCONDbits.ODCD4 = 1; } while(0)
#define _LCD_D4_SetAnalogMode()      do { ANSELDbits.ANSD4 = 1; } while(0)
#define _LCD_D4_SetDigitalMode()     do { ANSELDbits.ANSD4 = 0; } while(0)

// get/set _LCD_D5 aliases
#define _LCD_D5_TRIS                 TRISDbits.TRISD5
#define _LCD_D5_LAT                  LATDbits.LATD5
#define _LCD_D5_PORT                 PORTDbits.RD5
#define _LCD_D5_WPU                  WPUDbits.WPUD5
#define _LCD_D5_OD                   ODCONDbits.ODCD5
#define _LCD_D5_ANS                  ANSELDbits.ANSD5
#define _LCD_D5_SetHigh()            do { LATDbits.LATD5 = 1; } while(0)
#define _LCD_D5_SetLow()             do { LATDbits.LATD5 = 0; } while(0)
#define _LCD_D5_Toggle()             do { LATDbits.LATD5 = ~LATDbits.LATD5; } while(0)
#define _LCD_D5_GetValue()           PORTDbits.RD5
#define _LCD_D5_SetDigitalInput()    do { TRISDbits.TRISD5 = 1; } while(0)
#define _LCD_D5_SetDigitalOutput()   do { TRISDbits.TRISD5 = 0; } while(0)
#define _LCD_D5_SetPullup()          do { WPUDbits.WPUD5 = 1; } while(0)
#define _LCD_D5_ResetPullup()        do { WPUDbits.WPUD5 = 0; } while(0)
#define _LCD_D5_SetPushPull()        do { ODCONDbits.ODCD5 = 0; } while(0)
#define _LCD_D5_SetOpenDrain()       do { ODCONDbits.ODCD5 = 1; } while(0)
#define _LCD_D5_SetAnalogMode()      do { ANSELDbits.ANSD5 = 1; } while(0)
#define _LCD_D5_SetDigitalMode()     do { ANSELDbits.ANSD5 = 0; } while(0)

// get/set _LCD_D6 aliases
#define _LCD_D6_TRIS                 TRISDbits.TRISD6
#define _LCD_D6_LAT                  LATDbits.LATD6
#define _LCD_D6_PORT                 PORTDbits.RD6
#define _LCD_D6_WPU                  WPUDbits.WPUD6
#define _LCD_D6_OD                   ODCONDbits.ODCD6
#define _LCD_D6_ANS                  ANSELDbits.ANSD6
#define _LCD_D6_SetHigh()            do { LATDbits.LATD6 = 1; } while(0)
#define _LCD_D6_SetLow()             do { LATDbits.LATD6 = 0; } while(0)
#define _LCD_D6_Toggle()             do { LATDbits.LATD6 = ~LATDbits.LATD6; } while(0)
#define _LCD_D6_GetValue()           PORTDbits.RD6
#define _LCD_D6_SetDigitalInput()    do { TRISDbits.TRISD6 = 1; } while(0)
#define _LCD_D6_SetDigitalOutput()   do { TRISDbits.TRISD6 = 0; } while(0)
#define _LCD_D6_SetPullup()          do { WPUDbits.WPUD6 = 1; } while(0)
#define _LCD_D6_ResetPullup()        do { WPUDbits.WPUD6 = 0; } while(0)
#define _LCD_D6_SetPushPull()        do { ODCONDbits.ODCD6 = 0; } while(0)
#define _LCD_D6_SetOpenDrain()       do { ODCONDbits.ODCD6 = 1; } while(0)
#define _LCD_D6_SetAnalogMode()      do { ANSELDbits.ANSD6 = 1; } while(0)
#define _LCD_D6_SetDigitalMode()     do { ANSELDbits.ANSD6 = 0; } while(0)

// get/set _LCD_D7 aliases
#define _LCD_D7_TRIS                 TRISDbits.TRISD7
#define _LCD_D7_LAT                  LATDbits.LATD7
#define _LCD_D7_PORT                 PORTDbits.RD7
#define _LCD_D7_WPU                  WPUDbits.WPUD7
#define _LCD_D7_OD                   ODCONDbits.ODCD7
#define _LCD_D7_ANS                  ANSELDbits.ANSD7
#define _LCD_D7_SetHigh()            do { LATDbits.LATD7 = 1; } while(0)
#define _LCD_D7_SetLow()             do { LATDbits.LATD7 = 0; } while(0)
#define _LCD_D7_Toggle()             do { LATDbits.LATD7 = ~LATDbits.LATD7; } while(0)
#define _LCD_D7_GetValue()           PORTDbits.RD7
#define _LCD_D7_SetDigitalInput()    do { TRISDbits.TRISD7 = 1; } while(0)
#define _LCD_D7_SetDigitalOutput()   do { TRISDbits.TRISD7 = 0; } while(0)
#define _LCD_D7_SetPullup()          do { WPUDbits.WPUD7 = 1; } while(0)
#define _LCD_D7_ResetPullup()        do { WPUDbits.WPUD7 = 0; } while(0)
#define _LCD_D7_SetPushPull()        do { ODCONDbits.ODCD7 = 0; } while(0)
#define _LCD_D7_SetOpenDrain()       do { ODCONDbits.ODCD7 = 1; } while(0)
#define _LCD_D7_SetAnalogMode()      do { ANSELDbits.ANSD7 = 1; } while(0)
#define _LCD_D7_SetDigitalMode()     do { ANSELDbits.ANSD7 = 0; } while(0)

// get/set LED_BUILTIN aliases
#define LED_BUILTIN_TRIS                 TRISEbits.TRISE0
#define LED_BUILTIN_LAT                  LATEbits.LATE0
#define LED_BUILTIN_PORT                 PORTEbits.RE0
#define LED_BUILTIN_WPU                  WPUEbits.WPUE0
#define LED_BUILTIN_OD                   ODCONEbits.ODCE0
#define LED_BUILTIN_ANS                  ANSELEbits.ANSE0
#define LED_BUILTIN_SetHigh()            do { LATEbits.LATE0 = 1; } while(0)
#define LED_BUILTIN_SetLow()             do { LATEbits.LATE0 = 0; } while(0)
#define LED_BUILTIN_Toggle()             do { LATEbits.LATE0 = ~LATEbits.LATE0; } while(0)
#define LED_BUILTIN_GetValue()           PORTEbits.RE0
#define LED_BUILTIN_SetDigitalInput()    do { TRISEbits.TRISE0 = 1; } while(0)
#define LED_BUILTIN_SetDigitalOutput()   do { TRISEbits.TRISE0 = 0; } while(0)
#define LED_BUILTIN_SetPullup()          do { WPUEbits.WPUE0 = 1; } while(0)
#define LED_BUILTIN_ResetPullup()        do { WPUEbits.WPUE0 = 0; } while(0)
#define LED_BUILTIN_SetPushPull()        do { ODCONEbits.ODCE0 = 0; } while(0)
#define LED_BUILTIN_SetOpenDrain()       do { ODCONEbits.ODCE0 = 1; } while(0)
#define LED_BUILTIN_SetAnalogMode()      do { ANSELEbits.ANSE0 = 1; } while(0)
#define LED_BUILTIN_SetDigitalMode()     do { ANSELEbits.ANSE0 = 0; } while(0)

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


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCCF2 pin functionality
 * @Example
    IOCCF2_ISR();
 */
void IOCCF2_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCCF2 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCCF2 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF2_SetInterruptHandler(MyInterruptHandler);

*/
void IOCCF2_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCCF2 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCCF2_SetInterruptHandler() method.
    This handler is called every time the IOCCF2 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF2_SetInterruptHandler(IOCCF2_InterruptHandler);

*/
extern void (*IOCCF2_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCCF2 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCCF2_SetInterruptHandler() method.
    This handler is called every time the IOCCF2 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF2_SetInterruptHandler(IOCCF2_DefaultInterruptHandler);

*/
void IOCCF2_DefaultInterruptHandler(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCCF3 pin functionality
 * @Example
    IOCCF3_ISR();
 */
void IOCCF3_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCCF3 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCCF3 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF3_SetInterruptHandler(MyInterruptHandler);

*/
void IOCCF3_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCCF3 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCCF3_SetInterruptHandler() method.
    This handler is called every time the IOCCF3 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF3_SetInterruptHandler(IOCCF3_InterruptHandler);

*/
extern void (*IOCCF3_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCCF3 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCCF3_SetInterruptHandler() method.
    This handler is called every time the IOCCF3 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF3_SetInterruptHandler(IOCCF3_DefaultInterruptHandler);

*/
void IOCCF3_DefaultInterruptHandler(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/