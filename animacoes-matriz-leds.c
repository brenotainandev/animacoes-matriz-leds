#include <stdio.h>
#include "pico/stdlib.h"


#define pino_buzzer 27
#define pino_leds 7
// Configuração do teclado matricial
char teclado[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};
int pinos_colunas[4] = {3, 2, 1, 0};
int pinos_linhas[4] = {8, 6, 5, 4};

//Pinos disponíveis na BitDogLab
//int pinos_colunas[4] = {16, 17, 28, 18};
//int pinos_linhas[4] = {19, 20, 9, 8};


// Prototipação das funções
void inicializar_teclado(int colunas[4], int linhas[4]);
char ler_teclado();

int main() {

    inicializar_teclado(pinos_colunas, pinos_linhas);
    gpio_init(pino_buzzer);
    gpio_set_dir(pino_buzzer, GPIO_OUT);
    gpio_init(pino_leds);
    gpio_set_dir(pino_leds, GPIO_OUT);
    stdio_init_all();
    printf("Sistema inicializado. Aguardando comandos...\n");

  while (true) {
    char tecla = ler_teclado();
    if (tecla != 0) { // Se alguma tecla foi pressionada
          printf("Tecla retornada: %c \n", tecla);
  
      switch(tecla){
        case 'A':
          break;
        case 'B':
          break;
        default:
          printf("Nenhuma ação associada à tecla %c.\n", tecla);
  }}
}}
// Inicializa os pinos do teclado matricial
void inicializar_teclado(int colunas[4], int linhas[4]) {
    for (int i = 0; i < 4; i++) {
        gpio_init(colunas[i]);
        gpio_set_dir(colunas[i], GPIO_IN);
        gpio_pull_up(colunas[i]);
        gpio_init(linhas[i]);
        gpio_set_dir(linhas[i], GPIO_OUT);
        gpio_put(linhas[i], 1);
    }
}

// Lê o caractere pressionado no teclado matricial
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
