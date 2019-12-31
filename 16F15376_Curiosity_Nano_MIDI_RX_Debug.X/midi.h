//************************************************************
// MIDI Debugger
// Version 1.0
// CC BY-NC-ND 4.0
// module:      midi.h
//
// (C)2019 Bernardo Giovanni (CyB3rn0id)
// http://www.settorezero.com
//
//
// This work is distributed under CC BY-NC-ND 4.0
// Please read license before use:
// https://creativecommons.org/licenses/by-nc-nd/4.0/
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORTOR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//************************************************************

// download MIDI 1.0 spec:
// https://www.midi.org/specifications/item/the-midi-1-0-specification
//
// channel messages (bytes 7-4 of status byte)
// (bytes 3-0 identify the channel)
#define NOTEOFF     0b1000 // note off (note number - velocity)
#define NOTEON      0b1001 // note on  (note number - velocity)
#define POLYPRESS   0b1010 // polyphonic key pressure (note number - pressure) (=after touch on single note)
#define CC          0b1011 // control change (controller number - value)
#define PC          0b1100 // program change (program number)
#define CHANPRESS   0b1101 // channel pressure (pressure) (=after touch on entire channel)
#define PITCHBEND   0b1110 // pitch bend  (value LSB - value MSB)

// system messages
// (bytes 3-0 are all zeroes)
#define SYSMSG      0b11110000 // system messagge (to all channels)
#define EOX         0xF7       // end of system message

// Note names - 12 values
// diesis are written with lower-case letter: in the software they will be
// transformed in upeer-case + diesis symbol
const uint8_t notename[]={'C','c','D','d','E','F','f','G','g','A','a','B'};

// Following MIDI standard, the octave -1 starts from C0 (note n. 0)
// octave number 0 starts from C1 (note n. 12)
// octave number 1 starts from C2 (note n. 24) ecc
// in order to know the octave number you can divide the note number by 12
int8_t octave=-1; // octave from -1 to 9
uint8_t notepos=0;