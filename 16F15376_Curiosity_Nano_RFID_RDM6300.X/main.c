/*
 * Demo PIC16F15376 Curiosity Nano + RDM6300 RFID reader
 * Output on LCD 16x2
 * This is a demo: no checksum checked, no valid tag checked. Only reading
 * 
 * (c)2020 Bernardo Giovanni
 * https://www.settorezero.com
 * 
 */

/* Connections:
 * RD3  : LCD RS
 * RC0  : LCD EN
 * RB5  : LCD RW
 * RD4  : LCD D4
 * RD5  : LCD D5
 * RD6  : LCD D6
 * RD7  : LCD D7
 * RA0  : BUZZER (through a mosfet)
 * RE0  : LED0 on board
 * RE2  : SW0 on board
 * RC7  : EUSART1 RX (to module TX)
 * 
 */

#include "mcc_generated_files/mcc.h"
#include "hd44780sz.h"
#pragma warning disable 520 // suppress "function not used" warnings


uint8_t receive_status=0;
#define RECSTA_IDLE 0 // uart ready
#define RECSTA_BUSY 1 // uart is receiving
#define RECSTA_END 2  // tag received
#define MAX_TAG_LEN	12 // tag max bytes (without blank chars)
char rx_buffer[MAX_TAG_LEN];

// called on RCIF
void RFID_rx(void)
    {
    char rx_byte=RC1REG; // received byte
    if (receive_status==RECSTA_END) return; // exit if not in receive mode
    static uint8_t buffer_pointer=0; // rx buffer pointer
    
    // overrun error
    if(RC1STAbits.OERR)
        {
        // restart usart
        RC1STAbits.CREN = 0;
        RC1STAbits.CREN = 1;
        }
	
    // received byte value
	switch (rx_byte)
		{
		case 0x02: // STX - start transmission
            LED0_SetLow(); // turn on the led
			buffer_pointer=0; // pointer reset
			receive_status=RECSTA_BUSY; // I'm busy
			break;
			
		case 0x03: // ETX - end transmission
            LED0_SetHigh(); // turn off the led
            // if we're in receive mode
            if (receive_status==RECSTA_BUSY)
                {
                rx_buffer[buffer_pointer]='\0'; // close the buffer
                receive_status=RECSTA_END; // receive end
                }
            break;
			
        // do nothing for those chars
        case 0x00: // null
        case 0x0D: // <CR>
		case 0x0A: // <LF>
			break;
			
		default: // any byte other than previous ones => store
			if (receive_status==RECSTA_BUSY)
                {
                rx_buffer[buffer_pointer++]=rx_byte;
                }
            break;
		}
		
		// received bytes are too much
		if (buffer_pointer>MAX_TAG_LEN)
            {
			buffer_pointer=0; // pointer reset
            receive_status=RECSTA_IDLE;
			}
    }


void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // set the interrupt handler for uart receive
    EUSART1_SetRxInterruptHandler(*RFID_rx);

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
    
    LCDInit();
    LCDGoto(1,1);
    LCDPuts("RFID Reader");
    LCDGoto(2,1);
    LCDPuts("BernardoGiovanni");

    while (1)
        {
        // receive complete
        if (receive_status==RECSTA_END)
            {
            BUZZER_SetHigh();
            LCDGoto(2,1);
            uint8_t i=0;
            while(rx_buffer[i])
                {
                // remembder: last two chars are the checksum!
                LCDPutch(rx_buffer[i++]);
                }
            LCDPuts("    ");
            __delay_ms(100);
            BUZZER_SetLow();
            // wait 2 seconds
            uint8_t q=20;
            while (q--)
                {
                __delay_ms(100);
                }
            LCDGoto(2,1);
            LCDPuts("                "); // delete disply row
            receive_status=RECSTA_IDLE; // ready to receive again
            }
        }
}