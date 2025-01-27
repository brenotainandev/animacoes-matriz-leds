#include "../includes/animacoes.h"
#include "../includes/matriz-led.h"
#include "../includes/buzzer.h"

void animacao_1(PIO pio, uint sm, uint num_frame)
{
    double frames[num_frame][NUM_PIXELS][3];
    for (int j = 0; j < num_frame; j++)
    {
        for (int i = 0; i < NUM_PIXELS; i++)
        {
            frames[j][i][0] = (i + j) % 2 == 0 ? 0.7 : 0.3;
            frames[j][i][1] = (i + j) % 3 == 0 ? 0.0 : 0.5;
            frames[j][i][2] = (i + j) % 5 == 0 ? 1.0 : 0.0;
        }
    }

    uint32_t buffer[NUM_PIXELS];
    for (int j = 0; j < num_frame; j++)
    {
        for (int i = 0; i < 25; i++)
        {
            buffer[i] = retorno_rgb(frames[j][i][0], frames[j][i][1], frames[j][i][2]);
            // imprimir_binario(buffer[i]);
        }
        for (int i = 0; i < 25; i++)
        {
            pio_sm_put_blocking(pio, sm, buffer[i]);
        }
        sleep_ms(500);
    }
}

void animacao_coracao(PIO pio, uint sm) {
    int frame[25] = {
        0, 1, 0, 1, 0,
        1, 1, 1, 1, 1,
        1, 1, 1, 1, 1,
        0, 1, 1, 1, 0,
        0, 0, 1, 0, 0
    };

    for (int ciclo = 0; ciclo < 10; ciclo++) {
        uint32_t buffer[NUM_PIXELS];
        
        // Prepara o buffer para o coração piscando
        for (int i = 0; i < 5; i++) { // Itera pelas linhas
            for (int j = 0; j < 5; j++) { // Itera pelas colunas
                int index = (4 - i) * 5 + j; // Inverte a ordem das linhas
                if (frame[index] == 1) {
                    if (ciclo % 2 == 0) {
                        buffer[i * 5 + j] = retorno_rgb(0.0, 1.0, 0.0); // Vermelho intenso
                    } else {
                        buffer[i * 5 + j] = retorno_rgb(0.0, 0.5, 0.0); // Vermelho fraco
                    }
                } else {
                    buffer[i * 5 + j] = retorno_rgb(0.0, 0.0, 0.0); // Apagado
                }
            }
        }

        // Envia o frame para os LEDs
        for (int i = 0; i < NUM_PIXELS; i++) {
            pio_sm_put_blocking(pio, sm, buffer[i]);
        }

        // Adiciona o efeito de batimento cardíaco no buzzer
        // Primeiro "tum"
        acionamento_buzzer(150); // Batida longa (150ms)
        sleep_ms(150);          // Pausa curta (150ms)
        // Segundo "tum"
        acionamento_buzzer(100); // Batida curta (100ms)

        // Sincronizar com o piscar do coração
        sleep_ms(600); // Intervalo maior antes do próximo ciclo
    }

    // Desliga os LEDs e o buzzer ao final
    desligar_leds(pio, sm);
    gpio_put(PINO_BUZZER, 0); // Garante que o buzzer está desligado
}

void animacao_3(PIO pio, uint sm, uint num_frame) {
    double frames[num_frame][NUM_PIXELS][3];
    for (int j = 0; j < num_frame; j++) {
        for (int i = 0; i < NUM_PIXELS; i++) {
            frames[j][i][0] = sin((i + j) * 0.5) * 0.5 + 0.5; // Onda
            frames[j][i][1] = cos((i + j) * 0.5) * 0.5 + 0.5;
            frames[j][i][2] = 0.2;
        }
    }

    uint32_t buffer[NUM_PIXELS];
    for (int j = 0; j < num_frame; j++) {
        for (int i = 0; i < NUM_PIXELS; i++) {
            buffer[i] = retorno_rgb(frames[j][i][0], frames[j][i][1], frames[j][i][2]);
        }
        for (int i = 0; i < NUM_PIXELS; i++) {
            pio_sm_put_blocking(pio, sm, buffer[i]);
        }
        sleep_ms(400);
    }
}

void animacao_4(PIO pio, uint sm, uint num_frame) {
    double frames[num_frame][NUM_PIXELS][3]; 


    for (int j = 0; j < num_frame; j++) {
        for (int i = 0; i < NUM_PIXELS; i++) {
            frames[j][i][0] = (i + j) % 3 == 0 ? 0.1 : 0.0; 
            frames[j][i][1] = (i + j + 1) % 3 == 0 ? 0.9 : 0.0; 
            frames[j][i][2] = (i + j + 2) % 3 == 0 ? 0.3 : 0.0; 
        }
    }

    uint32_t buffer[NUM_PIXELS]; 

    for (int j = 0; j < num_frame; j++) {
        for (int i = 0; i < NUM_PIXELS; i++) {
            buffer[i] = retorno_rgb(frames[j][i][0], frames[j][i][1], frames[j][i][2]);
        }

        for (int i = 0; i < NUM_PIXELS; i++) {
            pio_sm_put_blocking(pio, sm, buffer[i]);
        }

        sleep_ms(200); 
    }
}

/*
Blue / Red / Blue / Red / Blue / Red
. . . . .    . . . .    .    . . . . .   .     .
.            .     .    .    .           .   .      . . .
. . .        . . .      .    .           . .      .       .
.            .     .    .    .           .   .      .   .
. . . . .    .     .    .    . . . . .   .     .      .
letra E ativa pins 0, 1, 2, 3, 4, 5, 12, 13, 14, 15, 20, 21, 22, 23, 24
letra R ativa pins 0, 4, 5, 8, 12, 13, 14, 15, 18, 21, 22, 23, 24
letra I ativa pins 4, 5, 14, 15, 24
letra C ativa pins 0, 1, 2, 3, 4, 5, 14, 15, 20, 21, 22, 23, 24
letra K ativa pins 1, 4, 5, 7, 13, 14, 15, 17, 21, 24
caractere ♥ ativa pins 2, 6, 8, 10, 12, 14, 16, 18
*/
void animacao_5(PIO pio, uint sm)
{
    int32_t sleep_time = 1000;
    // letra E ativa pins
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        if ((i >= 0 && i <= 5) || (i >= 12 && i <= 15) || (i >= 20 && i <= 24))
        {
            pio_sm_put_blocking(pio, sm, retorno_rgb(0.5, 0.0, 0.0));
        }
        else
        {
            pio_sm_put_blocking(pio, sm, retorno_rgb(0.0, 0.0, 0.0));
        }
    }
    sleep_ms(sleep_time); // Pausa para frame
    // letra R ativa pins
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        if (i == 0 || i == 4 || i == 5 || i == 8 || (i >= 12 && i <= 15) || i == 18 || (i >= 21 && i <= 24))
        {
            pio_sm_put_blocking(pio, sm, retorno_rgb(0.0, 0.5, 0.0));
        }
        else
        {
            pio_sm_put_blocking(pio, sm, retorno_rgb(0.0, 0.0, 0.0));
        }
    }
    sleep_ms(sleep_time); // Pausa para frame
    // letra I ativa pins
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        if (i == 4 || i == 5 || i == 14 || i == 15 || i == 24)
        {
            pio_sm_put_blocking(pio, sm, retorno_rgb(0.5, 0.0, 0.0));
        }
        else
        {
            pio_sm_put_blocking(pio, sm, retorno_rgb(0.0, 0.0, 0.0));
        }
    }
    sleep_ms(sleep_time); // Pausa para frame
    // letra C ativa pins
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        if ((i >= 0 && i <= 5) || (i >= 14 && i <= 15) || (i >= 20 && i <= 24))
        {
            pio_sm_put_blocking(pio, sm, retorno_rgb(0.0, 0.5, 0.0));
        }
        else
        {
            pio_sm_put_blocking(pio, sm, retorno_rgb(0.0, 0.0, 0.0));
        }
    }
    sleep_ms(sleep_time); // Pausa para frame
    // letra K ativa pins
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        if (i == 1 || i == 4 || i == 5 || i == 7 || (i >= 13 && i <= 15) || i == 17 || i == 21 || i == 24)
        {
            pio_sm_put_blocking(pio, sm, retorno_rgb(0.5, 0.0, 0.0));
        }
        else
        {
            pio_sm_put_blocking(pio, sm, retorno_rgb(0.0, 0.0, 0.0));
        }
    }
    sleep_ms(sleep_time);                             // Pausa para frame
    sleep_time = 450;                                 // Piscagem rápida do coração
    for (int quantity = 1; quantity <= 5; quantity++) // Pisca o coração 5 vezes
    {
        // Pisca coração em vermelho
        for (int i = 0; i < NUM_PIXELS; i++)
        {
            if (i != 0 && i != 4 && (i % 2 == 0) && i <= 18)
            {
                pio_sm_put_blocking(pio, sm, retorno_rgb(0.0, 0.5, 0.0));
            }
            else
            {
                pio_sm_put_blocking(pio, sm, retorno_rgb(0.0, 0.0, 0.0));
            }
        }
        sleep_ms(sleep_time); // Pausa para frame
        // Pisca coração em azul
        for (int i = 0; i < NUM_PIXELS; i++)
        {
            if (i != 0 && i != 4 && (i % 2 == 0) && i <= 18)
            {
                pio_sm_put_blocking(pio, sm, retorno_rgb(0.5, 0.0, 0.0));
            }
            else
            {
                pio_sm_put_blocking(pio, sm, retorno_rgb(0.0, 0.0, 0.0));
            }
        }
        sleep_ms(sleep_time); // Pausa para frame
    }
}

void animacao_6(PIO pio, uint sm)
{
    int linha = 5;
    int coluna = 5;

    // Definição das cores (100% de intensidade)
    double cores[3][3] = {
        {1.0, 0.0, 0.0}, // Vermelho (100%)
        {0.0, 1.0, 0.0}, // Verde (100%)
        {0.0, 0.0, 1.0}  // Azul (100%)
    };

    uint32_t buffer[linha * coluna];

    // Preenchendo a matriz com um padrão fixo de cores
    for (int i = 0; i < linha * coluna; i++)
    {
        int cor_index = i % 3; // Alterna entre 0, 1 e 2 (vermelho, verde, azul)
        buffer[i] = retorno_rgb(cores[cor_index][0], cores[cor_index][1], cores[cor_index][2]);
    }

    // Enviando os dados para os LEDs
    for (int i = 0; i < linha * coluna; i++)
    {
        pio_sm_put_blocking(pio, sm, buffer[i]);
    }

    sleep_ms(500); // Pausa para observar o padrão
}

// função da animação 7
void animacao_7(PIO pio, uint sm, uint num_frame)
{
    double frames[num_frame][NUM_PIXELS][3];
    for (int j = 0; j < num_frame; j++)
    {
        for (int i = 0; i < NUM_PIXELS; i++)
        {
            frames[j][i][0] = 0.5 + 0.5 * sin(2 * 3.1415 * i / 25 + j / 0.1);
            frames[j][i][1] = 0.5 + 0.5 * sin(2 * 3.1415 * i / 25 + j / 0.2);
            frames[j][i][2] = 0.5 + 0.5 * sin(2 * 3.1415 * i / 25 + j / 0.3);
        }
    }

    uint32_t buffer[NUM_PIXELS];
    for (int j = 0; j < num_frame; j++)
    {
        for (int i = 0; i < 25; i++)
        {
            buffer[i] = retorno_rgb(frames[j][i][0], frames[j][i][1], frames[j][i][2]);
            // imprimir_binario(buffer[i]);
        }
        for (int i = 0; i < 25; i++)
        {
            pio_sm_put_blocking(pio, sm, buffer[i]);
        }
        sleep_ms(500);
    }
}

void animacao_8(PIO pio, uint sm, uint num_frame) {
    double letras[12][NUM_PIXELS][3] = {
        
        {
            {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0},
            {0.0, 0.4, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0},
            {0.0, 0.4, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0}
        },
        
        {
            {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0},
            {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0}
        },
        
        {
            {0.0, 0.4, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0}, {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0}, {0.0, 0.0, 0.0},
            {0.0, 0.4, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}
        },
        
        {
            {0.0, 0.4, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0},
            {0.0, 0.4, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0},
            {0.0, 0.4, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}
        },

        {
            {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}
        },
        
        {
            {0.0, 0.4, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0},
            {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0}, {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0}, {0.0, 0.0, 0.0},
            {0.0, 0.4, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0}
        },

        {
            {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}
        },

        {
            {0.0, 0.6, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.6, 0.0},
            {0.0, 0.0, 0.0}, {0.0, 0.6, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.6, 0.0}, {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.6, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}, {0.0, 0.6, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.6, 0.0}, {0.0, 0.0, 0.0},
            {0.0, 0.6, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.6, 0.0}
        },

        {
            {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}
        },

        {
            {0.0, 0.8, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.8, 0.0},
            {0.0, 0.0, 0.0}, {0.0, 0.8, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.8, 0.0}, {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.8, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}, {0.0, 0.8, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.8, 0.0}, {0.0, 0.0, 0.0},
            {0.0, 0.8, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.8, 0.0}
        },

        {
            {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}
        },

        {
            {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 1.0, 0.0},
            {0.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0},
            {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        }

        
    };

    uint32_t buffer[NUM_PIXELS];

    // Loop pelos frames para exibição
    for (int frame = 0; frame < num_frame; frame++) {
        for (int i = 0; i < NUM_PIXELS; i++) {
            int row = i / 5;  // Linha atual
            int col = i % 5;  // Coluna atual
            buffer[i] = retorno_rgb(
                letras[frame % 12][(4 - row) * 5 + col][0],
                letras[frame % 12][(4 - row) * 5 + col][1],
                letras[frame % 12][(4 - row) * 5 + col][2]
            );
        }

        // Envio dos dados ao PIO
        for (int i = 0; i < NUM_PIXELS; i++) {
            pio_sm_put_blocking(pio, sm, buffer[i]);
        }
        sleep_ms(500); // Atraso entre os frames
    }
}

void animacao_B(PIO pio, uint sm, uint num_frame)
{
    double frames[num_frame][NUM_PIXELS][3];
    for (int j = 0; j < num_frame; j++)
    {
        for (int i = 0; i < NUM_PIXELS; i++)
        {
            frames[j][i][0] = 1.0;
            frames[j][i][1] = 0.0;
            frames[j][i][2] = 0.0;
        }
    }

    uint32_t buffer[NUM_PIXELS];
    for (int j = 0; j < num_frame; j++)
    {
        for (int i = 0; i < NUM_PIXELS; i++)
        {
            buffer[i] = retorno_rgb(frames[j][i][0], frames[j][i][1], frames[j][i][2]);
        }
        for (int i = 0; i < NUM_PIXELS; i++)
        {
            pio_sm_put_blocking(pio, sm, buffer[i]);
        }
        sleep_ms(200);
    }
}

void  animacao_c(PIO pio, uint sm) {
    uint32_t buffer[NUM_PIXELS];
    double intensidade = 0.8; 

    for (int i = 0; i < NUM_PIXELS; i++) {
        buffer[i] = retorno_rgb(0.0, intensidade, 0.0); 
    }

    for (int i = 0; i < NUM_PIXELS; i++) {
        pio_sm_put_blocking(pio, sm, buffer[i]);
    }
}

void animacao_hashtag(PIO pio, uint sm, uint num_frame)
{
    double frames[num_frame][NUM_PIXELS][3];
    for (int j = 0; j < num_frame; j++)
    {
        for (int i = 0; i < NUM_PIXELS; i++)
        {
            frames[j][i][0] = 0.2; // Vermelho (20% de intensidade)
            frames[j][i][1] = 0.2; // Verde    (20% de intensidade)
            frames[j][i][2] = 0.2; // Azul     (20% de intensidade)
        }
    }

    uint32_t buffer[NUM_PIXELS];
    for (int j = 0; j < num_frame; j++)
    {
        for (int i = 0; i < NUM_PIXELS; i++)
        {
            buffer[i] = retorno_rgb(frames[j][i][0], frames[j][i][1], frames[j][i][2]);
        }
        for (int i = 0; i < NUM_PIXELS; i++)
        {
            pio_sm_put_blocking(pio, sm, buffer[i]);
        }
        sleep_ms(200); // Delay opcional entre os frames
    }
}