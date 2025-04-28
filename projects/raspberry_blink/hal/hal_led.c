#include "hal_led.h"
#include "led_embutido.h"
#include "pico/stdlib.h"

void hal_led_init() {
    led_embutido_init();
}

void hal_led_toggle() {
    led_embutido_set(true);
    sleep_ms(500);
    led_embutido_set(false);
    sleep_ms(500);
}