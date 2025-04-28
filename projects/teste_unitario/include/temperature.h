
#ifndef TEMPERATURE_H_
#define TEMPERATURE_H_

#include "hardware/adc.h"

void start_adc();
float adc_to_celsius(uint16_t adc_val);


#endif

