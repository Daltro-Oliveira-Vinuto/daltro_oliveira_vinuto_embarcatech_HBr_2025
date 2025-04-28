#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "temperature.h"


void start_adc() {
	adc_init();
	adc_set_temp_sensor_enabled(true);
	adc_select_input(4);

}


float adc_to_celsius(uint16_t adc_val) {
	float temp;

	temp = 27.0f - ( ( ( adc_val*(3.3/ 4095) ) - 0.706f)/0.001721f );

	//temp = 27 - (adc_val-0.706)/0.001721;

	return temp;
}



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




