
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "inc/ssd1306.h"


//#include "pico/cyw43_arch.h"

#define BUTTON_A 5
#define BUTTON_B 6
#define LED_RED 13
#define LED_GREEN 11
#define LED_BLUE 12

#define OFF 0
#define ON 1

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

int main() {
  char string_total_pressed[3] = "ok";
  char string_time_now[3];
  uint wait_time = 1000;
  struct repeating_timer timer;


  stdio_init_all();

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
    /*
    if (total_pressed < 255) {
      strcpy(string_total_pressed,"0");
    }
    else {
      strcpy(string_total_pressed, "!");
    }
    */


    char *text[] = {
      "Tempo atual:",
      string_time_now,
      "button b: ",
      string_total_pressed};

    int y = 0;
    for (uint i = 0; i < count_of(text); i++)
    {
        ssd1306_draw_string(ssd, 5, y, text[i]);
        y += 8;
    }
    render_on_display(ssd, &frame_area);

  

  }



  return 0;
}
