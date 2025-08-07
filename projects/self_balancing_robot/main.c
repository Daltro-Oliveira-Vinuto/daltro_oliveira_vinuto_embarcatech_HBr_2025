#include <stdio.h> // Biblioteca padrão
#include <stdlib.h>
#include <math.h> // Biblioteca de matemática (função "round" foi utilizada)
#include <string.h>

// PICO standard libraries  
#include "pico/stdlib.h" // Biblioteca padrão pico
#include "pico/cyw43_arch.h" // Driver wifi for the Pico W 
#include "hardware/gpio.h" // Biblioteca de GPIOs
#include "hardware/adc.h" // Biblioteca do ADC
#include "hardware/pwm.h" // Biblioteca do PWM
#include "hardware/timer.h"
#include "hardware/i2c.h"

// libraries for the oled screen
#include "include/basic.h"
#include "include/ssd1306.h"

// driver for the motor (h bridge tb6612fng)
#include "motor.h"

// header file for the driver of the mpu6050
#include "mpu6050_i2c.h"

void setup_button(int button_left, int button_right) {
    gpio_init(button_left);
    gpio_set_dir(button_left, GPIO_IN);
    gpio_pull_up(button_left);

    gpio_init(button_right);
    gpio_set_dir(button_right, GPIO_IN);
    gpio_pull_up(button_right);
}


struct Angle {
    float x, y, z;
};
typedef struct Angle Angle_t;

int main() {
    int button_left = 6, button_right = 5;
    Angle_t angle;

    stdio_init_all();
    sleep_ms(3000);
    printf("Welcome to the binary world!\n");
    // setup and enable motor
    motor_setup();
    motor_enable();

    // setup and enable mpu6050
    mpu6050_setup_i2c();
    mpu6050_reset();

    // setup button
    setup_button(button_left, button_right);


    int16_t accel_raw[3], gyro_raw[3], temp;
    float accel[3], gyro[3], angles[3];

    // Exemplo: comando de controle com valor negativo = girar para tras
    float control_signal = -0.90f * 255.0f;

    bool direction = control_signal > 0; // obtem direcao
    float magnitude = fabsf(control_signal); // obtem modulo do sinal
    float limitado = fminf(magnitude, 255.0f); // limita ao maximo de 255
    uint16_t level = (uint16_t)limitado << 8; // converte e ajusta escala
    
    //motor_set_both_level(level, forward); // envia comando para motores

    //sleep_ms(0); // mantem ligado por 1 segundo

    motor_set_both_level(level, direction); // para os motores
    sleep_ms(2000);
    //level = 0;
    //motor_set_both_level(level, direction);

    while (1) {
        bool emergency_button;
        bool restart_button;
        bool high_angle, low_angle;
        printf("button left: %d  button_right: %d \n", emergency_button, restart_button);


        //tight_loop_contents(); // mantém o programa rodando
        mpu6050_read_raw(accel_raw, gyro_raw, &temp); // armazena valores lido
        printf("Accel raw X: %d, Y: %d, Z: %d \n", accel_raw[0], accel_raw[1], accel_raw[2]);
        printf("Gyro raw X: %d, Y: %d, Z: %d \n", gyro_raw[0], gyro_raw[1], gyro_raw[2]);

        // Convert to g's and degrees per second
        for (uint8_t i = 0; i < 3; i++) {
            accel[i] = (float)accel_raw[i] / 16384.0f;
            gyro[i] = (float)gyro_raw[i] / 131.0f;
            angles[i] = (180*asinf(accel[i]))/M_PI;
        }
        angle.x = angles[0];
        angle.y = angles[1];
        angle.z = angles[2];
        direction = angle.y < 0;


        printf("--------------------------------\n");
        printf("Accel X: %.3f g's, Y: %.3f g's, Z: %.3f g's \n", accel[0], accel[1], accel[2]);
        printf("Gyro X: %.1f °/s Y: %.1f °/s, Z: %.1f °/s\n", gyro[0], gyro[1], gyro[2]);
        printf("Gyro X: %.1f °, Y: %.1f °, Z: %.1f °\n", angle.x, angle.y, angle.z);

        printf("\n\n");

        high_angle =  (angle.y <= -45.0 || angle.y >= 45.0);
        low_angle =  (angle.y > -45.0 && angle.y < 45.0);

        emergency_button = !gpio_get(button_right);
        restart_button = !gpio_get(button_left);

        if (emergency_button || high_angle) {
            motor_set_both_level(0, direction);
        }

        if (restart_button || low_angle) {
            motor_set_both_level(level, direction);
        }

        sleep_ms(1000);
    }
}
