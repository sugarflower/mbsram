/*
library for simple SRAM access.

Copyright (c)2017 te3game
Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
and associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is 
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or 
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN 
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION 
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "mbsram.h"

void mbsram::begin(){
	pinMode(sramCS , OUTPUT);
	mbsram::writeSRAMCS( HIGH );
}

uint8_t mbsram::read(uint16_t address){
	mbsram::writeSRAMCS( LOW );
	mbsram::buf = mbsram::rw(3);
	mbsram::buf = mbsram::rw(address >> 8 );
	mbsram::buf = mbsram::rw(address & 0xff );
	mbsram::buf = mbsram::rw(0);
	mbsram::writeSRAMCS( HIGH );
	return mbsram::buf;
}

void mbsram::write(uint16_t address, uint8_t value){
	mbsram::writeSRAMCS( LOW );
	mbsram::buf = mbsram::rw(2);
	mbsram::buf = mbsram::rw(address >> 8 );
	mbsram::buf = mbsram::rw(address & 0xff );
	mbsram::buf = mbsram::rw(value);
	mbsram::writeSRAMCS( HIGH );
}

uint8_t mbsram::rw(uint8_t value){
	return SPI.transfer( value );
}

void mbsram::writeSRAMCS(uint8_t state){
	digitalWrite(sramCS, state);
}
