#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "temperature.h"


int main() {
	float temp_celsius;
	float adc_output;

	stdio_init_all();

	start_adc();



	while(true) {
		
		adc_output = adc_read(); //891 -> 20.015
		printf("ADC output: %.3f\n", adc_output);
		temp_celsius = adc_to_celsius(adc_output);
		printf("Temperature °C: %.3f\n", temp_celsius);
		sleep_ms(500);


	}

	return 0;
}




