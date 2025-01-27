#include "../includes/buzzer.h"

void acionamento_buzzer(int duracao_ms) {
    gpio_init(PINO_BUZZER);
    gpio_set_dir(PINO_BUZZER, GPIO_OUT);
    duracao_ms /= 2;

    for (int i = 0; i < duracao_ms; i++) {
        gpio_put(PINO_BUZZER, 1);
        sleep_us(500);
        gpio_put(PINO_BUZZER, 0);
        sleep_us(500);
    }
}
