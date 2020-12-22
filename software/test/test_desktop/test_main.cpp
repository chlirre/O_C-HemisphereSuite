#include <unity.h> 
#include "unittest_turing_machine.h"
#include "unittest_sample_and_hold.h"
#include "unittest_switch.h"

int main(int argc, char **argv) {
    UNITY_BEGIN();

    // Switch
    RUN_TEST(test_function_set_channel);
    RUN_TEST(test_function_update_inputs);

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