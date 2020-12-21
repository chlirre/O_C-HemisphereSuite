/*
 Copyright (c) 2014-present PlatformIO <contact@platformio.org>
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
    http://www.apache.org/licenses/LICENSE-2.0
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
**/
#ifndef _TEST_TURING_MACHINE_C_
#define _TEST_TURING_MACHINE_C_

#include "unittest_turing_machine.h"
#include "turing_machine.h"
#include <unity.h> 
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

uint32_t random_function(uint32_t min, uint32_t max) {
    srand((unsigned) time(NULL));
    return (rand() % (max-min)) + min;
};

uint32_t non_random_function_min(uint32_t min, uint32_t max) {
    return min;
};

uint32_t non_random_function_max(uint32_t min, uint32_t max) {
    return max;
};

TuringMachine turing_machine(random_function, 0b0, 0, 0);

void beforeEach(void) {
    turing_machine = TuringMachine(random_function, 0b0001110001110011, 16, 0);
}

void test_function_get_register(void) {
    beforeEach();
    TEST_ASSERT_EQUAL(turing_machine.getRegister(), 0b0001110001110011);
}

void test_function_cycle(void) {
    beforeEach();
    turing_machine.Cycle();
    TEST_ASSERT_EQUAL(turing_machine.getRegister(), 0b0011100011100110);
}

void test_function_length(void) {
    beforeEach();
    turing_machine.setLength(3);
    TEST_ASSERT_EQUAL(turing_machine.getRegister(), 0b0001110001110011);
    turing_machine.Cycle();
    TEST_ASSERT_EQUAL(turing_machine.getRegister(), 0b0011100011100110);
    turing_machine.Cycle();
    TEST_ASSERT_EQUAL(turing_machine.getRegister(), 0b0111000111001101);
    turing_machine.setLength(5);
    turing_machine.Cycle();
    TEST_ASSERT_EQUAL(turing_machine.getRegister(), 0b1110001110011010);
    turing_machine.Cycle();
    TEST_ASSERT_EQUAL(turing_machine.getRegister(), 0b1100011100110101);
    turing_machine.Cycle();
    TEST_ASSERT_EQUAL(turing_machine.getRegister(), 0b1000111001101011);
}

void test_function_probability_100(void) {
    beforeEach();
    turing_machine.setProbability(100);
    turing_machine.Cycle();
    TEST_ASSERT_EQUAL(0b0011100011100111, turing_machine.getRegister());
    turing_machine.Cycle();
    TEST_ASSERT_EQUAL(0b0111000111001111, turing_machine.getRegister());
    turing_machine.Cycle();
    TEST_ASSERT_EQUAL(0b1110001110011111, turing_machine.getRegister());
    turing_machine.Cycle();
    TEST_ASSERT_EQUAL(0b1100011100111110, turing_machine.getRegister());
    turing_machine.Cycle();
    TEST_ASSERT_EQUAL(0b1000111001111100, turing_machine.getRegister());
}

void test_function_set_probability_50(void) {
    beforeEach();
    turing_machine = TuringMachine(non_random_function_min, 0b0011001100110011, 16, 0);
    turing_machine.setProbability(50);
    turing_machine.Cycle();
    TEST_ASSERT_EQUAL(0b0110011001100111, turing_machine.getRegister());
    turing_machine.Cycle();
    TEST_ASSERT_EQUAL(0b1100110011001111, turing_machine.getRegister());
    turing_machine.Cycle();
    TEST_ASSERT_EQUAL(0b1001100110011110, turing_machine.getRegister());
}

void test_function_probability_50(void) {
    beforeEach();
    turing_machine = TuringMachine(non_random_function_min, 0b0011001100110011, 16, 50);
    turing_machine.Cycle();
    TEST_ASSERT_EQUAL(0b0110011001100111, turing_machine.getRegister());
    turing_machine.Cycle();
    TEST_ASSERT_EQUAL(0b1100110011001111, turing_machine.getRegister());
    turing_machine.Cycle();
    TEST_ASSERT_EQUAL(0b1001100110011110, turing_machine.getRegister());
}

void test_function_set_probability_0(void) {
    beforeEach();
    turing_machine = TuringMachine(non_random_function_min, 0b0011001100110011, 16, 0);
    turing_machine.Cycle();
    TEST_ASSERT_EQUAL(0b0110011001100110, turing_machine.getRegister());
    turing_machine.Cycle();
    TEST_ASSERT_EQUAL(0b1100110011001100, turing_machine.getRegister());
    turing_machine.Cycle();
    TEST_ASSERT_EQUAL(0b1001100110011001, turing_machine.getRegister());
}

void test_function_probability_0(void) {
    beforeEach();
    turing_machine = TuringMachine(non_random_function_min, 0b0011001100110011, 16, 50);
    turing_machine.setProbability(0);
    turing_machine.Cycle();
    TEST_ASSERT_EQUAL(0b0110011001100110, turing_machine.getRegister());
    turing_machine.Cycle();
    TEST_ASSERT_EQUAL(0b1100110011001100, turing_machine.getRegister());
    turing_machine.Cycle();
    TEST_ASSERT_EQUAL(0b1001100110011001, turing_machine.getRegister());
}

void test_function_scaled_values() {
    beforeEach();
    turing_machine = TuringMachine(non_random_function_min, 0b0011001100110011, 16, 0);
    TEST_ASSERT_EQUAL(19/31, turing_machine.getScaled5BitValue());
    TEST_ASSERT_EQUAL(51/255, turing_machine.getScaled8BitValue());
    turing_machine = TuringMachine(non_random_function_min, 0b0011001111110000, 16, 0);
    TEST_ASSERT_EQUAL(16/31, turing_machine.getScaled5BitValue());
    TEST_ASSERT_EQUAL(240/255, turing_machine.getScaled8BitValue());
    turing_machine = TuringMachine(non_random_function_min, 0b0011001111111111, 16, 0);
    TEST_ASSERT_EQUAL(31/31, turing_machine.getScaled5BitValue());
    TEST_ASSERT_EQUAL(255/255, turing_machine.getScaled8BitValue());
    turing_machine = TuringMachine(non_random_function_min, 0b0011001100000000, 16, 0);
    TEST_ASSERT_EQUAL(0/31, turing_machine.getScaled5BitValue());
    TEST_ASSERT_EQUAL(0/255, turing_machine.getScaled8BitValue());
}

#endif // _TEST_TURING_MACHINE_C_