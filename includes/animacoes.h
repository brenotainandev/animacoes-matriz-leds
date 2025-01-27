#ifndef ANIMACOES_H
#define ANIMACOES_H

#include <math.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"

// Declaração das funções de animações
void animacao_1(PIO pio, uint sm, uint num_frame);
void animacao_3(PIO pio, uint sm, uint num_frame);
void animacao_4(PIO pio, uint sm, uint num_frame);
void animacao_6(PIO pio, uint sm);
void animacao_7(PIO pio, uint sm, uint num_frame);
void animacao_8(PIO pio, uint sm, uint num_frame);
void animacao_coracao(PIO pio, uint sm);
void animacao_B(PIO pio, uint sm, uint num_frame);
void animacao_c(PIO pio, uint sm);
void animacao_hashtag(PIO pio, uint sm, uint num_frame);

#endif // ANIMACOES_H
