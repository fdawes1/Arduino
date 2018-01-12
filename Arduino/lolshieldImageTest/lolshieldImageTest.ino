/*
Basic LoL Shield Test

Writen for the LoL Shield, designed by Jimmie Rodgers:

http://jimmieprodgers.com/kits/lolshield/

This needs the Charliplexing library, which you can get at the
LoL Shield project page: http://code.google.com/p/lolshield/

Created by Jimmie Rodgers on 12/30/2009.
Adapted from: http://www.arduino.cc/playground/Code/BitMath

History:
December 30, 2009 – V1.0 first version written at 26C3/Berlin

This is free software; you can redistribute it and/or
modify it under the terms of the GNU Version 3 General Public
License as published by the Free Software Foundation;
or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <avr/pgmspace.h>  //AVR library for writing to ROM
#include <Charliplexing.h> //Imports the library, which needs to be
//Initialized in setup.

//Sets the time each frame is shown (milliseconds)
const unsigned int blinkdelay = 1000 / 50;

/*
The BitMap array is what contains the frame data. Each line is one full frame.
Since each number is 16 bits, we can easily fit all 14 LEDs per row into it.
The number is calculated by adding up all the bits, starting with lowest on
the left of each row. 18000 was chosen as the kill number, so make sure that
is at the end of the matrix, or the program will continue to read into memory.

Here PROGMEM is called, which stores the array into ROM, which leaves us
with our RAM. You cannot change the array during run-time, only when you
upload to the Arduino. You will need to pull it out of ROM, which is covered
below. If you want it to stay in RAM, just delete PROGMEM
*/

void setup() {
LedSign::Init(DOUBLE_BUFFER | GRAYSCALE);  //Initializes the screen
}
void loop() {
//  int b;
//  LedSign::Clear(0);
// // LedSign::Flip(true);
//  for (int y=0; y<=8; y++) {
//    for (int x=0; x<=13; x++) {
//       // LedSign::Clear(0);
//       b=y;
//       if (b<1) {b=1;}
//       if (b>7) {b=7;}
//        LedSign::Set(x, y, b);
//        LedSign::Set(5, 0, 0);
// LedSign::Set(6, 4, 0);
// LedSign::Set(5, 2, 0);
// LedSign::Set(5, 3, 0);
// LedSign::Set(13, 7, 0);
// LedSign::Set(6, 5, 0);
// LedSign::Set(7, 3, 0);
//       LedSign::Flip(true);
//      delay(250);
//    }
//  }
LedSign::Set(0, 8, 0);
LedSign::Set(0, 7, 1);
LedSign::Set(0, 6, 3);
LedSign::Set(0, 5, 2);
LedSign::Set(0, 4, 1);
LedSign::Set(0, 3, 1);
LedSign::Set(0, 2, 1);
LedSign::Set(0, 1, 6);
LedSign::Set(0, 0, 6);
LedSign::Set(1, 8, 0);
LedSign::Set(1, 7, 4);
LedSign::Set(1, 6, 3);
LedSign::Set(1, 5, 1);
LedSign::Set(1, 4, 1);
LedSign::Set(1, 3, 1);
LedSign::Set(1, 2, 6);
LedSign::Set(1, 1, 6);
LedSign::Set(1, 0, 6);
LedSign::Set(2, 8, 0);
LedSign::Set(2, 7, 0);
LedSign::Set(2, 6, 1);
LedSign::Set(2, 5, 1);
LedSign::Set(2, 4, 1);
LedSign::Set(2, 3, 1);
LedSign::Set(2, 2, 1);
LedSign::Set(2, 1, 6);
LedSign::Set(2, 0, 6);
LedSign::Set(3, 8, 0);
LedSign::Set(3, 7, 3);
LedSign::Set(3, 6, 0);
LedSign::Set(3, 5, 1);
LedSign::Set(3, 4, 0);
LedSign::Set(3, 3, 1);
LedSign::Set(3, 2, 6);
LedSign::Set(3, 1, 6);
LedSign::Set(3, 0, 6);
LedSign::Set(4, 8, 1);
LedSign::Set(4, 7, 3);
LedSign::Set(4, 6, 0);
LedSign::Set(4, 5, 1);
LedSign::Set(4, 4, 0);
LedSign::Set(4, 3, 1);
LedSign::Set(4, 2, 1);
LedSign::Set(4, 1, 6);
LedSign::Set(4, 0, 6);
LedSign::Set(5, 8, 0);
LedSign::Set(5, 7, 3);
LedSign::Set(5, 6, 3);
LedSign::Set(5, 5, 1);
LedSign::Set(5, 4, 0);
LedSign::Set(5, 3, 1);
LedSign::Set(5, 2, 6);
LedSign::Set(5, 1, 6);
LedSign::Set(5, 0, 6);
LedSign::Set(6, 8, 1);
LedSign::Set(6, 7, 4);
LedSign::Set(6, 6, 3);
LedSign::Set(6, 5, 4);
LedSign::Set(6, 4, 5);
LedSign::Set(6, 3, 5);
LedSign::Set(6, 2, 6);
LedSign::Set(6, 1, 6);
LedSign::Set(6, 0, 6);
LedSign::Set(7, 8, 1);
LedSign::Set(7, 7, 4);
LedSign::Set(7, 6, 2);
LedSign::Set(7, 5, 4);
LedSign::Set(7, 4, 5);
LedSign::Set(7, 3, 5);
LedSign::Set(7, 2, 6);
LedSign::Set(7, 1, 6);
LedSign::Set(7, 0, 6);
LedSign::Set(8, 8, 4);
LedSign::Set(8, 7, 4);
LedSign::Set(8, 6, 5);
LedSign::Set(8, 5, 2);
LedSign::Set(8, 4, 1);
LedSign::Set(8, 3, 4);
LedSign::Set(8, 2, 6);
LedSign::Set(8, 1, 6);
LedSign::Set(8, 0, 6);
LedSign::Set(9, 8, 3);
LedSign::Set(9, 7, 3);
LedSign::Set(9, 6, 3);
LedSign::Set(9, 5, 2);
LedSign::Set(9, 4, 1);
LedSign::Set(9, 3, 1);
LedSign::Set(9, 2, 1);
LedSign::Set(9, 1, 6);
LedSign::Set(9, 0, 6);
LedSign::Set(10, 8, 4);
LedSign::Set(10, 7, 3);
LedSign::Set(10, 6, 3);
LedSign::Set(10, 5, 2);
LedSign::Set(10, 4, 1);
LedSign::Set(10, 3, 1);
LedSign::Set(10, 2, 1);
LedSign::Set(10, 1, 6);
LedSign::Set(10, 0, 6);
LedSign::Set(11, 8, 3);
LedSign::Set(11, 7, 2);
LedSign::Set(11, 6, 2);
LedSign::Set(11, 5, 1);
LedSign::Set(11, 4, 1);
LedSign::Set(11, 3, 1);
LedSign::Set(11, 2, 1);
LedSign::Set(11, 1, 1);
LedSign::Set(11, 0, 2);
LedSign::Set(12, 8, 3);
LedSign::Set(12, 7, 3);
LedSign::Set(12, 6, 3);
LedSign::Set(12, 5, 1);
LedSign::Set(12, 4, 1);
LedSign::Set(12, 3, 1);
LedSign::Set(12, 2, 1);
LedSign::Set(12, 1, 1);
LedSign::Set(12, 0, 6);
LedSign::Set(13, 8, 2);
LedSign::Set(13, 7, 0);
LedSign::Set(13, 6, 0);
LedSign::Set(13, 5, 0);
LedSign::Set(13, 4, 0);
LedSign::Set(13, 3, 1);
LedSign::Set(13, 2, 1);
LedSign::Set(13, 1, 1);
LedSign::Set(13, 0, 1);

// LedSign::Set(5, 0, 0);
// LedSign::Set(6, 4, 0);
// LedSign::Set(5, 2, 0);
// LedSign::Set(5, 3, 0);
// LedSign::Set(13, 7, 0);
// LedSign::Set(6, 5, 0);
// LedSign::Set(7, 3, 0);
LedSign::Flip(true);
delay(500);

//  delayMicroseconds(5);
//  LedSign::Clear(0);
//  LedSign::Set(4, 3, 1);
//  LedSign::Flip(true);
//  delayMicroseconds(5);
}
