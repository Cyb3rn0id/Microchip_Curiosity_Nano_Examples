# Updated LCD Library

Since Microchip has changed path names and pin definitions I adjusted the library according MPLABX IDE V6.35 and MPLAB Code Configurator 5. So, for example `_LCD_RS_PORT` become `_LCD_RS_PORT_LAT`, `_LCD_RS_TRIS` become `_LCD_RS_PORT_TRIS` and so on.



Some PIC MCUs works properly with library up to 32MHz while other not: in this case the `LCD_INIT` routine stay stuck: I added a `BUSY_BYPASS` macro for avoiding the busy routine and apply a standard delay instead: uncomment that macro in library header file if you cannot init the display (this whill happen when PIC runs from 32MHz above).
