This example make use of the MAX7219sz PIC Lib.  
Please go [here](https://github.com/Cyb3rn0id/MAX7219sz_PIC_lib) for usage instructions.

Connections:  
- RC0 => MAX7219 Data
- RC1 => MAX7219 Clock
- RC3 => MAX7219 LOAD/!CS

Please note: To use the pins RC0 and RC1 as GPIO on the edge connector, some hardware modification is needed. Add a solder blob to the open straps on the bottom side to connect the routing. If you've connected the 32768Hz crystal, please disconnect it when using those pins as GPIO, as this might harm the crystal. If you don't want to use RC0 and RC1, you can easily change those pin from the Code Configurator, but you must name the pins as MAX_DAT (the one you want to connect to MAX7219 Data) and MAX_CLK (the one you want to connect to MAX7219 clock). The other pin, the one connected to MAX7219 LOAD/!CS is called MAX_LAT.
