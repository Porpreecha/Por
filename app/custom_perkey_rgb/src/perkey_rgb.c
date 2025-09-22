#include "perkey_rgb.h"
#include <drivers/led_strip.h>
#include <zephyr.h>

#define LED_COUNT 108

static const struct device *led_dev;
static uint32_t led_colors[LED_COUNT];

void perkey_rgb_init(void) {
    led_dev = device_get_binding("NEOPIXEL");
    for (int i = 0; i < LED_COUNT; i++) {
        led_colors[i] = 0x000000; // ปิดไฟทุก LED ตอน init
    }
    led_strip_update_rgb(led_dev, led_colors, LED_COUNT);
}

void perkey_rgb_set_key(uint16_t key_index, uint32_t color) {
    if (key_index >= LED_COUNT) return;

    led_colors[key_index] = color;
    led_strip_update_rgb(led_dev, led_colors, LED_COUNT);
}
