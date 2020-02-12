/*
 * Square Wave Generator (0-16MHz with 1Hz steps)
 *
 * This was intended as an example on how to use NCO module on PIC MCUs
 * I used a PIC16F15376 Curiosity Nano board from Microchip
 *
 * (C)2020 Giovanni Bernardo (CyB3rn0id)
 * blog: https://www.settorezero.com
 * twitter: https://www.twitter.com/settorezero
 * 
 * LICENSE
 * This work is distributed under a CC BY-NC-SA 4.0
 * Attribution-NonCommercial-ShareAlike 4.0 International 
 * You are free to:
 * Share - copy and redistribute the material in any medium or format
 * Adapt - remix, transform, and build upon the material
 * Under the following terms:
 * Attribution - You must give appropriate credit, provide a link to 
 * the license, and indicate if changes were made. You may do so in any 
 * reasonable manner, but not in any way that suggests the licensor 
 * endorses you or your use.
 * NonCommercial - You may not use the material for commercial purposes.
 * ShareAlike - If you remix, transform, or build upon the material, 
 * you must distribute your contributions under the same license as the original.
 * 
 * 
 * THIS SOFTWARE IS SUPPLIED "AS IS". NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
 * IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
 * FOR A PARTICULAR PURPOSE.
 *   
 * IN NO EVENT WILL AUTHOR BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
 * HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
 * THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
 * CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
 * OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
 * SOFTWARE.
 */

#include "mcc_generated_files/mcc.h"
#include "hd44780sz.h"
#pragma warning disable 520 // suppress "function not used" warnings

// Variables used for encoder
#define ENCTIMERESTART  4 // ms antibounce for encoder
#define CCOUNT 3 // number of equal ticks for giving ok
uint8_t cpVar=0; // number of consecutive equal ticks for increment
uint8_t cnVar=0; // number of consecutiv equal ticks for decrement
bool EncoderState=false; // true if pulse and dir are at same level
bool EncAntibounce=false; // antibounce in progress = interrupt disabled

// variables used for NCO module
#define OSCMF   1 // NCO clock is 31250Hz
#define OSCFO   2 // NCO clock is FOSC (actually 32MHz)
#define MODEFDC	1 // NCO mode is Fixed Duty Cycle
#define MODEPUL	2 // NCO mode is Pulse
uint32_t NCOval=0; // value that will be loaded in NCO increment registers
uint32_t NCOfre=1000; // choosen frequency in Hertz
uint32_t preNCOfre=1000; // previous frequency
uint32_t NCOmaxfreq=15000; // maximum allowable frequency (will vary depending selected clock)
uint8_t NCOosc=OSCMF; // From which oscillator NCO is running? (start with 31250Hz)
uint8_t preNCOosc=OSCMF; // previous clock source 
uint8_t NCOmode=MODEFDC; // NCO mode
uint8_t preNCOmode=MODEFDC; // previous NCO mode
uint32_t increment=1; // Hz increment per encoder step
uint8_t encPush=0; // number of consecutive encoder button pushes

// function prototypes
void checkEncoderButton(void);
void checkSW0Button(void);
void Encoder_Pulse_ISR(void);
void Encoder_Dir_ISR(void);
void Timer0_ISR(void);
uint32_t NCOcalcinc(uint32_t fr);
void setNCOincrement(uint32_t val);
void displayOutput(void);
void displayDefault(void);
void checkNCOchanges(void);

void main(void)
    {
    // initialize the device
    SYSTEM_Initialize();
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();
    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
    // start encoder with current state
    if (ENC_PUL_PORT==ENC_DIR_PORT) EncoderState=true;
    // set interrupt handlers for MCC generated functions
    IOCCF2_SetInterruptHandler(*Encoder_Pulse_ISR);
    IOCCF3_SetInterruptHandler(*Encoder_Dir_ISR);
    TMR0_SetInterruptHandler(*Timer0_ISR);
    
    NCOval=NCOcalcinc(NCOfre);
    setNCOincrement(NCOval);

    // LCD initialization
	LCDInit();
    displayDefault();
	
    while (1)
        {
		checkNCOchanges();
		displayOutput();
        checkEncoderButton();
		checkSW0Button();
        }
	} // \main

// check for NCO changes (mode, frequency, clock source)
void checkNCOchanges(void)
	{
	// changed NCO mode - not used in this revision
	if (NCOmode!=preNCOmode)
		{
		preNCOmode=NCOmode;
		}
	
	// changed NCO source clock
    if (NCOosc!=preNCOosc)
		{
		if (NCOosc==OSCMF)
			{
			NCO1CLK=0x04; //MFINTOSC 32KHz
			}
		else if (NCOosc==OSCFO)
			{
			NCO1CLK=0x00; // FOSC (32MHz)
			}
			// I don't update variable preNCOosc since now values for NCO INC registers
			// must be re-calculated since NCO clock source was changed
			// and the next routine will do this
			// reset increment to 1Hz
			encPush=0;
			increment=1;
            // changing from a clock source to another can happens that last
            // selected frequency is higher than that current clock source can reach
            if (NCOfre>NCOmaxfreq) NCOfre=NCOmaxfreq;
		}

	// changed frequency and/or clock source: recalculate NCO increment value
	if ((NCOfre!=preNCOfre) || (NCOosc!=preNCOosc))
		{
		NCOval=NCOcalcinc(NCOfre);
		setNCOincrement(NCOval);
		// set previous values
		preNCOfre=NCOfre;
		if (NCOosc!=preNCOosc)
			{
			displayDefault();
			preNCOosc=NCOosc;
			}
		}
	}
	
// Print display default values
void displayDefault(void)
	{
	LCDClear();
	LCDGoto(1,1);
    LCDPuts("Freq:");
    LCDGoto(2,1);
    LCDPuts("Step:");
	displayOutput();
	}

// Print values on display
void displayOutput(void)
	{
	// Print frequency
    LCDGoto(1,6);
    LCDPutun24(NCOfre);
    LCDPuts("Hz ");
    
    // Print Step per encoder tick
    LCDGoto(2,6);
	if (increment<1000)
		{
		LCDPutun(increment);
		LCDPuts("Hz");
		}
	else if (increment==1000000)
		{
		LCDPuts("1MHz");
		}
	else // >=1000 and <1000000
		{
		LCDPutun(increment/1000);
		LCDPuts("KHz");
		}
	LCDPuts("   ");
	
	// Print NCO Clock Source
	LCDGoto(2,15);
	if (NCOosc==OSCMF)
        {
        LCDPuts("MF");
        }
    else if (NCOosc==OSCFO)
        {
        LCDPuts("FO");
        }	
	}

// Encoder button pushed: change clock source for NCO
void checkEncoderButton(void)
	{
    if (!ENC_BUT_GetValue())
		{
        __delay_ms(80); // antibounce
        if (!ENC_BUT_GetValue())
           {
           NCOosc++;
           if(NCOosc>OSCFO)
				{
                NCOosc=1;
                }
			// stuck until button released
			while (!ENC_BUT_GetValue()) {continue;}
           }
        }
	}
	
// SW0 pushed : change Hz per encoder tick
void checkSW0Button(void)
	{
	if (!SW0_GetValue())
		{
        __delay_ms(80); // antibounce
        if (!SW0_GetValue())
			{
            encPush++;
            if (NCOosc==OSCFO)
				{
				if (encPush>6) encPush=0;
				}
			else
				{
				if(encPush>3) encPush=0;
				}
            switch (encPush)
				{
                case 0:
                increment=1;
                break;
                        
                case 1:
                increment=10;
                break;
                        
                case 2:
                increment=100;
                break;
                        
                case 3:
                increment=1000;
                break;
				
				case 4:
				increment=10000;
				break;
				
				case 5:
				increment=100000;
				break;
				
				case 6:
				increment=1000000;
				break;
                }
			// stuck until button released
			while (!SW0_GetValue()) {continue;}
			}
		}
	}

// calculate value to be loaded in NCO INC registers
// based on passed frequency and actual oscillator used
// this function will also set the global variable NCOmaxfreq
/*
 * Calculations explained:
 
 * in FDC mode overflow frequency must be divided by 2
 * in order to obtain square wave frequency
 * So the formula is: 
 * freq=((nco_osc_freq*inc_register)/(2^20))/2 =>
 * freq=((nco_osc_freq*inc_register)/(2^21)) =>
 * freq=(nco_osc_freq*inc_register)/2097152 =>
 * inc_register=freq*(2097152/nco_osc_freq) =>

 * using MFINTOSC at 31250Hz we have:
 * inc_register=freq*67,108864
 * Maximum frequency value=((31250*((2^20)-1)/(2^20))/2
 * = (31250*1048575/1048576)/2=15624Hz
 
 * using FOSC at 32000000Hz we have:
 * inc_register=freq*0,065536
 * Maximum frequency value=((32000000*((2^20)-1)/(2^20))/2
 * = (32000000*1048575/1048576)/2=15999984Hz
 */
uint32_t NCOcalcinc(uint32_t fr)
    {
    float in=0;
    if (NCOosc==OSCMF)
        {
        in=fr*67.109;
        NCOmaxfreq=15624UL;
        }
    else if (NCOosc==OSCFO)
        {
        in=fr*0.065536;
        NCOmaxfreq=15999984UL;
        }
	// in Pulse mode we must not use the division by 2
    if (NCOmode==MODEPUL)
        {
        in*=2;
        }
    return (uint32_t)in;
    }

// NCO module will produce a frequency based on value given
// to INCrement registers. Value is 20 bits, divided in 3
// registers: NCO1 INCrement (Low, High and Upper)
// datasheet says to fill first the upper, than the high 
// and low at the end: when you fill the low register, 
// new frequency will be generated
void setNCOincrement(uint32_t val)
    {
    NCO1INCU=(uint8_t)(val>>16);
	NCO1INCH=(uint8_t)(val>>8);
	NCO1INCL=(uint8_t)val;
    }

/******************************************************************************
INTERRUPTS
 Interrupt on change for:
 RC2 (any)
 RC3 (any)
 in pin_manager (inizialize) are activated interrupts for port Cx:
 IOCCNx (active for negative edge on port Cx)
 IOCCPx (active for positive edge on port Cx)
 or both IOCCN and IOCCP for any change
 then you check IOCCF for each port (interrupt flag)
******************************************************************************/	

// Interrupt on Encoder PULSE pin
void Encoder_Pulse_ISR(void)
    {
    if (EncAntibounce) return; // still in antibounce routine
    // disable interrupts on encoder pulse/dir
	// will be re-enabled in Timer0 interrupt
    IOCCNbits.IOCCN2 = 0;
    IOCCPbits.IOCCP2 = 0;
    IOCCNbits.IOCCN3 = 0;
    IOCCPbits.IOCCP3 = 0;
    // encoder turned clockwise (Pulse interrupt)
	if (ENC_PUL_PORT==ENC_DIR_PORT) 
		{
        cnVar=0;
        if (false==EncoderState)
            {
            cpVar++;
            if (cpVar==CCOUNT)
                {
                NCOfre+=increment;
                if (NCOfre>NCOmaxfreq) NCOfre=NCOmaxfreq;
                cpVar=0;
                }
            }
		EncoderState=true; 
		}
  else // encoder turned counterclockwise
		{
        cpVar=0;
        if (EncoderState) 
			{
            cnVar++;
            if (cnVar==CCOUNT)
                {
                if (NCOfre>increment)
                    {
                    NCOfre-=increment;
                    }
                else
                    {
                    NCOfre=increment;
                    }
                cnVar=0;
                }
			}
		EncoderState=false;   
		}
	EncAntibounce=true; // start antibounce routine
	}

// interrupt on encoder DIR pin
void Encoder_Dir_ISR(void)
	{
    if (EncAntibounce) return; // still in antibounce routine
    // disable interrupts on encoder pulse/dir 
	// will be re-enabled in Timer0 interrupt
	IOCCNbits.IOCCN2 = 0;
    IOCCPbits.IOCCP2 = 0;
    IOCCNbits.IOCCN3 = 0;
    IOCCPbits.IOCCP3 = 0;
    // encoder turned counterclockwise (Direction interrupt)
	if (ENC_PUL_PORT==ENC_DIR_PORT) 
		{
        cpVar=0;
        if (false==EncoderState)
            {
            cnVar++;
            if (cnVar==CCOUNT)
                {
                if (NCOfre>increment)
                    {
                    NCOfre-=increment;
                    }
                else
                    {
                    NCOfre=increment;
                    }
                cnVar=0;
                }
			}
		EncoderState=true;      
		}
  else // encoder turned clockwise
		{
        cnVar=0;
        if (EncoderState) 
			{
			cpVar++;
            if (cpVar==CCOUNT)
                {
                NCOfre+=increment;
                if (NCOfre>NCOmaxfreq) NCOfre=NCOmaxfreq;
                cpVar=0;
                }
			}
		EncoderState=false;   
      
		}
	EncAntibounce=true; // start antibounce routine
	}
	
// interrupt on Timer0 (every 1mS)
void Timer0_ISR(void)
    {
    static uint8_t EncTimer=0;
    if (EncAntibounce) // we're in antibounce routine
        {
        EncTimer++; // count antibounce time
        if (EncTimer>=ENCTIMERESTART) // end of antibounce routine
            {
            EncTimer=0;
            EncAntibounce=false;
			// re-enable interrupt on encoder pins
            IOCCNbits.IOCCN2 = 1;
            IOCCPbits.IOCCP2 = 1;
            IOCCNbits.IOCCN3 = 1;
            IOCCPbits.IOCCP3 = 1;
            }
        }
    }
