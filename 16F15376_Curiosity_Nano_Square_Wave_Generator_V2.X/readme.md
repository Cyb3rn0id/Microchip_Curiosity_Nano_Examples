# Square Wave generator Version 2

### What this example does
- Generates square waves with 50% Duty Cycle (NCO in Fixed Duty Cycle mode) or with (very little) variable Duty Cycle (NCO in Pulse Frequency mode) from 1Hz to 16MHz with 1Hz step.

### Notes
- SW0 (swith included on the board) is used for changing the NCO Clock Source (HFINTOSC or MFINTOSC at 31250Hz)
- SW1 (additional button on RB4) is used for changing the NCO mode (Fixed Duty / Pulse Frequency)
- A potentiometer between VDD rail and GND is connected on RA0/AN0 and used to change the Duty Cycle in Pulse Frequency Mode
- An encoder is used: encoder pins, A & B, are connected to RC2 and RC3: turning the encoder, frequency will increment/decrement by some steps. Steps are defined by pressing the encoder stem.
- Is mandatory to power LCD and board using an external power supply. For doing this, if you're using the Curiosity Nano, you must put board VOFF pin to GND and give a 5V supply on VTG pin. IT' DANGEROUS give 5V on VTG without putting VOFF to GND. Please see [repository ReadMe](https://github.com/Cyb3rn0id/Microchip_Curiosity_Nano_Examples#running-at-5-or-33v) paragraph "Running at 3.3 or 5V"
- Example is configured for a 16x2 LCD
- NCO output on RD2
- The builtin-led (RE0) flashes every 500mS managed by Timer0 interrupt

### Findings
- After 10MHz waves appears very weird and with low Vpp voltage : probably some sort of filter is needed.
- In the actual version of MCC I'm using there is a thing I can think is a bug: even if you configure the ADC module, this module will not work since remains disabled in the PMD (Peripheral Module Disable) registers. So if you have some troubles using ADC Module in your next projects and you cannot understand why this one works, it's because I've manually enabled the ADCMD bit in the PMD2 register. Same thing happens if you want to use the FVR (Fixed Voltage Reference): it's always disabled (register PMD0).
- You can achieve frequencies below 1Hz even if I didn't implemented this feature in the code (it needs frequency steps of 0.1 and 0.01Hz). The minimun frequency I achieved is 0.015Hz (measured on oscilloscope) using the LFINTOSC as clock source, FDC mode, and value 1 loaded in the increment register (you must have lot of patience to see the signal on the oscilloscope! It means a wave every 66seconds! So basetime must be very extended).
- The maximum frequency I achieved (always measured on oscilloscope) is always FOSC/2 in both modes. And this is strange! It's possible to load the maximum value of 1048575 (20bits) when using low frequencies clock sources (LFINTOSC, MFINTOSC at 500 or 31kHz): output on pin will be always what you expect: for example with MFINTOSC at 500kHz and 1048575 loaded, you'll obtain 250kHz in FDC and 500kHz in PF. Problems happens using FOSC or HFINTOSC. For example using 32MHz, if I load the value 1048575, FDC mode, I obtain what I expect: 16MHz (even if the square wave looks very weird!), but in PF mode I can't detect any signal on oscilloscope (only noise). In PF mode I reached a maximum of 16MHz loading the value 1048575/2 so the Maximum appears always to be 16MHz! It's not a problem of "32MHz": this happens even if I set 16MHz or 1MHz as FOSC: maximum I can achieve in always FOSC/2 in both modes! This is weird since using MPLAB CODE CONFIGURATOR and setting FOSC 32MHz, PF, it shows that 32MHz can be reached! Probably this frequency can be reached only internally but not as pin output but I repeat: is not a 32MHz thing... this happens with every frequency, even with only 1MHz! So it's really not a problem of maximum frequency a pin can manage! I tried also using the external crystal at 8MHz, with or without 4xPLL: behaviour is always the same in every condition (and the 16MHz wave appears "weird" in the same exact way using the external crystal!).

### System settings:
- system clock: 32MHz
- Interrupt on Timer0 every 1mS
- Interrupt on RC2 and RC3 for any state change

### Connections
Please note: LCD DATA and RS must be on the same port bank! In the example are connected to D bank. Enable and Read/write can be on different port banks. Remember this if you want to change ports

| Component    | PIC16F15376 Curiosity Nano pin |
|:-------------|:-------------------------------|
|LCD RS        |RD3                             |
|LCD RW        |RB5                             |
|LCD EN        |RC0                             |
|LCD D4 to D7  |RD4 to RD7                      |
|ENCODER A     |RC2                             |
|ENCODER B     |RC3                             |
|ENCODER BUTTON|RC4                             |
|SW0           |RE2 (default on nano board)     |
|SW1           |RB4                             |
|POTENTIOMETER |RA0/AN0                         |
|LED           |RE0                             |
|NCO OUTPUT    |RD2                             |

### Display Pinout
![LCD Pinout](../assets/images/LCD_HD44780_Pinout.png)

### Schematic
...to do...

### Links
- [Article on my blog about the previous version](https://www.settorezero.com/wordpress/un-generatore-di-onda-quadra-da-1hz-a-16mhz-con-un-microcontrollore-pic/)

### Pictures
...to do...
