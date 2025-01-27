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
// int pinos_colunas[4] = {16, 17, 28, 18};
// int pinos_linhas[4] = {19, 20, 9, 8};

void inicializar_teclado() {
    for (int i = 0; i < 4; i++) {
        gpio_init(pinos_colunas[i]);
        gpio_set_dir(pinos_colunas[i], GPIO_IN);
        gpio_pull_up(pinos_colunas[i]);
        gpio_init(pinos_linhas[i]);
        gpio_set_dir(pinos_linhas[i], GPIO_OUT);
        gpio_put(pinos_linhas[i], 1);
    }
}

char ler_teclado() {
    static char ultima_tecla = 0; // Armazena a última tecla pressionada
    char leitura = 0;

    for (int linha = 0; linha < 4; linha++) {
        gpio_put(pinos_linhas[linha], 0); // Define a linha como LOW
        for (int coluna = 0; coluna < 4; coluna++) {
            if (gpio_get(pinos_colunas[coluna]) == 0) { // Verifica se a tecla foi pressionada
                sleep_ms(20); // Atraso para estabilização (debounce)
                if (gpio_get(pinos_colunas[coluna]) == 0) { // Verifica novamente
                    leitura = teclado[linha][coluna];
                    if (leitura != ultima_tecla) { // Só registra se for uma tecla nova
                        ultima_tecla = leitura;
                        while (gpio_get(pinos_colunas[coluna]) == 0); // Aguarda liberação
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
