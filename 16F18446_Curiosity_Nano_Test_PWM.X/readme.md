System Clock: 32MHz internal  
PWM OUT on RA5 (Freq.: 1MHz, 50% Duty Cycle)  
FOSC/4 on RA4 (8MHz)  
  
Notes:  
Used CCP1 module+Timer 2  

CCP1 Settings:
- Enable CCP
- CCP Mode: PWM
- Timer used: Timer 2
- Duty Cycle: 50%  
PWM Frequency will be determined by Timer 2 settings  

Timer 2 settings:  
- Enable Timer
- Control Mode: Roll over puls
- Start-Reset: Software
- Clock Source: FOSC/4
- Prescaler: 1:1
- Postscaler: 1:1
- Timer period: 1uS (micro second)

Other settings:
- RA4 locked on OSC-CLKOUT output in the Pin Manager grid.  

Oscilloscope image:  
![Oscilloscope image - 1MHz on RA5, FOSC/4 on RA4](../assets/PIC16F18446_PWM_example.jpg)
Yellow signal: 1MHz square wave (50%) out from RA5. Frequency is changed by editing Timer Period/Pre+Post scaler and/or System Clock  
Blue signal: FOSC/4 (8MHz) out from RA4. I've put this only for reference: having the FOSC/4 output is always good as test to be sure you've correctly configured the system clock
