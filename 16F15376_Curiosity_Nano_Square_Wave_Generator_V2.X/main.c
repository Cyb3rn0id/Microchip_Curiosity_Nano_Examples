/*
 * Square Wave Generator V2 (0-16MHz with 1Hz steps)
 *
 * This was intended as an example on how to use NCO module on PIC MCUs
 * I used a PIC16F15376 Curiosity Nano board from Microchip
 *
 * (C)2024 Giovanni Bernardo (CyB3rn0id)
 * blog: https://www.settorezero.com
 * twitter: https://www.twitter.com/settorezero
 * 
 * LICENSE
 * This work is distributed under a CC BY-NC-SA 4.0
 * Attribution-NonCommercial-ShareAlike 4.0 International 
 * You are free to:
 * Share & copy and redistribute the material in any medium or format
 * Adapt & remix, transform, and build upon the material
 * Under the following terms:
 * Attribution : You must give appropriate credit, provide a link to 
 * the license, and indicate if changes were made. You may do so in any 
 * reasonable manner, but not in any way that suggests the licensor 
 * endorses you or your use.
 * NonCommercial : You may not use the material for commercial purposes.
 * ShareAlike : If you remix, transform, or build upon the material, 
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

/*
 * Here I report some findings
 * 
 * ADC MODULE
 * MCC will NOT do everything for making ADC module working! Dunno if it's a bug or not...
 * from MCC go in System Module and make those following adjustements:
 * (1) if you want to use the FVR=>
 * you must turn on this in the PMD0 register, FVRMD bit (turn to ENABLE(
 * (2) Enable the ADC module in the PMD=>
 * register PMD2, bit ADCMD (turn to enable)
 * 
 * MAXIMUM FREQUENCIES
 * The minimun frequency I achieved is 0.015Hz (measured on oscilloscope) using the LFINTOSC
 * as clock source, FDC mode, and value 1 loaded in the increment register.
 * The maximum frequency achieved (always measured on oscilloscope)
 * is always FOSC/2 in both modes. And this is strange!
 * It's possible to load the maximum value of 1048575 when using
 * low frequencies clock sources (LFINTOSC, MFINTOSC 500 or 31kHz):
 * output on pin will be what you expect: for example with MFINTOSC at 500kHz
 * and 1048575 loaded, you'll obtain 250kHz in FDC and 500kHz in PF.
 * 
 * Problems happens using FOSC or HFINTOSC. For example using 32MHz
 * If I load the value 1048575, FDC mode, i obtain 16MHz (even if the
 * square wave looks very weird!), but in PF mode oscilloscope can't detect
 * any form of wave. In PF mode I have a maximum of 16MHz loading 1048575/2.
 * It's not a problem of 32MHz: this happens even if I set 16MHz or 1MHz as FOSC:
 * maximum I can achieve in always fosc/2 in both modes!
 * This is weird since using MCC ad setting FOSC 32MHz, PF, it shows that 32MHz
 * can be reached! Probably it can be reached only internally but not as pin output,
 * anyway I remember that this weird behaviour happens also if I set the clock at 1MHz
 * even if I use the external crystal.
 */


#include "mcc_generated_files/mcc.h"
#include "hd44780sz.h"
#pragma warning disable 520 // suppress "function not used" warnings

// clock sources for the NCO module
typedef enum
   {
   ncoclk_fosc = 0,        // 32MHz
   ncoclk_hfintosc = 1,    // 32MHz
   ncoclk_lfintosc = 2,    // 31000 Hz
   ncoclk_mfintosc500 = 3, // 500kHz
   ncoclk_mfintosc31 = 4   // 31250 Hz
   } NCO_clock;

typedef enum
   {
   ncomode_fixed_duty=0,
   ncomode_pulse_frequency=1
   } NCO_mode;
   
// Variables used by the encoder
#define ENCTIMERESTART  4 // ms antibounce for encoder
#define CCOUNT 2 // number of equal ticks for giving ok
uint8_t cpVar=0; // number of consecutive equal ticks for step_increment
uint8_t cnVar=0; // number of consecutive equal ticks for decrement
bool EncoderState=false; // true if pulse and dir are at same level
bool EncAntibounce=false; // antibounce in progress = interrupt disabled
uint8_t encPush=0; // number of consecutive encoder button pushes (for setting steps)

// variables used by the NCO module
#define NCOFDC	0 // NCO mode is Fixed Duty Cycle (up to 16Mhz, fixed 50% Duty) - default
#define NCOPFM	1 // NCO mode is Pulse Frequency mode (up to 32MHz, variable Duty in 8 steps)

uint32_t  NCO_IncReg=0; // value that will be loaded in NCO increment registers
uint32_t  Frequency=1000; // user-choosen frequency in Hertz
uint32_t  preFrequency=1000; // previous frequency
uint32_t  MaxFrequency=15625; // maximum allowable frequency (will vary depending selected clock)
uint32_t  MinFrequency=1; // minumum allowable frequency
NCO_clock NCOclock=ncoclk_mfintosc31; // NCO clock source (start with 31250Hz)
NCO_clock preNCOclock=ncoclk_mfintosc31; // previous clock source
NCO_mode  NCOmode=ncomode_fixed_duty; // NCO actual mode
NCO_mode  preNCOmode=ncomode_fixed_duty; // NCO previous mode
uint8_t   NCOPulseDuty=0; // Duty cycle in pulse mode (from 0 to 7)
uint8_t   preNCOPulseDuty=0; // Previous Duty cycle in pulse mode (from 0 to 7)
uint32_t  step_increment=1; // Hz increment per encoder step
uint32_t  perioduty[7]={31,62,125,500,1000,2000,4000}; // Ton in nS depending on NCOPulseDuty value

// function prototypes
void checkEncoderButton(void);
void checkSW0Button(void);
void checkSW1Button(void);
void checkPotentiometer(void);
void Encoder_Pulse_ISR(void);
void Encoder_Dir_ISR(void);
void Timer0_ISR(void);
void displayOutput(void);
void displayDefault(void);
void checkNCOchanges(void);
void setNCOincreg(uint32_t val);
void setNCOPulseDuty(uint8_t val);
void setNCOmode(NCO_mode val);
void setNCOclock(NCO_clock cl);
uint32_t NCOIncFromFreq(uint32_t fr); // calculate value to assign to NCO INC registers from frequency in Hz


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
    
    // LCD initialization
	LCDInit();
    displayDefault();
        
    while (1)
        {
        checkNCOchanges();      // check for changes in NCO settings (mode, clock, frequency) and do it
		displayOutput();        // update LCD
        checkEncoderButton();   // check encoder button if pushed (change frequency step)
		checkSW0Button();       // check SW0 button if pushed (change NCO clock source) - builtin button on Nano Board
        checkSW1Button();       // check SW1 button if pushed (change NCO modality)
        checkPotentiometer();   // read potentiometer if in Pulse Frequency mode for changing duty cycle
        }
	} // \main

// check for NCO changes from user (mode, frequency, clock source) and do it
void checkNCOchanges(void)
	{
    // NCO source clock is changed
    if (NCOclock!=preNCOclock)
		{
		if (NCOclock==ncoclk_mfintosc31)
			{
			setNCOclock(ncoclk_mfintosc31); // MFINTOSC (31250Hz)
            if (encPush>3)
                {
                encPush=3;
                step_increment=1000;
                }
			}
		else if (NCOclock==ncoclk_hfintosc)
			{
			setNCOclock(ncoclk_hfintosc); // FOSC (32MHz)
			}
			// I don't update variable preNCO_clocksource since now values for NCO INC registers
			// must be re-calculated since NCO clock source was changed
			// and the next routine will do this
		}

    // changing from a clock source to another can happens that last
    // selected frequency is higher than that current clock source can reach
    if (Frequency>MaxFrequency) Frequency=MaxFrequency;
    if (Frequency<MinFrequency) Frequency=MinFrequency;
    
	// frequency and/or clock source are changed: recalculate NCO step_increment value
	if ((Frequency!=preFrequency) || (NCOclock!=preNCOclock) || (NCOmode != preNCOmode))
		{
		NCO_IncReg=NCOIncFromFreq(Frequency);
		setNCOincreg(NCO_IncReg);
        // when passing from a number having 7 digits
        // to a number having 5 or less digits, some
        // crap remains on the first row
        if ((preFrequency>999999) && (Frequency<100000))
            {
            displayDefault();
            }
		// set previous values
		preFrequency=Frequency;
		if (NCOclock!=preNCOclock)
			{
			displayDefault();
			preNCOclock=NCOclock;
			}
		}
    
    // NCO mode is changed (FDC/PFM)
    if (NCOmode != preNCOmode)
        {
        preNCOmode=NCOmode;
        setNCOmode(NCOmode);
        }
    
    // Pulse duty in PFM mode is changed
    if (NCOPulseDuty != preNCOPulseDuty)
        {
        preNCOPulseDuty=NCOPulseDuty;
        setNCOPulseDuty(NCOPulseDuty);
        }
    
	}
	
// check potentiometer if in Pulse Frequency mode, for setting the duty cycle
void checkPotentiometer(void)
    {
    if (NCOmode==ncomode_fixed_duty) return; // exit if no in Pulse mode
    uint16_t r = ADC_GetConversion(channel_ANA0); // read potentiometer from AN0/RA0
    // report 0-1023 from ADC to 0-7 for the NCO1CLK N1PWS bits
    NCOPulseDuty = r>>7;
    // check if the value obtained is suitable for the actual frequency:
    // HIGH state will last for (period of clock cycle * 2^Pulse duty value)
    // LOW state will last for (period of desidered frequency) - previous value
    // so for 32MHz we have:
    // NCOPulseDuty         Time on (TON)
    //      0               1 cycle  = 31.25nS
    //      1               2 cycles = 62.5ns
    //      2               4 cycles = 125nS
    //      3               8 cycles = 250nS
    //      4              16 cycles = 500nS
    //      5              32 cycles = 1000nS
    //      6              64 cycles = 2000nS
    //      8             128 cycles = 4000nS
    // so TON+TOFF = period (of actually choosen frequency)
    // TOFF = period-TON => this implies TON<period
    // so we must calculate conditions where:
    // TON < (1/Frequency)
    uint32_t period = (1/(Frequency/1000000))*1000; // actual period in nS
    uint8_t i=0;
    // scan for searching max allowable duty (TON) for this frequency
    while (i<8)
        {
        if (perioduty[i]>period) break; // last good value was i-1 if i>0
        i++;
        }
    // if the actual value is greater than the maximum allowable
    // report it to the maximum allowable
    if (i>0) i--;
    if (NCOPulseDuty>(i)) NCOPulseDuty=i; 
    }

// Print display default values
void displayDefault(void)
	{
	LCDClear();
	LCDGoto(1,1);
    LCDPuts("Fr:");
    LCDGoto(2,1);
    LCDPuts("St:");
	displayOutput();
	}

// Print values on display
void displayOutput(void)
	{
	// First Row
    // Fr:32000000Hz HI
    
    // Print frequency
    LCDGoto(1,4);
    LCDPutun24(Frequency);
    LCDPuts("Hz ");
    
    // Print NCO Clock Source
	LCDGoto(1,15);
	if (NCOclock==ncoclk_mfintosc31)
        {
        LCDPuts("LO");
        }
    else if (NCOclock==ncoclk_hfintosc)
        {
        LCDPuts("HI");
        }	
    
    // Second row
    // St:100kHz    f   
    // Print Step per encoder tick
    LCDGoto(2,4);
	if (step_increment<1000)
		{
		LCDPutun((uint16_t)step_increment);
		LCDPuts("Hz");
		}
	else if (step_increment==1000000)
		{
		LCDPuts("1MHz");
		}
	else // >=1000 and <1000000
		{
		LCDPutun((uint16_t)(step_increment/1000));
		LCDPuts("KHz");
		}
	LCDPuts("   ");
	
	// Print NCO mode
    LCDGoto(2,15);
	if (NCOmode==ncomode_fixed_duty)
        {
        LCDPuts("FD");
        }
    else if (NCOmode==ncomode_pulse_frequency)
        {
        LCDPuts("PF");
        }	

    // Print Duty Cycle value if in Pulse Mode
    LCDGoto(2,13);
    if (NCOmode==ncomode_fixed_duty) // no duty
        {
        LCDPuts(" ");
        }
    else
        {
        LCDPutun(NCOPulseDuty);
        }
	}

// Encoder button pushed: change frequency step per rotation
void checkEncoderButton(void)
	{
    if (!ENC_BUT_GetValue())
		{
        __delay_ms(80); // antibounce
        if (!ENC_BUT_GetValue())
           {
            encPush++;
            if ((NCOclock==ncoclk_hfintosc) || (NCOclock==ncoclk_fosc))
				{
				if (encPush>6) encPush=0;
				}
			else
				{
				if(encPush>3) encPush=0;
				}
            uint8_t i=encPush;
            step_increment=1;
            while (i--)
                {
                // 1 push=>step=10, 2 push=>step=100 and so on
                step_increment*=10;
                }
			// stuck until button released
			while (!ENC_BUT_GetValue()) {continue;}
           }
        }
	}
	
// SW0 pushed : change NCO clock source
void checkSW0Button(void)
	{
	if (!SW0_GetValue())
		{
        __delay_ms(80); // antibounce
        if (!SW0_GetValue())
			{
            if((NCOclock==ncoclk_hfintosc) || (NCOclock==ncoclk_fosc))
				{
                NCOclock=ncoclk_mfintosc31;
                }
            else if (NCOclock==ncoclk_mfintosc31)
                {
                NCOclock=ncoclk_hfintosc;
                }
			// stuck until button released
			while (!SW0_GetValue()) {continue;}
			}
		}
	}

// SW1 pushed : change NCO mode
void checkSW1Button(void)
	{
	if (!SW1_GetValue())
		{
        __delay_ms(80); // antibounce
        if (!SW1_GetValue())
			{
            // toggle NCO mode
            // I can do this way since NCOmode is only 0 or 1
            NCOmode=!NCOmode;
			// stuck until button released
			while (!SW1_GetValue()) {continue;}
			}
		}
	}

void setNCOclock(NCO_clock cl)
    {
    NCO1CLKbits.N1CKS=cl;
    }
/* calculate value to be loaded in NCO INC registers
 * based on passed frequency and actual oscillator used
 * this function will also set the global variable MaxFrequency
 * 
 * Calculations explained: 
 * in FDC mode overflow frequency must be divided by 2
 * (output toggles every overflow, so frequency is calculated
 * on 2 overflows...)
 * in order to obtain square wave frequency
 * So the formula is: 
 * freq=((nco_osc_freq*inc_register)/(2^20))/2 =>
 * freq=((nco_osc_freq*inc_register)/(2^21)) =>
 * freq=(nco_osc_freq*inc_register)/2097152 =>
 * inc_register=freq*(2097152/nco_osc_freq) =>

 * using MFINTOSC at 31250Hz (FDC) we have:
 * inc_register=freq*67,108864
 * Maximum frequency value=((31250*((2^20)-1)/(2^20))/2
 * = (31250*1048575/1048576)/2=15624Hz
 *
 * using FOSC or HFINTOSC at 32000000Hz (FDC) we have:
 * inc_register=freq*0,065536
 * Maximum frequency value=((32000000*((2^20)-1)/(2^20))/2
 * = (32000000*1048575/1048576)/2=15999984Hz
 * 
 * Maximum frequencies are doubled if in Pulse Frequency mode 
 */
uint32_t NCOIncFromFreq(uint32_t fr)
    {
    float increg=0; 
    if (NCOclock==ncoclk_mfintosc31) // 31250Hz
        {
        increg=(float)fr*67.109F;
        MaxFrequency=15625UL;
        MinFrequency=1;
        }
    else if (NCOclock==ncoclk_hfintosc) // supposed 32MHz
        {
        increg=(float)fr*0.065536F;
        MaxFrequency=15999985UL;
        MinFrequency=15625; // upper limit of mfintosc31
        }
	
    // in Pulse Frequency mode we must not use the division by 2
    // in calculations, so the step_increment, already calculated, must be multiplied by 2
    if (NCOmode==ncomode_pulse_frequency)
       {
       increg/=2;
       if (NCOclock==ncoclk_mfintosc31)
        {
        MaxFrequency=31250; 
        }
       // unfortunately, as I written in notes above,
       // oscilloscope gives nothing if frequency is set above FOSC/2
       // so this part is totally unuseful since you can't obtain
       // more than 16Mhz
       //else if (NCOclock==ncoclk_hfintosc) // supposed 32MHz
       // {
       // MaxFrequency=31999969;   
       // }
       }
    return (uint32_t)increg;
    }

/* NCO module will produce a frequency based on value given
 * to INCrement registers. Value is 20 bits, divided in 3
 * registers: NCO1 INCrement (Low, High and Upper)
 * datasheet says to fill first the upper, than the high 
 * and low at the end: when you fill the low register, 
 * new frequency will be generated
 */
void setNCOincreg(uint32_t val)
    {
    NCO1INCU = (uint8_t)(val>>16);
	NCO1INCH = (uint8_t)(val>>8);
	NCO1INCL = (uint8_t)val;
    NCO1ACCU = 0;
    NCO1ACCH = 0;
    NCO1ACCL = 0;
    }

// sets the NCO mode (Fixed Duty Cycle or Pulse Frequency Mode)
void setNCOmode(NCO_mode mod)
    {
    NCO1CONbits.N1PFM = mod; //0=FDC, 1=PFM
    NCOmode = mod;
    }

// sets the duty cycle when in PFMmode
void setNCOPulseDuty(uint8_t val)
    {
    if (NCOmode==ncomode_fixed_duty) return;
    if (val>7) val=7;
    NCO1CLKbits.N1PWS=val;
    }

/******************************************************************************
INTERRUPTS
 Interrupt on change for:
 RC2 (any)
 RC3 (any)
 in pin_manager (initialize) are activated interrupts for port Cx:
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
                Frequency+=step_increment;
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
                if (Frequency>step_increment)
                    {
                    Frequency-=step_increment;
                    }
                else
                    {
                    Frequency=step_increment;
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
                if (Frequency>step_increment)
                    {
                    Frequency-=step_increment;
                    }
                else
                    {
                    Frequency=step_increment;
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
                Frequency+=step_increment;
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
    static uint16_t Blinker=0;
    
    // flashing builtin led on RE0
    Blinker++;
    if (Blinker==500)
        {
        Blinker=0;
        LED_BUILTIN_Toggle();
        }
    
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