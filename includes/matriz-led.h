#ifndef LED_H
#define LED_H

#include "pico/stdlib.h"
#include "hardware/pio.h"

// Constantes
#define NUM_PIXELS 25
#define PINO_LEDS 7

// Funções gerais para LEDs
uint32_t retorno_rgb(double b, double r, double g);
void desligar_leds(PIO pio, uint sm);
void setup_case_d(PIO pio, uint sm);

#endif // LED_H
