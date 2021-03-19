#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

#define LED_PIN PICO_DEFAULT_LED_PIN
#define SELECT1 15


int main() {
    adc_init();

    adc_select_input(1);

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_init(SELECT1);
    gpio_set_dir(SELECT1, GPIO_OUT);
    gpio_put(SELECT1, 1);

    while (true) {
        uint16_t result = adc_read();
        gpio_put(LED_PIN, 1);
        sleep_ms(result);
        gpio_put(LED_PIN, 0);
        sleep_ms(result);
    }
}