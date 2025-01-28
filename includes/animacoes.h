#ifndef ANIMACOES_H
#define ANIMACOES_H

#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"

// Declaração das funções de animações
void animacao_1(PIO pio, uint sm, uint num_frame);       // Função do botão 1
void animacao_2(PIO pio, uint sm);                       // Função do botão 2
void animacao_3(PIO pio, uint sm, uint num_frame);       // Função do botão 3
void animacao_4(PIO pio, uint sm, uint num_frame);       // Função do botão 4
void animacao_5(PIO pio, uint sm);                       // Função do botão 5
void animacao_6(PIO pio, uint sm);                       // Função do botão 6
void animacao_7(PIO pio, uint sm, uint num_frame);       // Função do botão 7
void animacao_8(PIO pio, uint sm, uint num_frame);       // Função do botão 8
void animacao_a(PIO pio, uint sm);                       // Função do botão A
void animacao_b(PIO pio, uint sm, uint num_frame);       // Função do botão B
void animacao_c(PIO pio, uint sm);                       // Função do botão C
void animacao_d(PIO pio, uint sm);                       // Função do botão D
void animacao_hashtag(PIO pio, uint sm, uint num_frame); // Função do botão #

#endif // ANIMACOES_H
