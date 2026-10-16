// Compact monochrome status UI for Sofle OLED modules.
#ifdef OLED_ENABLE

static void oled_status_line(const char *label, bool active) {
    oled_write_ln(label, active);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

bool oled_task_user(void) {
    if (!is_keyboard_master()) {
        oled_write_ln_P(PSTR(" QMK "), true);
        oled_write_ln_P(PSTR("     "), false);
        oled_write_ln_P(PSTR("SOFLE"), false);
        oled_write_ln_P(PSTR("ELITE"), false);
        oled_write_ln_P(PSTR(" -C- "), false);
        return false;
    }

    const uint8_t layer = get_highest_layer(layer_state | default_layer_state);
    oled_write_ln_P(PSTR("SOFLE"), true);
    switch (layer) {
        case 1: oled_write_ln_P(PSTR("LOWER"), true); break;
        case 2: oled_write_ln_P(PSTR("RAISE"), true); break;
        case 3: oled_write_ln_P(PSTR("ADJST"), true); break;
        default: oled_write_ln_P(PSTR("BASE "), true); break;
    }
    oled_write_ln_P(PSTR("-----"), false);
    const uint8_t mods = get_mods() | get_oneshot_mods();
    oled_write_ln_P(PSTR("SHIFT"), mods & MOD_MASK_SHIFT);
    oled_write_ln_P(PSTR("CTRL "), mods & MOD_MASK_CTRL);
    oled_write_ln_P(PSTR("ALT  "), mods & MOD_MASK_ALT);
    oled_write_ln_P(PSTR("GUI  "), mods & MOD_MASK_GUI);
    oled_write_ln_P(PSTR("-----"), false);
    const led_t leds = host_keyboard_led_state();
    oled_write_ln_P(PSTR("CAPS "), leds.caps_lock);
    oled_write_ln_P(PSTR("NUM  "), leds.num_lock);
    oled_write_ln_P(PSTR("SCRL "), leds.scroll_lock);
    return false;
}
#endif
