// SPDX-License-Identifier: GPL-2.0-or-later
#ifdef OLED_ENABLE

// The common Sofle 128x32 display is 32x128 in portrait orientation.
// Draw simple outlined/filled indicator buttons without a font dependency.
static void draw_box(uint8_t x, uint8_t y, uint8_t w, uint8_t h, bool filled) {
    for (uint8_t py = y; py < (uint8_t)(y + h); py++) {
        for (uint8_t px = x; px < (uint8_t)(x + w); px++) {
            bool border = py == y || py == (uint8_t)(y + h - 1) ||
                          px == x || px == (uint8_t)(x + w - 1);
            oled_write_pixel(px, py, filled || border);
        }
    }
}

static void indicator(uint8_t x, uint8_t y, uint8_t w, uint8_t h, bool active) {
    draw_box(x, y, w, h, active);
}

static void status_oled(void) {
    const uint8_t active_layer = get_highest_layer(layer_state | default_layer_state);
    const uint8_t mods = get_mods() | get_oneshot_mods();
    const led_t locks = host_keyboard_led_state();

    // Fixed portrait text header; pixel indicators underneath.
    oled_set_cursor(0, 0);
    oled_write_P(PSTR("SOFLE"), true);
    oled_set_cursor(0, 1);
    oled_write_P(PSTR("LAYER"), false);

    // Four layer indicators in a vertical column, with tiny numeric labels.
    // Inactive: thin outline; active: inverted/filled interior.
    for (uint8_t i = 0; i < 4; ++i) {
        indicator(1, (uint8_t)(19 + i * 13), 13, 11, i == active_layer);
        oled_set_cursor(3, (uint8_t)(2 + i)); // next to the box: numeric label
        oled_write_char((char)('0' + i), i == active_layer);
    }

    oled_set_cursor(0, 7);
    oled_write_P(PSTR("MODS"), false);
    indicator(1, 68, 13, 12, (mods & MOD_MASK_SHIFT) != 0);
    indicator(17, 68, 13, 12, (mods & MOD_MASK_CTRL) != 0);
    indicator(1, 83, 13, 12, (mods & MOD_MASK_ALT) != 0);
    indicator(17, 83, 13, 12, (mods & MOD_MASK_GUI) != 0);

    // Labels for the four modifier indicator boxes, via font cursor.
    oled_set_cursor(0, 10);
    oled_write_P(PSTR("S C"), false);
    oled_set_cursor(0, 12);
    oled_write_P(PSTR("A G"), false);

    // Host lock LED states are shown as active boxes only, not a permanently
    // illuminated list. C = Caps, N = Num, S = Scroll.
    indicator(1, 110, 9, 12, locks.caps_lock);
    indicator(12, 110, 9, 12, locks.num_lock);
    indicator(23, 110, 8, 12, locks.scroll_lock);
}

static void firmware_oled(void) {
    oled_set_cursor(0, 0);
    oled_write_ln_P(PSTR(" QMK "), true);
    oled_write_ln_P(PSTR("     "), false);
    oled_write_ln_P(PSTR("SOFLE"), false);
    oled_write_ln_P(PSTR("ELITE"), false);
    oled_write_ln_P(PSTR("  C  "), false);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

bool oled_task_user(void) {
    // Clear once per refresh so inactive boxes reliably revert to outlines.
    oled_clear();
    if (is_keyboard_master()) {
        status_oled();
    } else {
        firmware_oled();
    }
    return false;
}
#endif
