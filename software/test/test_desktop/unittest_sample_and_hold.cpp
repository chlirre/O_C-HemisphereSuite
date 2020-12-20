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

#include "sample_and_hold.h"
#include <unity.h> 
#include <stdint.h>
#include <stdlib.h>
#include <time.h>


void test_function_get_value(void) {
    uint32_t input = 0;
    SampleAndHold sample_and_hold = SampleAndHold(input);
    TEST_ASSERT_EQUAL(0, sample_and_hold.getValue());
}

void test_function_sample_returns_value(void) {
    uint32_t input = 0;
    SampleAndHold sample_and_hold = SampleAndHold(input);
    TEST_ASSERT_EQUAL(0, sample_and_hold.Sample());
    input = 2;
    TEST_ASSERT_EQUAL(2, sample_and_hold.Sample());
}

void test_function_get_value_same_until_sample(void) {
    uint32_t input = 0;
    SampleAndHold sample_and_hold = SampleAndHold(input);
    TEST_ASSERT_EQUAL(0, sample_and_hold.getValue());
    input = 1;
    TEST_ASSERT_EQUAL(0, sample_and_hold.getValue());
    input = 2;
    TEST_ASSERT_EQUAL(0, sample_and_hold.getValue());
    sample_and_hold.Sample();
    TEST_ASSERT_EQUAL(2, sample_and_hold.getValue());
}

void test_function_initial_value_is_sampled(void) {
    uint32_t input = 42;
    SampleAndHold sample_and_hold = SampleAndHold(input);
    TEST_ASSERT_EQUAL(42, sample_and_hold.getValue());
}

#endif // _TEST_SAMPLE_AND_HOLD_C_