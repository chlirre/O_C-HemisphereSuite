// Copyright (c) 2020, Christoffer Meier
//
// Turing Machine based on https://thonk.co.uk/documents/random%20sequencer%20documentation%20v2-1%20THONK%20KIT_LargeImages.pdf
//
// I thank Jason Justian whom in turn thanks:
// Thanks to Tom Whitwell for creating the concept, and for clarifying some things
// Thanks to Jon Wheeler for the CV length and probability updates
// 
//
// Based on Ornament and Crime Hemisphere firmware
// Copyright (c) 2018, Jason Justian
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


#ifndef TURING_MACHINE_C_
#define TURING_MACHINE_C_

#include <turing_machine.h>
#include <stdint.h>

const uint8_t MIN_LENGTH = 2;
const uint8_t MAX_LENGTH = 16;
const uint8_t MIN_PROB = 0;
const uint8_t MAX_PROB = 100;

TuringMachine::TuringMachine(random_fn _random, uint32_t _reg, uint8_t _length, uint8_t _probability) {
    init(_random, _reg, _length, _probability);
}

TuringMachine::TuringMachine(random_fn _random, uint8_t _length, uint8_t _probability) {
    init(_random, _random(0, 65535), _length, _probability);
}

void TuringMachine::TuringMachine::init(random_fn _random, uint32_t _reg, uint8_t _length, uint8_t _probability) {
    random = _random;
    reg = _reg;
    setLength(_length);
    setProbability(_probability);
}
    
void TuringMachine::TuringMachine::setLength(uint8_t _length) {
    if (_length < MIN_LENGTH) {
        length = MIN_LENGTH;
        return;
    }    
    if (_length > MAX_LENGTH) {
        length = MAX_LENGTH;
        return;
    }
    length = _length;
}
void TuringMachine::TuringMachine::setProbability(uint8_t _probability) {
    if (_probability < MIN_PROB) {
        probability = MIN_PROB;
        return;
    }    
    if (_probability > MAX_PROB) {
        probability = MAX_PROB;
        return;
    }
    probability = _probability;
}

uint16_t TuringMachine::TuringMachine::getRegister() {
    return reg;
}

void TuringMachine::TuringMachine::Cycle() {
    // Grab the bit that's about to be shifted away
    int last = (reg >> (length - 1)) & 0x01;

    // Does it change?
    if (random(0, 99) < probability) last = 1 - last;

    // Shift left, then potentially add the bit from the other side
    reg = (reg << 1) + last;
}

#endif //#TURING_MACHINE_C_
