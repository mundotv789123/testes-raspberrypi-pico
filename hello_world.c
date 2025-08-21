#include <stdio.h>
#include "pico/stdlib.h"

#ifndef PICO_DEFAULT_LED_PIN
#warning blink_simple example requires a board with a regular LED
#endif

void pico_led_init(void) {
#ifdef PICO_DEFAULT_LED_PIN
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
#endif
}

void pico_set_led(bool led_on) {
#if defined(PICO_DEFAULT_LED_PIN)
    gpio_put(PICO_DEFAULT_LED_PIN, led_on);
#endif
}

int main() {
    pico_led_init();
    stdio_init_all();
    while (true) {
        printf("Hello, world!\n");
        pico_set_led(true);
        sleep_ms(500);
        pico_set_led(false);
        sleep_ms(500);
    }
}
