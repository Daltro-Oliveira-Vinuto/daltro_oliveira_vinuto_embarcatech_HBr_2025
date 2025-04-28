#ifndef INCLUDE_LED_EMBUTIDO_H_
#define INCLUDE_LED_EMBUTIDO_H_

#include "pico/cyw43_arch.h"

void led_embutido_init();
void led_embutido_set(bool value);

#endif /* INCLUDE_LED_EMBUTIDO_H_ */