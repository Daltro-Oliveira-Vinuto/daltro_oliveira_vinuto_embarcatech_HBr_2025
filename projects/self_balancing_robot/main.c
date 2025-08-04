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


int main() {
    stdio_init_all();
    // setup and enable motor
    motor_setup();
    motor_enable();

    // setu and enable mpu6050
    mpu6050_setup_i2c();
    mpu6050_reset();
    int16_t accel_raw[3], gyro_raw[3], temp;
    float accel[3], gyro[3];

    // Exemplo: comando de controle com valor negativo = girar para tras
    float control_signal = -0.95f * 255.0f;

    bool forward = control_signal > 0; // obtem direcao
    float magnitude = fabsf(control_signal); // obtem modulo do sinal
    float limitado = fminf(magnitude, 255.0f); // limita ao maximo de 255
    uint16_t level = (uint16_t)limitado << 8; // converte e ajusta escala
    
    motor_set_both_level(level, forward); // envia comando para motores

    sleep_ms(5000); // mantem ligado por 1 segundo

    motor_set_both_level(0, true); // para os motores

    while (1) {
        //tight_loop_contents(); // mantém o programa rodando
        mpu6050_read_raw(accel, gyro, &temp); // armazena valores lido
        printf("Accel raw X: %d, Y: %d, Z: %d \n", accel_raw[0], accel_raw[1], accel_raw[2]);
        printf("Gyro raw X: %d, Y: %d, Z: %d \n", gyro_raw[0], gyro_raw[1], gyro_raw[2]);

        // Convert to g's and degrees per second
        for (uint8_t i = 0; i < 3; i++) {
            accel[i] = (float)accel_raw[i] / 16384.0f;
            gyro[i] = (float)gyro_raw[i] / 131.0f;
        }
        printf("--------------------------------\n");
        printf("Accel X: %.3f, Y: %.3f, Z: %.3f \n", accel[0], accel[1], accel[2]);
        printf("Gyro X: %.3f, Y: %.3f, Z: %.3f \n", gyro[0], gyro[1], gyro[2]);
        printf("\n\n");

        sleep_ms(1000);
    }
}
