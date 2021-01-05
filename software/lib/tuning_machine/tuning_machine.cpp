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

#ifndef TUNING_MACHINE_C_
#define TUNING_MACHINE_C_

#include <stdint.h>
#include "tuning_machine.h"
#include "braids_quantizer.h"
#include "clock_div.h"

const uint8_t RANDOMNESS_SPREAD_FACTOR = 8;

TuningMachine::TuningMachine(
    random_fn _random,
    constrain_fn _constrain,
    // Idea: The note mask could be be ortogonal between the two instances of TuningMachines
    // Perhaps represented as euclidian patterns where steps =~length/2
    // Note mask would be inverted for the other TuningMachines
    // Perhaps controlled by gate in?
    braids::Quantizer* _quantizer, 
    // The scale might not be needed here, only the quantizer
    braids::Scale* _scale,
    uint8_t* _density,
    uint8_t* _randomness,
    int32_t* _quantized_pitch_out
) : random(_random), constrain(_constrain), tm_quantizer(_quantizer), tm_scale(_scale),
    density(_density), randomness(_randomness), quantized_pitch_out(_quantized_pitch_out) {
        // initAll() ?
    }

void TuningMachine::trig() {
    // So, what should this app do?
    trigAll();
    updateAll();
    *quantized_pitch_out = (*tm_quantizer).Process(sampleAndHoldOut);   
}

bool TuningMachine::getAndClearTriggered() {
    bool wasTriggered = sampleAndHoldSpy.wasTrigged();
    sampleAndHoldSpy.reset();
    return wasTriggered;
}

void TuningMachine::trigAll() {
    for (int i = 0; i < tmsClockDiv.size(); i++) {
        tmsClockDiv[i].trig();
    }
    switchingTMClockDiv.trig();
    fourChannelSwitch.setChannel(switchingTuringMachineScaledFiveBitOut % 4);
    euclid.trig();
}

void TuningMachine::updateAll() {
    // Example "algorithm"
    for(int i = 0; i < SWITCH_SIZE; i++) {
        tmsProbability[i] = *randomness / RANDOMNESS_SPREAD_FACTOR; // Logistic curve?
        // f(x) = max / (1 + e^(-k)*(x-x0)) 
        // where 
        // max = the curve's maximum value
        // k = the logistic growth rate or steepness of the curve
        // x0 = midpoint (of result, i.e. MAX_PROBABILITY / 2)
        // https://en.wikipedia.org/wiki/Logistic_function
        tmsDivision[i] = 4 - 3; // TODO: Something musical with *density
        tmsLengths[i] = 16 + tmsRegisters[i-1 % SWITCH_SIZE]; // TODO 
    }
    switchingTuringMachineProbability = *randomness / RANDOMNESS_SPREAD_FACTOR;
    
    euclidSteps = (tmsOutFiveBit[1] % 31) + 1 + (*density/UINT8_MAX); // TODO: Something clever
    euclidLength = tmsOutEightBit[tmsOutFiveBit[3]%SWITCH_SIZE] % 32; // TODO: Something clever
}

#endif //TUNING_MACHINE_C_
