#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "animacoes_matriz_leds.pio.h"
#include <math.h>
#include "pico/bootrom.h"

#define pino_buzzer 21
#define pino_leds 7
#define pixels 25
#define FPS 10
// Configuração do teclado matricial
char teclado[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

int pinos_colunas[4] = {5, 4, 3, 2};
int pinos_linhas[4] = {10, 9, 8, 6};

// Pinos disponíveis na BitDogLab
// int pinos_colunas[4] = {16, 17, 28, 18};
// int pinos_linhas[4] = {19, 20, 9, 8};

// Prototipação das funções
void inicializar_teclado(int colunas[4], int linhas[4]);
char ler_teclado();

void imprimir_binario(int num);                     // Função util para depuração das animações
uint32_t retorno_rgb(double b, double r, double g); // Função que converte float em inteiro por cor
void animacao_1(PIO pio, uint sm, uint num_frame);
void animacao_3(PIO pio, uint sm, uint num_frame);
void animacao_4(PIO pio, uint sm, uint num_frame);
void animacao_6(PIO pio, uint sm);
void animacao_7(PIO pio, uint sm, uint num_frame); // Função do botão 7
void animacao_8(PIO pio, uint sm, uint num_frame);
void animacao_B(PIO pio, uint sm, uint num_frame);
void animacao_c(PIO pio, uint sm);
void setup_case_d(PIO pio, uint sm);
void desligar_leds(PIO pio, uint sm);
void habilitar_modo_gravacao(); // Função do botão *
void acionamento_buzzer(int duracao_ms);
void animacao_hashtag(PIO pio, uint sm, uint num_frame); // Função do botão #
void animacao_coracao(PIO pio, uint sm);

int main()
{
    PIO pio = pio0;
    bool clk;

    clk = set_sys_clock_khz(128000, false);

    uint offset = pio_add_program(pio, &animacoes_matriz_leds_program);
    uint sm = pio_claim_unused_sm(pio, true);
    animacoes_matriz_leds_program_init(pio, sm, offset, pino_leds);

    inicializar_teclado(pinos_colunas, pinos_linhas);
    gpio_init(pino_buzzer);
    gpio_set_dir(pino_buzzer, GPIO_OUT);
    stdio_init_all();
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
                animacao_coracao(pio, sm);
                break;
            case '3':
                printf("Executando animacao 3!\n");
                animacao_3(pio, sm, 5);
                break;
            case '4':
                printf("Executando animacao 4!\n");
                animacao_4(pio, sm, 5);
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
                desligar_leds(pio, sm);
                break;
            case 'B':
                printf("Ligando os LEDs azuis.\n");
                animacao_B(pio, sm, 5);
                break;
            case 'C':
                printf("Ligando os LEDs vermelhos a 80 de intensidade.\n");
                animacao_c(pio, sm);
                break;
            case 'D':
                printf("Configurando os leds para o caso D");
                setup_case_d(pio, sm);
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

// Configuração dos LEDs para o caso D
void setup_case_d(PIO pio, uint sm)
{
    uint32_t buffer[pixels]; // Buffer para os 25 LEDs
    for (int i = 0; i < pixels; i++)
    {
        buffer[i] = retorno_rgb(0.0, 0.0, 0.5);  // Cor verde com intensidade de 50%
        pio_sm_put_blocking(pio, sm, buffer[i]); // Enviar o buffer para todos os LEDs
    }
}

// Inicializa os pinos do teclado matricial
void inicializar_teclado(int colunas[4], int linhas[4])
{
    for (int i = 0; i < 4; i++)
    {
        gpio_init(colunas[i]);
        gpio_set_dir(colunas[i], GPIO_IN);
        gpio_pull_up(colunas[i]);
        gpio_init(linhas[i]);
        gpio_set_dir(linhas[i], GPIO_OUT);
        gpio_put(linhas[i], 1);
    }
}

// Lê o caractere pressionado no teclado matricial
char ler_teclado()
{
    static char ultima_tecla = 0; // Armazena a última tecla pressionada
    char leitura = 0;

    for (int linha = 0; linha < 4; linha++)
    {
        gpio_put(pinos_linhas[linha], 0); // Define a linha como LOW
        for (int coluna = 0; coluna < 4; coluna++)
        {
            if (gpio_get(pinos_colunas[coluna]) == 0)
            {                 // Verifica se a tecla foi pressionada
                sleep_ms(20); // Atraso para estabilização (debounce)
                if (gpio_get(pinos_colunas[coluna]) == 0)
                { // Verifica novamente
                    leitura = teclado[linha][coluna];
                    if (leitura != ultima_tecla)
                    { // Só registra se for uma tecla nova
                        ultima_tecla = leitura;
                        while (gpio_get(pinos_colunas[coluna]) == 0)
                            ; // Aguarda liberação
                        gpio_put(pinos_linhas[linha], 1);
                        return leitura; // Retorna a tecla
                    }
                }
            }
        }
        gpio_put(pinos_linhas[linha], 1); // Restaura a linha para HIGH
    }

    ultima_tecla = 0; // Reseta a última tecla caso nenhuma tecla esteja pressionada
    return leitura;
}

void imprimir_binario(int num)
{
    int i;
    for (i = 31; i >= 0; i--)
    {
        (num & (1 << i)) ? printf("1") : printf("0");
    }
    printf("\n");
}

uint32_t retorno_rgb(double b, double r, double g)
{
    unsigned char R, G, B;
    R = r * 255;
    G = g * 255;
    B = b * 255;
    return (G << 24) | (R << 16) | (B << 8);
}

void animacao_1(PIO pio, uint sm, uint num_frame)
{
    double frames[num_frame][pixels][3];
    for (int j = 0; j < num_frame; j++)
    {
        for (int i = 0; i < pixels; i++)
        {
            frames[j][i][0] = (i + j) % 2 == 0 ? 0.7 : 0.3;
            frames[j][i][1] = (i + j) % 3 == 0 ? 0.0 : 0.5;
            frames[j][i][2] = (i + j) % 5 == 0 ? 1.0 : 0.0;
        }
    }

    uint32_t buffer[pixels];
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

void animacao_3(PIO pio, uint sm, uint num_frame)
{
    double frames[num_frame][pixels][3];
    for (int j = 0; j < num_frame; j++)
    {
        for (int i = 0; i < pixels; i++)
        {
            frames[j][i][0] = sin((i + j) * 0.5) * 0.5 + 0.5; // Onda
            frames[j][i][1] = cos((i + j) * 0.5) * 0.5 + 0.5;
            frames[j][i][2] = 0.2;
        }
    }

    uint32_t buffer[pixels];
    for (int j = 0; j < num_frame; j++)
    {
        for (int i = 0; i < pixels; i++)
        {
            buffer[i] = retorno_rgb(frames[j][i][0], frames[j][i][1], frames[j][i][2]);
        }
        for (int i = 0; i < pixels; i++)
        {
            pio_sm_put_blocking(pio, sm, buffer[i]);
        }
        sleep_ms(400);
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

void animacao_8(PIO pio, uint sm, uint num_frame)
{
    double letras[12][pixels][3] = {

        {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0}, {0.0, 0.4, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0}, {0.0, 0.4, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0}},

        {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0}},

        {{0.0, 0.4, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},

        {{0.0, 0.4, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0}, {0.0, 0.4, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0}, {0.0, 0.4, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},

        {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},

        {{0.0, 0.4, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.4, 0.0}},

        {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},

        {{0.0, 0.6, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.6, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.6, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.6, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.6, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.6, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.6, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.6, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.6, 0.0}},

        {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},

        {{0.0, 0.8, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.8, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.8, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.8, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.8, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.8, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.8, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.8, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.8, 0.0}},

        {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},

        {{0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 1.0, 0.0}}

    };

    uint32_t buffer[pixels];

    // Loop pelos frames para exibição
    for (int frame = 0; frame < num_frame; frame++)
    {
        for (int i = 0; i < pixels; i++)
        {
            int row = i / 5; // Linha atual
            int col = i % 5; // Coluna atual
            buffer[i] = retorno_rgb(
                letras[frame % 12][(4 - row) * 5 + col][0],
                letras[frame % 12][(4 - row) * 5 + col][1],
                letras[frame % 12][(4 - row) * 5 + col][2]);
        }

        // Envio dos dados ao PIO
        for (int i = 0; i < pixels; i++)
        {
            pio_sm_put_blocking(pio, sm, buffer[i]);
        }
        sleep_ms(500); // Atraso entre os frames
    }
}

// função da animação 7
void animacao_7(PIO pio, uint sm, uint num_frame)
{
    double frames[num_frame][pixels][3];
    for (int j = 0; j < num_frame; j++)
    {
        for (int i = 0; i < pixels; i++)
        {
            frames[j][i][0] = 0.5 + 0.5 * sin(2 * 3.1415 * i / 25 + j / 0.1);
            frames[j][i][1] = 0.5 + 0.5 * sin(2 * 3.1415 * i / 25 + j / 0.2);
            frames[j][i][2] = 0.5 + 0.5 * sin(2 * 3.1415 * i / 25 + j / 0.3);
        }
    }

    uint32_t buffer[pixels];
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

void animacao_B(PIO pio, uint sm, uint num_frame)
{
    double frames[num_frame][pixels][3];
    for (int j = 0; j < num_frame; j++)
    {
        for (int i = 0; i < pixels; i++)
        {
            frames[j][i][0] = 1.0;
            frames[j][i][1] = 0.0;
            frames[j][i][2] = 0.0;
        }
    }

    uint32_t buffer[pixels];
    for (int j = 0; j < num_frame; j++)
    {
        for (int i = 0; i < pixels; i++)
        {
            buffer[i] = retorno_rgb(frames[j][i][0], frames[j][i][1], frames[j][i][2]);
        }
        for (int i = 0; i < pixels; i++)
        {
            pio_sm_put_blocking(pio, sm, buffer[i]);
        }
        sleep_ms(200);
    }
}

void animacao_hashtag(PIO pio, uint sm, uint num_frame)
{
    double frames[num_frame][pixels][3];
    for (int j = 0; j < num_frame; j++)
    {
        for (int i = 0; i < pixels; i++)
        {
            frames[j][i][0] = 0.2; // Vermelho (20% de intensidade)
            frames[j][i][1] = 0.2; // Verde    (20% de intensidade)
            frames[j][i][2] = 0.2; // Azul     (20% de intensidade)
        }
    }

    uint32_t buffer[pixels];
    for (int j = 0; j < num_frame; j++)
    {
        for (int i = 0; i < pixels; i++)
        {
            buffer[i] = retorno_rgb(frames[j][i][0], frames[j][i][1], frames[j][i][2]);
        }
        for (int i = 0; i < pixels; i++)
        {
            pio_sm_put_blocking(pio, sm, buffer[i]);
        }
        sleep_ms(200); // Delay opcional entre os frames
    }
}

void desligar_leds(PIO pio, uint sm)
{
    uint32_t buffer[pixels]; // Buffer para os 25 LEDs
    for (int i = 0; i < pixels; i++)
    {
        buffer[i] = retorno_rgb(0.0, 0.0, 0.0); // Cor preta (desligado)
    }

    // Enviar o buffer para todos os LEDs
    for (int i = 0; i < pixels; i++)
    {
        pio_sm_put_blocking(pio, sm, buffer[i]);
    }
}

// função do botão *
void habilitar_modo_gravacao()
{
    printf("Reiniciando e habilitando o modo de gravação via USB...\n");
    sleep_ms(1000);       // Pequeno atraso para garantir que a mensagem seja impressa
    reset_usb_boot(0, 0); // Reinicia e entra no modo de boot USB
}

void acionamento_buzzer(int duracao_ms)
{
    duracao_ms /= 2;
    for (int i = 0; i < duracao_ms; i++)
    {
        gpio_put(pino_buzzer, 1);
        sleep_us(500);
        gpio_put(pino_buzzer, 0);
        sleep_us(500);
    }
}

void animacao_c(PIO pio, uint sm)
{
    uint32_t buffer[pixels];
    double intensidade = 0.8;

    for (int i = 0; i < pixels; i++)
    {
        buffer[i] = retorno_rgb(0.0, intensidade, 0.0);
    }

    for (int i = 0; i < pixels; i++)
    {
        pio_sm_put_blocking(pio, sm, buffer[i]);
    }
}

void animacao_4(PIO pio, uint sm, uint num_frame)
{
    double frames[num_frame][pixels][3];

    for (int j = 0; j < num_frame; j++)
    {
        for (int i = 0; i < pixels; i++)
        {
            frames[j][i][0] = (i + j) % 3 == 0 ? 0.1 : 0.0;
            frames[j][i][1] = (i + j + 1) % 3 == 0 ? 0.9 : 0.0;
            frames[j][i][2] = (i + j + 2) % 3 == 0 ? 0.3 : 0.0;
        }
    }

    uint32_t buffer[pixels];

    for (int j = 0; j < num_frame; j++)
    {
        for (int i = 0; i < pixels; i++)
        {
            buffer[i] = retorno_rgb(frames[j][i][0], frames[j][i][1], frames[j][i][2]);
        }

        for (int i = 0; i < pixels; i++)
        {
            pio_sm_put_blocking(pio, sm, buffer[i]);
        }

        sleep_ms(200);
    }
}

void animacao_coracao(PIO pio, uint sm)
{
    int frame[25] = {
        0, 1, 0, 1, 0,
        1, 1, 1, 1, 1,
        1, 1, 1, 1, 1,
        0, 1, 1, 1, 0,
        0, 0, 1, 0, 0};

    for (int ciclo = 0; ciclo < 10; ciclo++)
    {
        uint32_t buffer[pixels];

        // Prepara o buffer para o coração piscando
        for (int i = 0; i < 5; i++)
        { // Itera pelas linhas
            for (int j = 0; j < 5; j++)
            {                                // Itera pelas colunas
                int index = (4 - i) * 5 + j; // Inverte a ordem das linhas
                if (frame[index] == 1)
                {
                    if (ciclo % 2 == 0)
                    {
                        buffer[i * 5 + j] = retorno_rgb(0.0, 1.0, 0.0); // Vermelho intenso
                    }
                    else
                    {
                        buffer[i * 5 + j] = retorno_rgb(0.0, 0.5, 0.0); // Vermelho fraco
                    }
                }
                else
                {
                    buffer[i * 5 + j] = retorno_rgb(0.0, 0.0, 0.0); // Apagado
                }
            }
        }

        // Envia o frame para os LEDs
        for (int i = 0; i < pixels; i++)
        {
            pio_sm_put_blocking(pio, sm, buffer[i]);
        }

        // Adiciona o efeito de batimento cardíaco no buzzer
        // Primeiro "tum"
        acionamento_buzzer(150); // Batida longa (150ms)
        sleep_ms(150);           // Pausa curta (150ms)
        // Segundo "tum"
        acionamento_buzzer(100); // Batida curta (100ms)

        // Sincronizar com o piscar do coração
        sleep_ms(600); // Intervalo maior antes do próximo ciclo
    }

    // Desliga os LEDs e o buzzer ao final
    desligar_leds(pio, sm);
    gpio_put(pino_buzzer, 0); // Garante que o buzzer está desligado
}
