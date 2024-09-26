#include <stdint.h>
#include "7seg74HC595.h"
#include "mcc_generated_files/pin_manager.h"

// *****************************************************************************************
// Display functions
// *****************************************************************************************
// set single digits to passed values
// example:
// you want to show 1A9 on display
// you write: display_set(1, DIG_A, 9);
// or: display_set(1, 10, 9) since DIG_A=10 and the digits array index 10 shows the A letter
void display_set(uint8_t v1, uint8_t v2, uint8_t v3)
  {
  display_values[2]=digits[v1];
  display_values[1]=digits[v2];  
  display_values[0]=digits[v3];  
  display_update();
  }

// reset display
void display_reset(void)
  {
  display_set(DIG_OFF, DIG_OFF, DIG_OFF); 
  }
  
// writes an unsigned integer to display
void display_write(uint8_t num)
  {
  uint8_t digit1=DIG_OFF;
  uint8_t digit2=DIG_OFF;
  uint8_t digit3=DIG_OFF;
  
  if (num<10)
    {
    digit3=num;  
    }
  else if (num<100)
    {
    digit3=num%10;
    digit2=num/10;  
    }
  else
    {
    digit3=num%10;
    digit2=(num%100)/10;
    digit1=num/100;  
    }
  display_set(digit1, digit2, digit3);
  }

// transfer datas from array in ram to shift registers
void display_update(void)
  {
  // send data to shift registers from last number to first number
  for (int8_t i=2; i>=0; i--) 
    {
    ShiftOut(display_values[i]);
    }
  // strobe signal on latch pin
  SR_LAT_SetHigh();
  SR_LAT_SetLow();
  }

// transmit an integer one bit at time, from MSB to LSB
void ShiftOut(uint8_t dat)
    {
    // scan bits from left to right
    for (uint8_t i=0; i<8; i++)  
        {
        if (dat & (0x80>>i))
            {
            SR_DAT_SetHigh();
            }
        else
            {
            SR_DAT_SetLow();
            }
        // clock strobe
        SR_CLK_SetHigh();
        SR_CLK_SetLow();
        }
    }