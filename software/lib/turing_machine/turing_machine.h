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


#ifndef TURING_MACHINE_H_
#define TURING_MACHINE_H_

#include <stdint.h>

static const uint8_t DEFAULT_LENGTH = 16;
static const uint8_t DEFAULT_PROBABILITY = 0;

typedef uint32_t (*random_fn)(uint32_t min, uint32_t max);


class TuringMachine {
    
    public: 
        TuringMachine(random_fn _random, uint32_t _reg, uint8_t _length = DEFAULT_LENGTH, uint8_t _probability = DEFAULT_PROBABILITY);
        TuringMachine(random_fn _random, uint8_t _length = DEFAULT_LENGTH, uint8_t _probability = DEFAULT_PROBABILITY);
        void setLength(uint8_t _length);
        void setProbability(uint8_t _probability);
        uint16_t getRegister();
        void Cycle();

    private:
        void init(random_fn _random, uint32_t _reg, uint8_t _length, uint8_t _probability);
        uint16_t reg;
        uint8_t length;
        uint8_t probability;
        random_fn random;
};

#endif //#TURING_MACHINE_H_