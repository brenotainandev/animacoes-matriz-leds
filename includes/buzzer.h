#ifndef BUZZER_H
#define BUZZER_H

#include "pico/stdlib.h"
#include "hardware/gpio.h"

// Constante
#define PINO_BUZZER 21

// Função para controle do buzzer
void acionamento_buzzer(int duracao_ms);

#endif // BUZZER_H
