#include <stdio.h>
#include <math.h>
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "animacoes_matriz_leds.pio.h"
#include "./includes/teclado.h"
#include "./includes/animacoes.h"
#include "./includes/buzzer.h"
#include "./includes/matriz-led.h"
#include "./includes/modo-gravacao.h"

int main()
{
    PIO pio = pio0;
    bool clk;

    clk = set_sys_clock_khz(128000, false);

    uint offset = pio_add_program(pio, &animacoes_matriz_leds_program);
    uint sm = pio_claim_unused_sm(pio, true);
    animacoes_matriz_leds_program_init(pio, sm, offset, PINO_LEDS);

    gpio_init(PINO_BUZZER);
    gpio_set_dir(PINO_BUZZER, GPIO_OUT);
    stdio_init_all();
    inicializar_teclado();

    if (clk)
        printf("clock definido em: %ld\n", clock_get_hz(clk_sys));
    printf("Sistema inicializado. Aguardando comandos...\n");

    while (true)
    {

        char tecla = ler_teclado();

        if (tecla != 0)
        { // Se alguma tecla foi pressionada
            printf("Tecla retornada: %c \n", tecla);
            acionamento_buzzer(500);
            sleep_ms(500);

            switch (tecla)
            {
            case '1':
                printf("Executando animacao 1!\n");
                animacao_1(pio, sm, 5);
                break;
            case '2':
                printf("Executando animacao do coracao!\n");
                animacao_2(pio, sm);
                break;
            case '3':
                printf("Executando animacao 3!\n");
                animacao_3(pio, sm, 5);
                break;
            case '4':
                printf("Executando animacao 4!\n");
                animacao_4(pio, sm, 5);
                break;
            case '5':
                printf("Executando animacao 5!\n");
                animacao_5(pio, sm);
                break;
            case '6':
                printf("Executando animacao 6!\n");
                animacao_6(pio, sm);
                break;
            case '7':
                printf("Executando animacao 7!\n");
                animacao_7(pio, sm, 5);
                break;
            case '8':
                printf("Executando animacao 8!\n");
                animacao_8(pio, sm, 12);
                break;
            case 'A':
                printf("Desligando todos os LEDs.\n");
                animacao_a(pio, sm);
                break;
            case 'B':
                printf("Ligando os LEDs azuis.\n");
                animacao_b(pio, sm, 5);
                break;
            case 'C':
                printf("Ligando os LEDs vermelhos a 80 de intensidade.\n");
                animacao_c(pio, sm);
                break;
            case 'D':
                printf("Configurando os leds para o caso D");
                animacao_d(pio, sm);
                break;
            case '*':
                printf("Reiniciando o Raspberry Pi Pico W.\n");
                habilitar_modo_gravacao();
                break;
            case '#':
                printf("Executando animacao da tecla #\n");
                animacao_hashtag(pio, sm, 5);
                break;
            default:
                printf("Nenhuma ação associada à tecla %c.\n", tecla);
            }
        }
    }
}
