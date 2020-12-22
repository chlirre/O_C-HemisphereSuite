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
#ifndef _TEST_SAMPLE_AND_HOLD_C_
#define _TEST_SAMPLE_AND_HOLD_C_

#include <array>
#include <unity.h> 
#include "switch.h"
#include "unittest_switch.h"
#include <iostream>

void test_function_set_channel(void) {
    std::array<uint16_t, 4> inputs = {1, 3, 5, 7};
    uint16_t* output = nullptr;
    Switch sw = Switch(&inputs, 0, &output);
    TEST_ASSERT_EQUAL(1, *output);
    sw.setChannel(1);
    TEST_ASSERT_EQUAL(3, *output);
    sw.setChannel(2);
    TEST_ASSERT_EQUAL(5, *output);
    sw.setChannel(3);
    TEST_ASSERT_EQUAL(7, *output);
    sw.setChannel(4);
    TEST_ASSERT_EQUAL(7, *output);
    sw.setChannel(5);
    TEST_ASSERT_EQUAL(7, *output);
}

void test_function_update_inputs(void) {
    std::array<uint16_t, 4> inputs = {0,0,0,0};
    uint16_t* output = nullptr;
    Switch sw = Switch(&inputs, 1, &output);
    TEST_ASSERT_EQUAL(0, *output);
    inputs[1] = 20;
    TEST_ASSERT_EQUAL(20, *output);
    inputs[1] = 42;
    TEST_ASSERT_EQUAL(42, *output);
}

#endif // _TEST_SAMPLE_AND_HOLD_C_