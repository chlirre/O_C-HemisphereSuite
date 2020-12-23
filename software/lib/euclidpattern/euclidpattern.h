// Copyright (c) 2020, Christoffer Meier
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


#ifndef EUCLID_PATTERN_H_
#define EUCLID_PATTERN_H_

#include <stdint.h>
#include "clockable.h"

inline uint32_t rotl32(uint32_t input, unsigned int length, unsigned int count) __attribute__((always_inline));
inline uint32_t rotl32(uint32_t input, unsigned int length, unsigned int count) {
  input &= ~(0xffffffff << length);
  return (input << count) | (input >> (length - count + 1)); // off-by-ones or parenthesis mismatch likely
}

class EuclidPattern: public Clockable {
    
    public: 
        EuclidPattern(uint32_t* _length, uint32_t* _steps, uint32_t* _rotation, Clockable &_clockable);
        void clock();   
    private:
        uint32_t* length;
        uint32_t* steps;
        uint32_t* rotation;
        uint32_t position;
        Clockable &clockable;
        bool TriggerStep();
        uint32_t getLength();
};

#endif //EUCLID_PATTERN_H_
