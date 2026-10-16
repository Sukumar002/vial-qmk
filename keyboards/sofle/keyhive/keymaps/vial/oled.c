// SPDX-License-Identifier: GPL-2.0-or-later
#ifdef OLED_ENABLE

static void render_status(void) {
    oled_write_ln_P(PSTR("SOFLE"), true);
    oled_write_ln_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state | default_layer_state)) {
        case 1: oled_write_ln_P(PSTR("LOWER"), false); break;
        case 2: oled_write_ln_P(PSTR("RAISE"), false); break;
        case 3: oled_write_ln_P(PSTR("ADJST"), false); break;
        default: oled_write_ln_P(PSTR("BASE "), false); break;
    }
    oled_write_ln_P(PSTR("LOCKS"), false);
    const led_t locks = host_keyboard_led_state();
    oled_write_ln_P(PSTR("CAPS "), locks.caps_lock);
    oled_write_ln_P(PSTR("NUM  "), locks.num_lock);
    oled_write_ln_P(PSTR("SCRL "), locks.scroll_lock);
}

static void render_firmware(void) {
    oled_write_ln_P(PSTR(" QMK "), true);
    oled_write_ln_P(PSTR("SOFLE"), false);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return is_keyboard_master() ? OLED_ROTATION_270 : rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status();
    } else {
        render_firmware();
    }
    return false;
}
#endif
