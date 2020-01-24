# Simple Menu on LCD using a rotary encoder

### What this example does:
- There is a menu on display, this menu has 2 pages. Every page allows to change a different variable ('var' changed in page 0, 'var2' changed in page 1).
- You can cycle through menu pages pushing encoder button. Encoder button is connected on RE2 that is the same pin used by SW0 on PIC16F15376 Curiosity Nano, so if your encoder does not have a pushbutton, you can use SW0. 
- You can change currently showed variable value turning the encoder.
- If you want increase variable turning clock-wise and you see that behavior is different, invert encoder A/B pins connections.

### Notes:
- Is mandatory to power LCD and board using an external power supply. For doing this you must put board VOFF pin to GND and give a 5V supply on VTG pin. IT' DANGEROUS give 5V on VTG without putting VOFF to GND. Please see [repository ReadMe](https://github.com/Cyb3rn0id/Microchip_Curiosity_Nano_Examples#running-at-5-or-33v) paragraph "Running at 3.3 or 5V"
- Example is configured for an 20x4 LCD
- Encoder I've used is very cheap and give me a lot of noise. In order to properly debounce it, I've used a debounce routine based on Timer0 (I don't check the encoder if a certain time is passed) and I count 3 consecutive tick for assuming 1 only tick. In this manner I got no oscillations on value but sometimes is necessary turn one more time the encoder in order to see a change in the variable value. If you have a better solution to this, you can open an issue.

### System settings:
- system clock: 32MHz
- interrupts on ANY change on RC2 and RC3
- interrupt on Timer0 every 1mS (used for encoder debounce)

### Connections
Please note: if you want to change connections remember that LCD DATA and LCD RS must be on the same port bank! In this example those pins are all connected on D bank. LCD Enable and LCD Read/write can be connected on different port banks. 

| Connections  | PIC16F15376 Curiosity Nano pin |
|:-------------|:-------------------------------|
|LCD RS        |RD3                             |
|LCD RW        |RB5                             |
|LCD EN        |RC0                             |
|LCD D4 to D7  |RD4 to RD7                      |
|Encoder A     |RC2                             |
|Encoder B     |RC3                             |
|Encoder Button|RE2 (=SW0)                      |

### Video: How this demo works
[![Menu with encoder Demo](https://img.youtube.com/vi/mWQ9CHzGuuE/maxresdefault.jpg)](https://www.youtube.com/watch?v=mWQ9CHzGuuE)  

### Display Pinout
![LCD Pinout](../assets/LCD_HD44780_Pinout.png)
