#include "../includes/matriz-led.h"

uint32_t retorno_rgb(double b, double r, double g) {
    unsigned char R = r * 255;
    unsigned char G = g * 255;
    unsigned char B = b * 255;
    return (G << 24) | (R << 16) | (B << 8);
}

void desligar_leds(PIO pio, uint sm) {
    uint32_t buffer[NUM_PIXELS];
    for (int i = 0; i < NUM_PIXELS; i++) {
        buffer[i] = retorno_rgb(0.0, 0.0, 0.0);
    }

    for (int i = 0; i < NUM_PIXELS; i++) {
        pio_sm_put_blocking(pio, sm, buffer[i]);
    }
}

void setup_case_d(PIO pio, uint sm) {
    uint32_t buffer[NUM_PIXELS];
    for (int i = 0; i < NUM_PIXELS; i++) {
        buffer[i] = retorno_rgb(0.0, 0.0, 0.5);
        pio_sm_put_blocking(pio, sm, buffer[i]);
    }
}
