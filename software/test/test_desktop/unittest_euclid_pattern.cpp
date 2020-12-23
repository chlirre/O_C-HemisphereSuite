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
#ifndef _TEST_EUCLID_PATTERN_C_
#define _TEST_EUCLID_PATTERN_C_

#include "euclidpattern.h"
#include "unittest_euclid_pattern.h"
#include "clockable.h"
#include <unity.h> 
#include <stdint.h>
#include <stdlib.h>
#include <iostream>

class ClockListener : public Clockable {
    public:
        void clock() {
            calls++;
        };
        uint32_t calls;        
};

void test_function_euclid_clock(void) {
    ClockListener cl = ClockListener();
    cl.calls = 0;
    uint32_t length = 16;
    uint32_t steps = 4;
    uint32_t rotation = 0;
    EuclidPattern euclid = EuclidPattern(&length, &steps, &rotation, cl);
    TEST_ASSERT_EQUAL(0, cl.calls);
    euclid.clock();
    TEST_ASSERT_EQUAL(1, cl.calls);
    euclid.clock();
    TEST_ASSERT_EQUAL(1, cl.calls);
    euclid.clock();
    TEST_ASSERT_EQUAL(1, cl.calls);
    euclid.clock();
    TEST_ASSERT_EQUAL(1, cl.calls);
    euclid.clock();
    TEST_ASSERT_EQUAL(2, cl.calls);
    euclid.clock();
    TEST_ASSERT_EQUAL(2, cl.calls);
    euclid.clock();
    TEST_ASSERT_EQUAL(2, cl.calls);
    euclid.clock();
    TEST_ASSERT_EQUAL(2, cl.calls);
    euclid.clock();
    TEST_ASSERT_EQUAL(3, cl.calls);
}

void test_function_total_steps(void) {
    uint32_t length = 2;
    uint32_t steps = 1;
    uint32_t rotation = 0;
    for (length; length < 16; length++) {
        steps = 1;
        for (steps; steps < length + 1; steps++) {
            ClockListener cl = ClockListener();
            cl.calls = 0;
            EuclidPattern euclid = EuclidPattern(&length, &steps, &rotation, cl);
            cl.calls = 0;
            for (int i = 0; i < length; i++) {
                euclid.clock();
            }
            TEST_ASSERT_EQUAL(steps, cl.calls);
        }
    }
}

void test_function_update_steps(void) {
    uint32_t length = 8;
    uint32_t steps = 1;
    uint32_t rotation = 0;
    ClockListener cl = ClockListener();
    cl.calls = 0;
    EuclidPattern euclid = EuclidPattern(&length, &steps, &rotation, cl);
    euclid.clock();
    TEST_ASSERT_EQUAL(1, cl.calls);
    euclid.clock();
    TEST_ASSERT_EQUAL(1, cl.calls);
    euclid.clock();
    TEST_ASSERT_EQUAL(1, cl.calls);
    euclid.clock();
    TEST_ASSERT_EQUAL(1, cl.calls);
    steps = 8;
    euclid.clock();
    TEST_ASSERT_EQUAL(2, cl.calls);
    euclid.clock();
    TEST_ASSERT_EQUAL(3, cl.calls);
    euclid.clock();
    TEST_ASSERT_EQUAL(4, cl.calls);
    euclid.clock();
    TEST_ASSERT_EQUAL(5, cl.calls);
}

void test_function_update_length(void) {
    uint32_t length = 8;
    uint32_t steps = 3;
    uint32_t rotation = 0;
    ClockListener cl = ClockListener();
    cl.calls = 0;
    EuclidPattern euclid = EuclidPattern(&length, &steps, &rotation, cl);
    // 100|100|10
    // 100|010|00100
    euclid.clock();
    TEST_ASSERT_EQUAL(1, cl.calls);
    euclid.clock();
    TEST_ASSERT_EQUAL(1, cl.calls);
    euclid.clock();
    TEST_ASSERT_EQUAL(1, cl.calls);
    length = 11;
    euclid.clock();
    TEST_ASSERT_EQUAL(1, cl.calls);
    euclid.clock();
    TEST_ASSERT_EQUAL(2, cl.calls);
    euclid.clock();
    TEST_ASSERT_EQUAL(2, cl.calls);
    length = 8;
    euclid.clock();
    TEST_ASSERT_EQUAL(3, cl.calls);
    euclid.clock();
    TEST_ASSERT_EQUAL(3, cl.calls);
}

void test_function_zero_steps(void) {
    uint32_t length = 16;
    uint32_t steps = 0;
    uint32_t rotation = 0;
    ClockListener cl = ClockListener();
    cl.calls = 0;
    EuclidPattern euclid = EuclidPattern(&length, &steps, &rotation, cl);
    for (int i = 0; i < length; i++) {
        euclid.clock();
    }
    TEST_ASSERT_EQUAL(0, cl.calls);
}

void test_function_steps_above_length(void) {
    uint32_t length = 8;
    uint32_t steps = 10;
    uint32_t rotation = 0;
    ClockListener cl = ClockListener();
    cl.calls = 0;
    EuclidPattern euclid = EuclidPattern(&length, &steps, &rotation, cl);
    for (int i = 0; i < length; i++) {
        euclid.clock();
    }
    TEST_ASSERT_EQUAL(8, cl.calls);
}

void test_function_length_above_length(void) {
    uint32_t length = 42; // MAX = 32
    uint32_t steps = 1;
    uint32_t rotation = 0;
    ClockListener cl = ClockListener();
    cl.calls = 0;
    EuclidPattern euclid = EuclidPattern(&length, &steps, &rotation, cl);
    euclid.clock();
    TEST_ASSERT_EQUAL(1, cl.calls);
    for (int i = 0; i < 31; i++) {
        euclid.clock();
    }
    TEST_ASSERT_EQUAL(1, cl.calls);
}

void test_function_zero_length(void) {
    uint32_t length = 0; // MIN = 2
    uint32_t steps = 1;
    uint32_t rotation = 0;
    ClockListener cl = ClockListener();
    cl.calls = 0;
    EuclidPattern euclid = EuclidPattern(&length, &steps, &rotation, cl);
    euclid.clock();
    TEST_ASSERT_EQUAL(1, cl.calls);
    euclid.clock();
    TEST_ASSERT_EQUAL(1, cl.calls);
    euclid.clock();
    TEST_ASSERT_EQUAL(2, cl.calls);
}

void test_function_euclid_rotated(void) {
    uint32_t length = 8;
    uint32_t steps = 1;
    uint32_t rotation = 2;
    ClockListener cl = ClockListener();
    cl.calls = 0;
    EuclidPattern euclid = EuclidPattern(&length, &steps, &rotation, cl);
    euclid.clock();
    TEST_ASSERT_EQUAL(0, cl.calls);
    euclid.clock();
    TEST_ASSERT_EQUAL(0, cl.calls);
    euclid.clock();
    TEST_ASSERT_EQUAL(1, cl.calls);
    euclid.clock();
    TEST_ASSERT_EQUAL(1, cl.calls);
    euclid.clock();
    TEST_ASSERT_EQUAL(1, cl.calls);
    euclid.clock();
    TEST_ASSERT_EQUAL(1, cl.calls);
    euclid.clock();
    TEST_ASSERT_EQUAL(1, cl.calls);
    euclid.clock();
    TEST_ASSERT_EQUAL(1, cl.calls);
}

#endif // _TEST_EUCLID_PATTERN_C_
