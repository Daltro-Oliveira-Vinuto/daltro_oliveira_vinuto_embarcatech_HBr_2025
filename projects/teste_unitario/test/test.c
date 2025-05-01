#include <stdio.h>
#include "pico/stdlib.h"
#include "temperature.h"
#include "Unity/unity.h"

void setUp() {


}

void tearDown() {

    
}

void test_sensor_temperature() {
    //891 -> 20.015
    float correct_temperature = 20.015;
    uint16_t  adc_readed = 891;
    float readed_temperature = adc_to_celsius(adc_readed);

    TEST_ASSERT_FLOAT_WITHIN(0.1f, readed_temperature, correct_temperature);
}


int main(void) {
    stdio_init_all();



    while (true) {
        UNITY_BEGIN();

        RUN_TEST(test_sensor_temperature);
        sleep_ms(500);

    }


    return 0;
}