#include <stdio.h>
#include "pico/stdlib.h"

bool LED_STATE = false;

int64_t blink_callback(alarm_id_t id, void *user_data) {
    LED_STATE = !LED_STATE;
    gpio_put(PICO_DEFAULT_LED_PIN, LED_STATE);
    return 500*1000;
}

void pico_led_init(void) {
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
}

int main() {
    pico_led_init();
    stdio_init_all();

    add_alarm_in_ms(500, blink_callback, NULL, true);
    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }

    return 0;
}
