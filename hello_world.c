#include <stdio.h>
#include "pico/stdlib.h"

#include "pico/time.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"

#include "pico/multicore.h"

void on_pwm_wrap() {
    static int fade = 0;
    static bool going_up = true;
    pwm_clear_irq(pwm_gpio_to_slice_num(PICO_DEFAULT_LED_PIN));

    if (going_up) {
        ++fade;
        if (fade > 255) {
            fade = 255;
            going_up = false;
        }
    } else {
        --fade;
        if (fade < 0) {
            fade = 0;
            going_up = true;
        }
    }

    pwm_set_gpio_level(PICO_DEFAULT_LED_PIN, fade * fade);
}

void main2() {
    gpio_set_function(PICO_DEFAULT_LED_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(PICO_DEFAULT_LED_PIN);

    pwm_clear_irq(slice_num);
    pwm_set_irq_enabled(slice_num, true);
    irq_set_exclusive_handler(PWM_DEFAULT_IRQ_NUM(), on_pwm_wrap);
    irq_set_enabled(PWM_DEFAULT_IRQ_NUM(), true);

    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 4.f);
    pwm_init(slice_num, &config, true);

    while (1)
        tight_loop_contents();
}


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
//    pico_led_init();
    stdio_init_all();

//    add_alarm_in_ms(500, blink_callback, NULL, true);
    multicore_launch_core1(main2);

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }

    return 0;
}
