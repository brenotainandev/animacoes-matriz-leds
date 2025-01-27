#include "../includes/matriz-led.h"

uint32_t retorno_rgb(double b, double r, double g) {
    unsigned char R = r * 255;
    unsigned char G = g * 255;
    unsigned char B = b * 255;
    return (G << 24) | (R << 16) | (B << 8);
}

void desligar_leds(PIO pio, uint sm)
{
    uint32_t buffer[NUM_PIXELS]; // Buffer para os 25 LEDs
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        buffer[i] = retorno_rgb(0.0, 0.0, 0.0); // Cor preta (desligado)
    }

    // Enviar o buffer para todos os LEDs
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        pio_sm_put_blocking(pio, sm, buffer[i]);
    }
}

// Configuração dos LEDs para o caso D
void setup_case_d(PIO pio, uint sm)
{
    uint32_t buffer[NUM_PIXELS]; // Buffer para os 25 LEDs
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        buffer[i] = retorno_rgb(0.0, 0.0, 0.5);  // Cor verde com intensidade de 50%
        pio_sm_put_blocking(pio, sm, buffer[i]); // Enviar o buffer para todos os LEDs
    }
}
