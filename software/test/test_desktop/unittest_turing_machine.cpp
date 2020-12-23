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

uint8_t length = 0;
uint8_t probability = 0;
double fiveBit = 0.0;
double eightBit = 0.0;

void test_function_get_register(void) {
    length = 16;
    probability = 0;
    TuringMachine turing_machine(random_function, 0b0001110001110011, &length, &probability, &fiveBit, &eightBit);
    TEST_ASSERT_EQUAL(0b10011 / 0b11111, fiveBit);
    TEST_ASSERT_EQUAL(0b01110011 / 0b11111111, eightBit);
}

void test_function_cycle(void) {
    length = 16;
    probability = 0;
    TuringMachine turing_machine(random_function, 0b0001110001110011, &length, &probability, &fiveBit, &eightBit);
    turing_machine.clock();
    TEST_ASSERT_EQUAL(0b00110 / 0b11111, fiveBit);
    TEST_ASSERT_EQUAL(0b11100110 / 0b11111111, eightBit);
}

void test_function_length(void) {
    length = 16;
    probability = 0;
    TuringMachine turing_machine(random_function, 0b0001110001110011, &length, &probability, &fiveBit, &eightBit);
    length = 3;
    TEST_ASSERT_EQUAL(0b10011 / 0b11111, fiveBit);
    TEST_ASSERT_EQUAL(0b01110011 / 0b11111111, eightBit);
    turing_machine.clock();
    TEST_ASSERT_EQUAL(0b00110 / 0b11111, fiveBit);
    TEST_ASSERT_EQUAL(0b11100110 / 0b11111111, eightBit);
    turing_machine.clock();
    TEST_ASSERT_EQUAL(0b01101 / 0b11111, fiveBit);
    TEST_ASSERT_EQUAL(0b11001101 / 0b11111111, eightBit);
    length = 5;
    turing_machine.clock();
    TEST_ASSERT_EQUAL(0b11010 / 0b11111, fiveBit);
    TEST_ASSERT_EQUAL(0b10011010 / 0b11111111, eightBit);
    turing_machine.clock();
    TEST_ASSERT_EQUAL(0b10101 / 0b11111, fiveBit);
    TEST_ASSERT_EQUAL(0b00110101 / 0b11111111, eightBit);
    turing_machine.clock();
    TEST_ASSERT_EQUAL(0b01011 / 0b11111, fiveBit);
    TEST_ASSERT_EQUAL(0b01101011 / 0b11111111, eightBit);
}

void test_function_probability_100(void) {
    length = 16;
    probability = 0;
    TuringMachine turing_machine(random_function, 0b0001110001110011, &length, &probability, &fiveBit, &eightBit);
    probability = 100;
    turing_machine.clock();
    TEST_ASSERT_EQUAL(0b00111 / 0b11111, fiveBit);
    TEST_ASSERT_EQUAL(0b11100111 / 0b11111111, eightBit);
    turing_machine.clock();
    TEST_ASSERT_EQUAL(0b01111 / 0b11111, fiveBit);
    TEST_ASSERT_EQUAL(0b11001111 / 0b11111111, eightBit);
    turing_machine.clock();
    TEST_ASSERT_EQUAL(0b11111 / 0b11111, fiveBit);
    TEST_ASSERT_EQUAL(0b10011111 / 0b11111111, eightBit);
    turing_machine.clock();    
    TEST_ASSERT_EQUAL(0b11110 / 0b11111, fiveBit);
    TEST_ASSERT_EQUAL(0b00111110 / 0b11111111, eightBit);
    turing_machine.clock();
    TEST_ASSERT_EQUAL(0b11100 / 0b11111, fiveBit);
    TEST_ASSERT_EQUAL(0b01111100 / 0b11111111, eightBit);
}

void test_function_set_probability_50(void) {
    length = 16;
    probability = 0;
    TuringMachine turing_machine(non_random_function_min, 0b0011001100110011, &length, &probability, &fiveBit, &eightBit);
    probability = 50;
    turing_machine.clock();
    TEST_ASSERT_EQUAL(0b00111 / 0b11111, fiveBit);
    TEST_ASSERT_EQUAL(0b01100111 / 0b11111111, eightBit);
    turing_machine.clock();
    TEST_ASSERT_EQUAL(0b01111 / 0b11111, fiveBit);
    TEST_ASSERT_EQUAL(0b11001111 / 0b11111111, eightBit);
    turing_machine.clock();
    TEST_ASSERT_EQUAL(0b11110 / 0b11111, fiveBit);
    TEST_ASSERT_EQUAL(0b10011110 / 0b11111111, eightBit);
}

void test_function_probability_50(void) {
    length = 16;
    probability = 50;
    TuringMachine turing_machine(non_random_function_min, 0b0011001100110011, &length, &probability, &fiveBit, &eightBit);
    turing_machine.clock();
    TEST_ASSERT_EQUAL(0b00111 / 0b11111, fiveBit);
    TEST_ASSERT_EQUAL(0b01100111 / 0b11111111, eightBit);
    turing_machine.clock();
    TEST_ASSERT_EQUAL(0b01111 / 0b11111, fiveBit);
    TEST_ASSERT_EQUAL(0b11001111 / 0b11111111, eightBit);
    turing_machine.clock();
    TEST_ASSERT_EQUAL(0b11110 / 0b11111, fiveBit);
    TEST_ASSERT_EQUAL(0b10011110 / 0b11111111, eightBit);
}

void test_function_set_probability_0(void) {
    length = 16;
    probability = 50;
    TuringMachine turing_machine(non_random_function_min, 0b0011001100110011, &length, &probability, &fiveBit, &eightBit);
    probability = 0;
    turing_machine.clock();
    TEST_ASSERT_EQUAL(0b00110 / 0b11111, fiveBit);
    TEST_ASSERT_EQUAL(0b01100110 / 0b11111111, eightBit);
    turing_machine.clock();
    TEST_ASSERT_EQUAL(0b01100 / 0b11111, fiveBit);
    TEST_ASSERT_EQUAL(0b11001100 / 0b11111111, eightBit);
    turing_machine.clock();
    TEST_ASSERT_EQUAL(0b11001 / 0b11111, fiveBit);
    TEST_ASSERT_EQUAL(0b10011001 / 0b11111111, eightBit);    
}

void test_function_probability_0(void) {
    length = 16;
    probability = 0;
    TuringMachine turing_machine(non_random_function_min, 0b0011001100110011, &length, &probability, &fiveBit, &eightBit);
    turing_machine.clock();
    TEST_ASSERT_EQUAL(0b00110 / 0b11111, fiveBit);
    TEST_ASSERT_EQUAL(0b01100110 / 0b11111111, eightBit);
    turing_machine.clock();
    TEST_ASSERT_EQUAL(0b01100 / 0b11111, fiveBit);
    TEST_ASSERT_EQUAL(0b11001100 / 0b11111111, eightBit);
    turing_machine.clock();
    TEST_ASSERT_EQUAL(0b11001 / 0b11111, fiveBit);
    TEST_ASSERT_EQUAL(0b10011001 / 0b11111111, eightBit);  
}

#endif // _TEST_TURING_MACHINE_C_
