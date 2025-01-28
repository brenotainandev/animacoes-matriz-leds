#include "../includes/modo-gravacao.h"

// função do botão *
void habilitar_modo_gravacao()
{
    printf("Reiniciando e habilitando o modo de gravação via USB...\n");
    sleep_ms(1000);       // Pequeno atraso para garantir que a mensagem seja impressa
    reset_usb_boot(0, 0); // Reinicia e entra no modo de boot USB
}