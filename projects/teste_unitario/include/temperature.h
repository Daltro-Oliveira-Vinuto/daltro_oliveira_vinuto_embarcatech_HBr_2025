#include "hardware/adc.h"

#ifndef TEMPERATURE_H_
#define TEMPERATURE_H_


void start_adc();
float adc_to_celsius(uint16_t adc_val);


#endif

