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


#ifndef TUNING_MACHINE_H_
#define TUNING_MACHINE_H_

#include <stdint.h>
#include "triggable.h"
#include "braids_quantizer.h"
#include "braids_quantizer_scales.h"
#include "turing_machine.h"
#include "clock_div.h"
#include "switch.h"
#include "sample_and_hold.h"
#include "euclidpattern.h"

const uint8_t MIN_EUCLID_DIVISION = 1;
const uint8_t MAX_EUCLID_DIVISION = 4;
const uint8_t DEFAULT_TURING_MACHINE_DIVISION = 16;

class TriggerSpy: public Triggable {
    public:
        TriggerSpy(Triggable &_t) : t(_t) {};
        void trig() {
            was_trigged = true;
            t.trig();
        };
        bool wasTrigged() {
            return was_trigged;
        };
        void reset() {
            was_trigged = false;
        };
    
    private:
        Triggable &t;
        bool was_trigged = false;
};

typedef uint32_t (*constrain_fn)(uint32_t val, uint32_t min, uint32_t max);

// I will probably hate myself for this naming, but I couldn't help myself.
// TuningMachine utilises multiple Turing Machines to output a melody 
// - random, loopable and everything inbetween.
class TuningMachine: public Triggable {
    
    public: 
        TuningMachine(
            random_fn _random,
            constrain_fn _constrain,
            // TODO: Idea, share the quantizer and scale with the other tuning machines including note mask
            braids::Quantizer* _quantizer, 
            braids::Scale* _scale,
            // But density and randomness are unique per tuning machine instance
            uint8_t* _density,
            uint8_t* _randomness,
            int32_t* _quantized_pitch_out
        );
        void trig();
        bool getAndClearTriggered();

    private:
        void trigAll();
        void updateAll();

        random_fn random;
        constrain_fn constrain;
        braids::Quantizer* tm_quantizer;
        braids::Scale* tm_scale;
        uint8_t* density;
        uint8_t* randomness;
        int32_t* quantized_pitch_out = 0;

        uint16_t sampleAndHoldOut = 0;        
        uint16_t* switchOut = nullptr;

        uint32_t euclidLength = 16;
        uint32_t euclidSteps = 1;
        uint32_t euclidRotation = 0;

        uint8_t euclidDiv = MIN_EUCLID_DIVISION;
        
        std::array<uint16_t, SWITCH_SIZE> tmsOutFiveBit = {0, 0, 0, 0};
        std::array<uint16_t, SWITCH_SIZE> tmsOutEightBit = {0, 0, 0, 0};
        std::array<uint8_t, SWITCH_SIZE> tmsLengths = {0, 0, 0, 0};
        std::array<uint16_t, SWITCH_SIZE> tmsRegisters = {random(0, UINT16_MAX), random(0, UINT16_MAX), random(0, UINT16_MAX), random(0, UINT16_MAX)};
        std::array<uint8_t, SWITCH_SIZE> tmsProbability = {0, 0, 0, 0};
        std::array<uint8_t, SWITCH_SIZE> tmsDivision = {DEFAULT_TURING_MACHINE_DIVISION, DEFAULT_TURING_MACHINE_DIVISION, DEFAULT_TURING_MACHINE_DIVISION, DEFAULT_TURING_MACHINE_DIVISION}; 

        uint8_t switchingTuringMachineLength = 16;
        uint8_t switchingTuringMachineProbability = 0;
        uint16_t switchingTuringMachineScaledFiveBitOut = 0;
        uint16_t switchingTuringMachineScaledEightBitOut = 0;
        uint8_t switchingTuringMachineDiv = 1;
        uint16_t switchingTuringMachineRegister = random(0, UINT16_MAX);

        // Triggable instrances        
        TuringMachine tm1 = TuringMachine(random, &tmsRegisters[0], &tmsLengths[0], &tmsProbability[0], &tmsOutFiveBit[0], &tmsOutEightBit[0]);
        TuringMachine tm2 = TuringMachine(random, &tmsRegisters[1], &tmsLengths[1], &tmsProbability[1], &tmsOutFiveBit[1], &tmsOutEightBit[1]);
        TuringMachine tm3 = TuringMachine(random, &tmsRegisters[2], &tmsLengths[2], &tmsProbability[2], &tmsOutFiveBit[2], &tmsOutEightBit[2]);
        TuringMachine tm4 = TuringMachine(random, &tmsRegisters[3], &tmsLengths[3], &tmsProbability[3], &tmsOutFiveBit[3], &tmsOutEightBit[3]);
        Switch fourChannelSwitch = Switch(&tmsOutFiveBit, 0, &switchOut);
        SampleAndHold sampleAndHold = SampleAndHold(switchOut, &sampleAndHoldOut);        
        TriggerSpy sampleAndHoldSpy = TriggerSpy(sampleAndHold);
        EuclidPattern euclid = EuclidPattern(&euclidLength, &euclidSteps, &euclidRotation, sampleAndHoldSpy);
        
        TuringMachine switchingTuringMachine  = TuringMachine(
            random, 
            &switchingTuringMachineRegister, 
            &switchingTuringMachineLength, 
            &switchingTuringMachineProbability, 
            &switchingTuringMachineScaledFiveBitOut, 
            &switchingTuringMachineScaledEightBitOut
        );

        // Clock divs
        std::array<ClockDiv, SWITCH_SIZE> tmsClockDiv = {ClockDiv(tmsDivision[0], tm1), ClockDiv(tmsDivision[1], tm2), ClockDiv(tmsDivision[2], tm3), ClockDiv(tmsDivision[3], tm4)};
        ClockDiv switchingTMClockDiv = ClockDiv(switchingTuringMachineDiv, switchingTuringMachine);
        ClockDiv euclidClockDiv = ClockDiv(euclidDiv, euclid);
};

#endif //TUNING_MACHINE_H_
