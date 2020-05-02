# Reading RFID 125kHz Tags using an RDM6300 module

### What this example does:
- Reads a 125kHZ RFID Tag using an RDM6300 module and shows tag info on am LCD 16x2
- the onboard LED (LED0) turns on during TAG reading
- A buzzer sounds when a tag is received and printed on display

### What this example doesn't do:
- evaluate the TAG checksum

### Notes
I'm talking about the RDM6300 module (Six thousand three Hundred) but there is also an RDM630 (six hundred and thirty) that looks similar and internet says works at same manner of RDM6300 so I think those two modules are swappable since have an identical form-factor and pinout.

### Connections
Please note: if you want to change connections remember that LCD DATA and LCD RS must be on the same port bank!
You can't connect the buzzer directly on the port: you must do this using a transistor.  
RDM6300 module have TX connected to RC7 of Curiosity Nano configured as UART1 RX. Module has also an RX pin but no documents talk about functions you can transmit to it, so I left this pin disconnected.  
The LED pin of the RDM6300 can drive a small led (connect the pin to led cathode and connect the anode to +5V, the led will flash during TAG detecting).

 
| Connections  | PIC16F15376 Curiosity Nano pin |
|:-------------|:-------------------------------|
|LCD RS        |RD3                             |
|LCD RW        |RB5                             |
|LCD EN        |RC0                             |
|LCD D4 to D7  |RD4 to RD7                      |
|Buzzer        |RA0                             |
|LED0          |RE0                             |
|RX            |RC7                             |

### Links
- [RMD6300 wiki on ITEAD](https://www.itead.cc/wiki/RDM6300)
- [Nice picture of module pinout](https://www.kriwanek.de/index.php/de/homeautomation/esp8266-ger%C3%A4te/wemos-ger%C3%A4te/561-rdm6300-rfid-reader)

### Video
Here is a video showing how it works:  
[![RFID Reader demo](https://img.youtube.com/vi/zu99cKpayJY/maxresdefault.jpg)](https://www.youtube.com/watch?v=zu99cKpayJY)  
