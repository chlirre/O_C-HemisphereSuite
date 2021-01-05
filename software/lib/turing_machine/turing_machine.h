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
#include "triggable.h"

static const uint8_t DEFAULT_LENGTH = 16;
static const uint8_t DEFAULT_PROBABILITY = 0;

typedef uint16_t (*random_fn)(uint16_t min, uint16_t max);

class TuringMachine: public Triggable {
    
    public: 
        TuringMachine(
            random_fn _random, 
            uint16_t* reg, 
            uint8_t* _length, 
            uint8_t* _probability, 
            uint16_t* _scaledFiveBitOut,
            uint16_t* _scaledEightBitOut
        );
        void trig();
        const uint16_t DEFAULT_LENGTH = 16;
        const uint16_t DEFAULT_PROBABILITY = 0;

    private:
        uint16_t* reg;
        uint8_t* length;
        uint8_t* probability;
        random_fn random;
        uint16_t* scaledFiveBitOut;
        uint16_t* scaledEightBitOut;
        uint8_t getLength();
        uint8_t getProbability();
        void updateOutput();
};

#endif //#TURING_MACHINE_H_
