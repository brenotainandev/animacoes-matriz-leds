#ifndef TECLADO_H
#define TECLADO_H

#include <stdint.h>
#include "pico/stdlib.h"

// Configuração do teclado matricial
extern char teclado[4][4];          // Mapeamento das teclas
extern int pinos_colunas[4];        // Pinos das colunas do teclado
extern int pinos_linhas[4];         // Pinos das linhas do teclado

// Funções para inicializar e ler o teclado
void inicializar_teclado();         // Inicializa os pinos do teclado
char ler_teclado();                 // Lê a tecla pressionada

#endif // TECLADO_H
