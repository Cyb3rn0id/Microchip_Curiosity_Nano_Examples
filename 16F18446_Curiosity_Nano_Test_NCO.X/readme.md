System Clock: 32MHz internal  
NCO OUT on RA5 (Start Freq.: 1007Hz, 50% Duty Cycle)  
FOSC/4 on RA4 (8MHz).  
By pressing SW0, frequency will increment.  You need an oscilloscope of a Frequency counter to see it.  

NCO stands for the Numerically Controlled Oscillator.  
In this example is used in FDC mode (Fixed Duty Cycle). In this mode, incrementing the INC registers, frequency output will rise.  
INC registers will be loaded in the accumulator. Every time accumulator overflows, pin is toggled. Overflow frequency is determined by this formula:  

F_overflow=(NCO_Clock_Freq x INC_value)/(2^20)  

with NCO_Clock_Freq=32MHz (32000000Hz), INC_value=66, F_Overflow is 2014Hz => so pin will be toggled every 495uS and then, since Ton=Toff=495uS, output frequency on the pin will be 1007Hz.  
In the code, pressing SW0, the INC register value is incremented by one every button press.

### NCO1 Settings:
- Enable NCO
- NCO mode: FDC_mode
- Clock Source: FOSC
- NCO Output Frequency: 1KHz (actual: 1007Hz)
PWM Frequency will be determined by Timer 2 settings  

### Other settings:
- RA4 locked on OSC-CLKOUT output in the Pin Manager grid.
- RA5 locked on NCO1- NOC1OUT output in the Pin Manager grid.

[![Example Video of this code](https://img.youtube.com/vi/7wrxOczbIB0/maxresdefault.jpg)](https://youtu.be/7wrxOczbIB0)
