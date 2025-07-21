#include <stdio.h> // Biblioteca padrão
#include <stdlib.h>
#include <math.h> // Biblioteca de matemática (função "round" foi utilizada)
#include <string.h>

#include "pico/stdlib.h" // Biblioteca padrão pico
#include "hardware/gpio.h" // Biblioteca de GPIOs
#include "hardware/adc.h" // Biblioteca do ADC
#include "hardware/pwm.h" // Biblioteca do PWM
#include "hardware/timer.h"
#include "hardware/i2c.h"

#include "include/basic.h"
#include "include/ssd1306.h"

uint gpio_pwm = 18;     
uint gpio_pwm2 = 9;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
uint gpio_stdby = 4;

uint gpio_input1 = 20; 
uint gpio_input2 = 19;


uint gpio_input3 = 7;
uint gpio_input4= 8;




pwm_t* set_pwm(uint32_t pwm_pin, uint32_t pwm_frequency, uint16_t duty_cycle) {

  pwm_t *pwm;

  pwm = (pwm_t*)malloc(sizeof(pwm_t));

  float clkdiv; // 3.81
  uint16_t wrap = 10; //find_pwm_wrap(pwm_frequency, clkdiv);
  clkdiv = ( 1.0*clock_get_hz(clk_sys) )/((wrap)*pwm_frequency);
  uint16_t gpio_level;
  gpio_set_function(pwm_pin, GPIO_FUNC_PWM);

  uint32_t slice = pwm_gpio_to_slice_num(pwm_pin);

  pwm_set_wrap(slice, wrap);
  pwm_set_clkdiv(slice, clkdiv);

  //pwm_set_enabled(slice, true);
  gpio_level = (duty_cycle/100.0)*wrap;
  pwm_set_gpio_level(pwm_pin , gpio_level);

  //pwm_set_irq_enabled(slice, true);
  //irq_set_enabled(PWM_IRQ_WRAP, true);

  pwm->clkdiv = clkdiv;
  pwm->wrap = wrap;
  pwm->frequency = ( (125000000)/(clkdiv*wrap) );
  printf("frequency pwm: %d\n", pwm->frequency);
  pwm->slice = slice;
  pwm->gpio = pwm_pin;
  pwm->gpio_level = gpio_level;
  pwm->duty_cycle = duty_cycle;

  return pwm;
}

void set_gpio(void) {
  gpio_init(gpio_stdby);
  gpio_set_dir(gpio_stdby, GPIO_OUT);
  gpio_put(gpio_stdby, 1);

  gpio_init(gpio_input1);
  gpio_set_dir(gpio_input1, GPIO_OUT);
  gpio_put(gpio_input1, 1);

  gpio_init(gpio_input2);
  gpio_set_dir(gpio_input2, GPIO_OUT);
  gpio_put(gpio_input2, 0);


  gpio_init(gpio_input3);
  gpio_set_dir(gpio_input3, GPIO_OUT);
  gpio_put(gpio_input3, 1);

  gpio_init(gpio_input4);
  gpio_set_dir(gpio_input4, GPIO_OUT);
  gpio_put(gpio_input4, 0);
}


int main() {
  uint32_t slice, slice2;
  uint32_t pwm_frequency; // in Hz
  uint16_t duty_cycle; // in percentage % 

  pwm_t *pwm_motor_a;
  pwm_t *pwm_motor_b;

  stdio_init_all();

  set_gpio();

  pwm_frequency =40000;
  duty_cycle = 70;
  pwm_motor_a = set_pwm(gpio_pwm, pwm_frequency, duty_cycle);
  pwm_motor_b = set_pwm(gpio_pwm2, pwm_frequency, duty_cycle);


  slice = pwm_gpio_to_slice_num(gpio_pwm);
  slice2 = pwm_gpio_to_slice_num(gpio_pwm2);


  pwm_set_enabled(slice, true);
  pwm_set_enabled(slice2, true);


  gpio_put(gpio_stdby, 1);

  while (1) {

    printf("forwared direction\n");

    gpio_put(gpio_input1, 1);
    gpio_put(gpio_input2, 0);

    gpio_put(gpio_input3, 1);
    gpio_put(gpio_input4, 0);

    sleep_ms(5000);
    printf("paused\n");
    gpio_put(gpio_input1, 0);
    gpio_put(gpio_input2, 0);

    gpio_put(gpio_input3, 0);
    gpio_put(gpio_input4, 0);

    sleep_ms(1000);
    printf("backward direction...\n");
    gpio_put(gpio_input1, 0);
    gpio_put(gpio_input2, 1);

    gpio_put(gpio_input3, 0);
    gpio_put(gpio_input4, 1);
    sleep_ms(5000);

    printf("paused\n"); 
    gpio_put(gpio_input1, 0);
    gpio_put(gpio_input2, 0);

    gpio_put(gpio_input3, 0);
    gpio_put(gpio_input4, 0);

    sleep_ms(1000);

  }

  return 0;
}
