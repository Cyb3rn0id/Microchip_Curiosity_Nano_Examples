# Blinking led on Timer0 Interrupt with debug

### What this example does:
- The on-board LED (connected on RF3) toggles every 500mS (1Hz flash rate) using the overflow interrupt on Timer0
- The debug pin (aka _GPIO0_ aka _DBG2_ aka _RB4_) will toggle too allowing the user to visualize the event on the _Data Visualizer_ component of MPLABX

### Notes:
- The onboard witch, SW0, is connected on the same IO used as debug pin, so pay attention when you use this switch but you want also to use this debug feature
- The Timer0 interrupt is actually set to fire every 4uS: even if from the Timer0 Hardware settings is possible to go under to 15.625x10^-9 seconds (15.626nS), in the reality we can't go uder 4uS: even putting 1uS, interrupt fires every 4uS since there are anyway lot of instructions to be executed at FOSC/4=16MHz rate: not only instructions written in my ISR but also ones called by the Timer0 interface created by Mplab Melody (TMR0_OverflowISR() in _tmr0.c_ called by __interrupt() INTERRUPT_InterruptManagerHigh() in _interrupt.c_). Obviously you don't need an 1uS or 4uS rate interrupt for blinking a led! This was only a demo program for showing capabilities and learn to use MPLABX tools.

I posted this question on the [Microchip Forum](https://forum.microchip.com/s/topic/a5CV40000002KYvMAM/t398385)

![Timer0 Settings](../assets/images/18F57Q43_blink_TImer0_Settings.png)

### Settings:
- External oscillator: not enabled
- Oscillator used: HFINTOSC at 64MHz
- Interrupt manager set to use High and Low priorities
- Timer0 set as High Priority Interrupt
- RB4 set as output to be used as debug pin 

### How to use Data Visualizer
- You have to set RB4 as output. Remember that RB4, from the Debug side, is known as _GPIO 0_
- After you uploaded code on the board, start the _Data Visualizer_ component by pressing the _DV_ icon:  

![Data Visualizer button](../assets/images/Data_Visualizer_button.png)

- In the data visualizer, set _GPIO 0_ in the _Data Axis_ settings on the right of the plot area:  

![Data Visualizer button](../assets/images/18F57Q43_enable_debug_gpio0.png)

- Press the _PLAY_ button next to the _Debug GPIO_ feature on the left of plot area:  

![Data Visualizer button](../assets/images/Start_Capturing_GPIO0.png)

- If you don't see any signal in the plot area, maybe the plot is paused, so click _Show Live Data_ in the upper part of the plot area:  

![Data Visualizer button](../assets/images/Show_Live_Data.png)