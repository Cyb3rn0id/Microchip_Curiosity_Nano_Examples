/*
 RC3 = LAT
 RC1 = CLOCK
 RC0 = DATA
 */

// display segments as attached on shift registers bits
// on display OHO_DY1
#define SEG_A 0b00010000  
#define SEG_B 0b00000010 
#define SEG_C 0b00001000  
#define SEG_D 0b01000000  
#define SEG_E 0b10000000  
#define SEG_F 0b00000001 
#define SEG_G 0b00100000  
#define SEG_P 0b00000100  // decimal point

// digits definition
// OHO_DY1 display is common anode: 1=segment OFF, 0=segment on that's why I've put ~
// segments to be turned on for display numbers and simbols
// I've put ~ because display used is common anode, so 1=segment off and 0=segment on
uint8_t digits[]=
  {                                                          //  index value=digit showed on display
  (uint8_t)~(SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F),           //  0=0
  (uint8_t)~(SEG_B|SEG_C),                                   //  1=1
  (uint8_t)~(SEG_A|SEG_B|SEG_D|SEG_E|SEG_G),                 //  2=2
  (uint8_t)~(SEG_A|SEG_B|SEG_C|SEG_D|SEG_G),                 //  3=3
  (uint8_t)~(SEG_B|SEG_C|SEG_F|SEG_G),                       //  4=4
  (uint8_t)~(SEG_A|SEG_C|SEG_D|SEG_F|SEG_G),                 //  5=5
  (uint8_t)~(SEG_A|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G),           //  6=6
  (uint8_t)~(SEG_A|SEG_B|SEG_C),                             //  7=7
  (uint8_t)~(SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G),     //  8=8
  (uint8_t)~(SEG_A|SEG_B|SEG_C|SEG_D|SEG_F|SEG_G),           //  9=9
  (uint8_t)~(SEG_A|SEG_B|SEG_C|SEG_E|SEG_F|SEG_G),           // 10=A
  (uint8_t)~(SEG_C|SEG_D|SEG_E|SEG_F|SEG_G),                 // 11=b
  (uint8_t)~(SEG_A|SEG_D|SEG_E|SEG_F),                       // 12=C
  (uint8_t)~(SEG_B|SEG_C|SEG_D|SEG_E|SEG_G),                 // 13=d
  (uint8_t)~(SEG_A|SEG_D|SEG_E|SEG_F|SEG_G),                 // 14=E
  (uint8_t)~(SEG_A|SEG_E|SEG_F|SEG_G),                       // 15=F
  (uint8_t)~(0)                                              // 16=all segments OFF
  };

// mnemonic to array index for non-numbers
#define DIG_A 10
#define DIG_B 11
#define DIG_C 12
#define DIG_D 13
#define DIG_E 14
#define DIG_F 15
#define DIG_OFF 16

// digits in ram
uint8_t display_values[3];

// function prototypes
void display_set(uint8_t v1, uint8_t v2, uint8_t v3);
void display_reset(void);
void display_write(uint8_t num);
void display_update(void);
void ShiftOut(uint8_t dat);

