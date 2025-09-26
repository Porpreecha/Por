#include <device.h>
#include <drivers/behavior.h>
#include <zmk/keys.h>
#include <zmk/event_manager.h>
#include <zmk/events/keycode_state_changed.h>

struct encoder_macro_config {
    uint8_t key1;
    uint8_t key2; // ใช้สำหรับ scroll หรือ zoom ถ้าไม่ใช้ก็ใส่ 0
};

struct encoder_macro_data {};

int encoder_macro_init(struct device *dev) {
    ARG_UNUSED(dev);
    return 0;
}

int encoder_macro_binding_pressed(struct device *dev, struct behavior_binding *binding) {
    struct encoder_macro_config *cfg = (struct encoder_macro_config *)binding->behavior_dev->config;

    if (cfg->key2) {
        // ส่ง key1 และ key2 พร้อมกัน (เช่น เมาส์กลาง + scroll)
        ZMK_EVENT_RAISE(new_zmk_keycode_state_changed(dev, cfg->key1, true));
        ZMK_EVENT_RAISE(new_zmk_keycode_state_changed(dev, cfg->key2, true));
        ZMK_EVENT_RAISE(new_zmk_keycode_state_changed(dev, cfg->key2, false));
        ZMK_EVENT_RAISE(new_zmk_keycode_state_changed(dev, cfg->key1, false));
    } else {
        // ส่ง key1 อย่างเดียว
        ZMK_EVENT_RAISE(new_zmk_keycode_state_changed(dev, cfg->key1, true));
        ZMK_EVENT_RAISE(new_zmk_keycode_state_changed(dev, cfg->key1, false));
    }

    return 0;
}

int encoder_macro_binding_released(struct device *dev, struct behavior_binding *binding) {
    // ไม่ต้องทำอะไรเพราะ macro ส่ง key แบบ tap ไปแล้ว
    return 0;
}

ZMK_BEHAVIOR_DRIVER(encoder_macro, encoder_macro_init, encoder_macro_binding_pressed, encoder_macro_binding_released);
