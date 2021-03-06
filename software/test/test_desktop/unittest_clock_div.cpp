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
#ifndef _TEST_CLOCK_DIV_C_
#define _TEST_CLOCK_DIV_C_

#include <unity.h>
#include <stdint.h> 

#include "unittest_clock_div.h"
#include "clock_div.h"

class ClockListener : public Clockable {
    public:
        void clock() {
            calls++;
        };
        uint32_t calls;        
};

void test_function_clock(void) {
    uint8_t division = 2;
    ClockListener cl = ClockListener();
    cl.calls = 0;
    ClockDiv clock_div = ClockDiv(division, cl);
    TEST_ASSERT_EQUAL(0, cl.calls);
    clock_div.clock();
    TEST_ASSERT_EQUAL(0, cl.calls);
    clock_div.clock();
    TEST_ASSERT_EQUAL(1, cl.calls);
}

void test_function_change_division(void) {
    uint8_t division = 2;
    ClockListener cl = ClockListener();
    cl.calls = 0;
    ClockDiv clock_div = ClockDiv(division, cl);
    TEST_ASSERT_EQUAL(0, cl.calls);
    clock_div.clock();
    TEST_ASSERT_EQUAL(0, cl.calls);
    division = 4;
    clock_div.clock();
    TEST_ASSERT_EQUAL(0, cl.calls);
    clock_div.clock();
    TEST_ASSERT_EQUAL(0, cl.calls);
    clock_div.clock();
    TEST_ASSERT_EQUAL(1, cl.calls);
}

#endif // _TEST_CLOCK_DIV_C_
