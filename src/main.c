#include "pico/stdlib.h"
#include "bsp/board.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

#include "tusb.h"

uint16_t value = 0;

void midi_task(void)
{
    uint8_t const cable_num = 0; // MIDI jack associated with USB endpoint
    uint8_t const channel   = 0; // 0 for channel 1

    uint8_t packet[4];
    while(tud_midi_available()) tud_midi_receive(packet);


    // Send Note On for current position at full velocity (127) on channel 1.
    tudi_midi_write24(cable_num, 0xB0 | channel, 2, value);
}

int main() {

    tusb_init();

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    int array[]= {10, 11, 12, 13, 14, 15};
    int arraySize = sizeof(array) / sizeof(int);
    for(int i=0; i < arraySize; i++){
        gpio_init(array[i]);
        gpio_set_dir(array[i], GPIO_OUT);
    }

    adc_init();
    adc_gpio_init(27);
    adc_select_input(1);

    while (true) {
        tud_task(); // TinyUSB device task
        midi_task();
        //for(int i = 0; i < arraySize; i++) {

        gpio_put(array[0], 1);
        value = adc_read() / 32;
        gpio_put(array[0], 0);

        // gpio_put(PICO_DEFAULT_LED_PIN, 1);
        // sleep_ms(result);
        // gpio_put(PICO_DEFAULT_LED_PIN, 0);
        // sleep_ms(result);
        // gpio_put(array[0], 0);
        //}
    }
}