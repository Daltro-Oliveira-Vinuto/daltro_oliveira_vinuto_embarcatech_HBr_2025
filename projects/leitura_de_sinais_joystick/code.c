
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "inc/ssd1306.h"
#include "hardware/adc.h"


//#include "pico/cyw43_arch.h"

#define BUTTON_A 5
#define BUTTON_B 6
#define LED_RED 13
#define LED_GREEN 11
#define LED_BLUE 12

#define OFF 0
#define ON 1

#define VRX_PIN 27
#define VRY_PIN 26
#define SW_PIN 22

const uint I2C_SDA = 14;
const uint I2C_SCL = 15;

volatile uint time_now = 0;
volatile uint total_pressed = 0;
volatile bool time_started = false;

void set_color(bool red, bool green, bool blue) {
  gpio_put(LED_RED, red);
  gpio_put(LED_GREEN, green);
  gpio_put(LED_BLUE, blue);
}

void gpio_irq_handler(uint gpio, uint32_t event_mask) {
  if (gpio == BUTTON_A) {
    set_color(0,0,0);
    set_color(0, 0, 1);
    time_now = 9;
    total_pressed = 0;
  }
  else if (gpio == BUTTON_B){
   set_color(0,0,0);
   set_color(0,1,0);
   if (time_now > 0) {
    total_pressed+= 1;
   }
 }
}

bool repeating_timer_callback(struct repeating_timer *t) {

  if (time_now > 0) {
    time_now = time_now - 1;

    return true;
  } else {
    time_started = false;
    return false;
  }
}

float adc_to_temperature(uint16_t adc) {
  const float conversion_factor = 3.3f/(1 << 12);
  float voltage = adc* conversion_factor;
  float temperature = 27.0f - (voltage - 0.706f) / 0.001721f;
  return temperature;
}

/*
void start_adc() {
  adc_init();
  adc_set_temp_sensor_enabled(true);
  adc_select_input(4);
}
*/

void start_adc_joystick() {
  adc_init();
  adc_gpio_init(VRX_PIN);
  adc_gpio_init(VRY_PIN);

  gpio_init(SW_PIN);
  gpio_set_dir(SW_PIN, GPIO_IN);
  gpio_pull_up(SW_PIN);
}

int main() {
  char string_vrx[5];
  char string_vry[5];
  uint16_t vrx_value;
  uint16_t vry_value;

  char string_int_temperature[4];
  float float_temperature = 0.0;
  int int_temperature = 0;

  char string_total_pressed[3] = "ok";
  char string_time_now[3];
  uint wait_time = 1000;
  struct repeating_timer timer;


  stdio_init_all();
  start_adc_joystick();

  gpio_init(BUTTON_A);
  gpio_set_dir(BUTTON_A, GPIO_IN);
  gpio_pull_up(BUTTON_A);

  gpio_init(BUTTON_B);
  gpio_set_dir(BUTTON_B, GPIO_IN);
  gpio_pull_up(BUTTON_B);

  gpio_init(LED_RED);
  gpio_set_dir(LED_RED, GPIO_OUT);

  gpio_init(LED_GREEN);
  gpio_set_dir(LED_GREEN, GPIO_OUT);
  gpio_put(LED_GREEN, 0);

  gpio_init(LED_BLUE);
  gpio_set_dir(LED_BLUE, GPIO_OUT);
  gpio_put(LED_BLUE, 0);

  printf("Hello led button!\n");

  //gpio_put(LED_BLUE, 1);
  //gpio_put(LED_GREEN, 1);
  //gpio_put(LED_RED, 1);

  gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
  gpio_set_irq_enabled(BUTTON_B, GPIO_IRQ_EDGE_FALL, true);


 // Inicialização do i2c
  i2c_init(i2c1, ssd1306_i2c_clock * 1000);
  gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
  gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
  gpio_pull_up(I2C_SDA);
  gpio_pull_up(I2C_SCL);

  // Processo de inicialização completo do OLED SSD1306
  ssd1306_init();

  // Preparar área de renderização para o display (ssd1306_width pixels por ssd1306_n_pages páginas)
  struct render_area frame_area = {
      start_column : 0,
      end_column : ssd1306_width - 1,
      start_page : 0,
      end_page : ssd1306_n_pages - 1
  };

  calculate_render_area_buffer_length(&frame_area);

  // zera o display inteiro
  uint8_t ssd[ssd1306_buffer_length];
  memset(ssd, 0, ssd1306_buffer_length);
  render_on_display(ssd, &frame_area);

  /*
  char *text[] = {
      "World.!   ",
      "",
      "is bigger!..   ",
      "",
      "I love money",
      (total_pressed+"0")};

  int y = 0;
  for (uint i = 0; i < count_of(text); i++)
  {
      ssd1306_draw_string(ssd, 5, y, text[i]);
      y += 8;
  }
  render_on_display(ssd, &frame_area);
  */


  while (1) {

    if (time_now == 9 && !time_started) {
      add_repeating_timer_ms(wait_time, repeating_timer_callback, NULL, &timer);
      time_started = true;
    } 

    /*
    if (!gpio_get(BUTTON_A) && !gpio_get(BUTTON_B)) {
      set_color(1,1, 1);

    }
    
    else if(!gpio_get(BUTTON_A)) {
      set_color(0,0,1);
    }

    else if(!gpio_get(BUTTON_B)) {
      set_color(0, 1, 0);
    } else {
      set_color(0, 0, 0);
    }
    */

    memset(string_total_pressed, 0, sizeof(string_total_pressed));
    sprintf(string_total_pressed, "%-3d", total_pressed);
    memset(string_time_now, 0, sizeof(string_time_now));
    sprintf(string_time_now, "%-3d", time_now);

    sprintf(string_int_temperature, "%-3d", int_temperature);

    sprintf(string_vrx, "%-6d", vrx_value);
    sprintf(string_vry, "%-6d", vry_value);


    /*
    if (total_pressed < 255) {
      strcpy(string_total_pressed,"0");
    }
    else {
      strcpy(string_total_pressed, "!");
    }
    */

    /*
    char *text[] = {
      "Tempo atual:",
      string_time_now,
      "button b: ",
      string_total_pressed,
      "temperature: ",
      string_int_temperature
      };
    */
    char *text[] = {
      "VRX:",
      string_vrx,
      "VRY: ",
      string_vry
      };

    int y = 0;
    for (uint i = 0; i < count_of(text); i++)
    {
        ssd1306_draw_string(ssd, 5, y, text[i]);
        y += 8;
    }
    render_on_display(ssd, &frame_area);

    
    // temperature
    uint16_t adc_value = adc_read();
    float_temperature = adc_to_temperature(adc_value);
    int_temperature = float_temperature;
    
    //sleep_ms(1000);

    // joystick
    adc_select_input(0);
    vry_value = adc_read();

    adc_select_input(1);
    vrx_value = adc_read();

    bool sw_value = gpio_get(SW_PIN) == 0;

    sleep_ms(500);
  }



  return 0;
}
