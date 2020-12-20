#include <unity.h> 
#include "unittest_turing_machine.h"
#include "unittest_sample_and_hold.h"
#include "unittest_switch.h"
#include "unittest_clock_div.h"

int main(int argc, char **argv) {
    UNITY_BEGIN();

<<<<<<< 2d0524a68f6029791ba610b7dd21b1a33dd6d2b0
    // Switch
    RUN_TEST(test_function_set_channel);
    RUN_TEST(test_function_update_inputs);
=======
    // Clock Div
    RUN_TEST(test_function_clock);
    RUN_TEST(test_function_change_division);
>>>>>>> Reorder

    // Turing Machine
    RUN_TEST(test_function_get_register);
    RUN_TEST(test_function_cycle);
    RUN_TEST(test_function_length);
    RUN_TEST(test_function_probability_100);
    RUN_TEST(test_function_set_probability_50);
    RUN_TEST(test_function_set_probability_0);
    RUN_TEST(test_function_probability_0);
    RUN_TEST(test_function_scaled_values);

    // Sample n Hold
    RUN_TEST(test_function_get_value);
    RUN_TEST(test_function_sample_returns_value);
    RUN_TEST(test_function_get_value_same_until_sample);
    RUN_TEST(test_function_initial_value_is_sampled);

    UNITY_END();
    return 0;
}
