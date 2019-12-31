/*
    MIDI Debugger
    Version 1.0
    CC BY-NC-ND 4.0
    module:      main.c

    (C)2019 Bernardo Giovanni (CyB3rn0id)
    http://www.settorezero.com


    This work is distributed under CC BY-NC-ND 4.0
    Please read license before use:
    https://creativecommons.org/licenses/by-nc-nd/4.0/
    
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

// disable some warning messages
#pragma warning disable 520 // function not used
#pragma warning disable 1510
#pragma warning disable 1498

#include "mcc_generated_files/mcc.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "midi.h"

#define MAX_MIDI_BUFFER   16
uint8_t midi_buffer[MAX_MIDI_BUFFER]; // RX buffer
bool midi_msg_ready=false; // message ready to be parsed

// Timer0 interrupt every 1mS
void MyInterrupt_Timer0(void)
    {
    static uint16_t timerLed=0;
    if (++timerLed >= 1000U)
        {
        //LED0_Toggle();
        timerLed=0;
        }
    }   

// EUSART1 custom interrupt on receive
// RX connected on RB5 @ 31250bps for MIDI receive
void MyInterrupt_MIDI_Rx(void)
    {
    static uint8_t rxbuf=0; // temporary RX buffer
    static uint8_t rxcnt=0; // RX data count
    static bool _sysmsg=false; // system message flag
    
    // resetting overrun error if any
    if (RC1STAbits.OERR) 
        {
        RC1STAbits.CREN=0;
        RC1STAbits.CREN=1;
        }
    
    // reading from UART buffer
	rxbuf=RC1REG;
    
    // it's a system message
    if (rxbuf==SYSMSG) 
        {
        _sysmsg=true;
        rxcnt=0;
        return;
        }
    
    // end of system message
    if (_sysmsg && rxbuf==EOX) 
        {
        midi_msg_ready=true;
        midi_buffer[rxcnt+1U]='\0';
        _sysmsg=false;
        return;
        }
            
    // not end of system message : receiving data
    if (_sysmsg)
        {
        // reached the buffer amount: exit
        if (rxcnt==MAX_MIDI_BUFFER-1)
            {
            midi_msg_ready=true;
            midi_buffer[rxcnt+1U]='\0';
            _sysmsg=false;
            return;
            }
        rxcnt++;
        midi_buffer[rxcnt]=rxbuf;
        return;
        }
            
    // If bit 7 is 1, it's a message header (status byte))
    if (rxbuf & 0x80)
        {
        midi_msg_ready=false; // we're still receiving
        rxcnt=0; // counter must start from 0
        midi_buffer[0]=rxbuf; // first data in the buffer
        }
    else // it's a data byte
        {
        rxcnt++;
        midi_buffer[rxcnt]=rxbuf;
        // it's the second data byte?
        if (rxcnt==2)
            {
            midi_msg_ready=true;
            }
        else
            {
            // It's a program change or a channel pressure message?
            // Those has only 1 data byte after the status
            // So in this case there is no second data byte!
            if (((midi_buffer[0]>>4) == CHANPRESS) || ((midi_buffer[0]>>4) == PC))
                {
                midi_buffer[2]=0;
                midi_msg_ready=true;
                } // PC or Channel pressure
            } // not second data byte
        } // It's a data byte
}

// debug midi message on EUSART2 connected to USB CDC
void MIDI_print_status(uint8_t header, uint8_t data1, uint8_t data2)
    {
    uint8_t type=(uint8_t)(header>>4); // Message Type
    uint8_t channel=(uint8_t)(header & 0x0F)+1U; // Message Channel, 1-based
    
    // print message type
    switch(type)
        {
        case NOTEOFF:
            printf("Note OFF\r");
        break;
                    
        case NOTEON:
            printf("Note ON\r");
        break;
                    
        case POLYPRESS:
            printf("Polyphonic Pressure\r");
        break;
                    
        case CC:
            printf("Control Change\r");
        break;
                    
        case PC:
            printf("Program Change\r");
        break;
                    
        case CHANPRESS:
            printf("Channel Pressure\r");
        break;
                    
        case PITCHBEND:
            printf("Pitch Bend\r");
        break;

        default:
            printf("UNKNOWN\r");
        break;
        }
    
    // print channel
    printf ("Channel: ");
    printf ("%d\r",channel);
    
    // it's a pitchbend
    if (type==PITCHBEND)
        {
        volatile int16_t bend=0;
        // byte2 need to be shifted by 7 positions, not 8, since bit 7 is
        // always zero in order to identify data bytes
        bend=((data2<<7)|(data1))-8192;
        printf("Bend value: %d\r", bend);
        }
    else // Is not a Pitchbend message, so data bytes are separated
        {
        // For Note ON, Note OFF and Polyphonic Pressure messages
		// I write the Note and the Octave
        if (type==NOTEON || type==NOTEOFF || type==POLYPRESS)
            {
            printf("Note: ");
            octave=data1/12;
            notepos=(uint8_t)(data1-(octave*12)); // Note position from 0 to 11
            // In the notename array the black keys are written in lower-case
			// so here I transform them in uppercase and I add the diesis symbol
            if (notename[notepos] > 'G') // it's a lowercase letter (see ascii chart)
                {
                printf("%c",(uint8_t)(notename[notepos]-32)); // Upper-case transform
                printf("#"); // diesis
                }
            else
                {
                printf("%c",notename[notepos]);
                }
            printf("%d\r",(uint8_t)octave); // note octave position
            // octave number from midi standard: C0 is in octave -1
			printf("Octave: ");
            octave-=1;
            printf("%d\r",octave);
            }
        else // not a note
            {
			printf("Data 1: ");
            printf("%d\r", data1);
            }
               
        // Second data byte
        // Program Change and Channel Pressure has only 1 data byte
        // Pitch Bend has 2 but I treated them as one, so I must esclude
        // this 3 messages types from this elaboration
        if ((type != PC) && (type!=CHANPRESS) && (type != PITCHBEND))
            {
			// If message is Note On or Note Off, second data byte is velocity
            if (type==NOTEON || type==NOTEOFF)
                {
                printf("Velocity: ");
                if (data2==0)
                    {
                    printf("0 (same as Note OFF)\r");
                    }
                else // Velocity is not zero
                    {
                    printf("%d\r",data2);
                    }
                } 
            else // This is a Polyphonic Pressure or a Control Change message
                {
                printf("Data 2: %d\r",data2);
                }
            }
        else // There is no second data byte
            {
            
            }
        } // Is not a pitchbend
    printf("\r");
	} // print midi message

void main(void)
	{
    // initialize the device
    SYSTEM_Initialize();
    TMR0_SetInterruptHandler(*MyInterrupt_Timer0);
    EUSART1_SetRxInterruptHandler(*MyInterrupt_MIDI_Rx);
    
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    while (1)
        {
        if (midi_msg_ready)
            {
            LED0_SetLow();
            if (midi_buffer[0]==SYSMSG)
                {
                printf("System message\r");
                }
            else
                {
                MIDI_print_status(midi_buffer[0], midi_buffer[1], midi_buffer[2]);
                }
            midi_msg_ready=false; // I've parsed the message
            LED0_SetHigh();
            } // message ready
        }
	}
