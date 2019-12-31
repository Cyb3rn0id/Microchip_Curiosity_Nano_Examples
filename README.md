# Microchip Curiosity Nano Examples   
![PIC16F15376 Curiosity Nano](assets/image.jpg)

My experiments and snippets with Microchip Curiosity Nano boards.

### Powering Curiosity Nano 
#### Running at 5 or 3.3V 
By default Curiosity nano runs at 3.3V when powered from USB: there is a software controlled variable regulator on board that generates the VTG (V Target). If you want to run the board @5V when you power it from USB you must change a parameter in the project configuration: 
- Right click on project in "Projects" tree and select "Properties"
- in "Categories" box on the left, select "PKOB Nano"
- in "Option Categories" dropdown box, on the right, select "Power"
- check the "Power target circuit" checkbox
- write "5" in the blank field "Voltage level"
- press OK   

The project property will be changed and will be active the next time you'll program the board. Voltage change is permanent, so there is no need to keep this setting every-time for every project: be careful. This setting, obviously, only affect the V Target when you power the board from USB. Following picture illustrates where this setting is located:   

![VTG modification](assets/changing_Vtarget.png)    

#### Powering from external 
If you want to power the board from the external instead of USB, you must tie to GND the pin "VOFF": it's the second pin on the right, starting from top, having the USB connector on top: this will disable the on board regulator. Now you can power the board from the pin "VTG": it's the sixth pin on the right, starting from top, having the USB connector on top. The voltage you apply will not be affected by the modification explained above.   

![Curiosity Nano Debugger Pinout](assets/curiosity_nano_standard_debugger_pinout.png)   

### Usage of certain pins  
Following infos are for the PIC16F15376 Curiosity Nano.  
- RCO and RC1: Normally, those pins are not routed from edge connector to PIC MCU, so if you would to use them, put a solder blob on pads on the bottom of the board
- RB6 and RB7: Those pins are used by the debugger (DGB0 and DBG1), maybe is safe to use if you disconnect them first than programming 

### Links
- My Simple (italian) [tutorial about Curiosity Nano and MPLAB Code Configurator](https://www.settorezero.com/wordpress/curiosity-nano-code-configurator-per-entrare-nel-mondo-dei-microcontrollori-pic-senza-sforzo-e-in-economia/)
- [Microchip Curiosity Nano Portfolio](https://www.microchip.com/design-centers/8-bit/development-tools/pic-hardware/curiosity-nano-development-platform)
