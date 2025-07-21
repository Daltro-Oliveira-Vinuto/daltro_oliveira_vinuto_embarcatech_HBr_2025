#include "stdio.h"
#include "stdlib.h"

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/clocks.h"
#include "hardware/pwm.h"
#include "hardware/adc.h"
#include "hardware/timer.h"


#ifndef __BASIC_H__
#define __BASIC_H__


typedef struct pwm {
  float clkdiv;
  uint16_t wrap;
  uint32_t frequency;
  uint16_t duty_cycle;
  uint32_t slice;
  uint32_t gpio;
  uint16_t gpio_level;

} pwm_t;


#endif // __BASIC_H__    