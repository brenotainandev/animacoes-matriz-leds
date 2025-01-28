#include "../includes/teclado.h"

// Configuração do teclado matricial
char teclado[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Pinos disponíveis no Wokwi Simulator
int pinos_colunas[4] = {5, 4, 3, 2};
int pinos_linhas[4] = {10, 9, 8, 6};

// Pinos disponíveis na BitDogLab
// int pinos_linhas[4] = {16, 17, 18, 19};
// int pinos_colunas[4] =  {20, 4, 9, 8};

void inicializar_teclado() {
    // Inicializa as linhas e colunas do teclado
    for (int i = 0; i < 4; i++) {  // Itera sobre cada linha do teclado.
        gpio_init(pinos_linhas[i]);       // Inicializa o pino da linha atual.
        gpio_set_dir(pinos_linhas[i], GPIO_OUT); // Define o pino como saída.
        gpio_put(pinos_linhas[i], 1);     // Define o pino como alto (1).
    }

    for (int i = 0; i < 4; i++) {  // Itera sobre cada coluna do teclado.
        gpio_init(pinos_colunas[i]);       // Inicializa o pino da coluna atual.
        gpio_set_dir(pinos_colunas[i], GPIO_IN);  // Define o pino como entrada.
        gpio_pull_up(pinos_colunas[i]);    // Ativa o resistor de pull-up no pino.
    }
}

char ler_teclado() {
    for (int linha = 0; linha < 4; linha++) {
        gpio_put(pinos_linhas[linha], 0); // Define a linha como LOW
        sleep_ms(5); // Pequeno atraso para estabilização

        for (int coluna = 0; coluna < 4; coluna++) {
            if (gpio_get(pinos_colunas[coluna]) == 0) { // Verifica se a tecla foi pressionada
                while (gpio_get(pinos_colunas[coluna]) == 0); // Aguarda até que a tecla seja liberada
                gpio_put(pinos_linhas[linha], 1); // Restaura a linha para nível lógico alto
                return teclado[linha][coluna]; // Retorna a tecla correspondente
            }
        }
        gpio_put(pinos_linhas[linha], 1); // Restaura a linha para nível lógico alto
    }

    return '\0'; // Nenhuma tecla foi pressionada
}