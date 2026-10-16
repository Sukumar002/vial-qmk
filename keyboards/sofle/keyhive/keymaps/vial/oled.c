// SPDX-License-Identifier: GPL-2.0-or-later
#ifdef OLED_ENABLE

// Portrait mode on the standard Sofle 128x32 OLED provides 32x128 pixels.
// All indicators are real pixel-drawn outline/filled buttons.
static void box(uint8_t x, uint8_t y, uint8_t w, uint8_t h, bool on) {
    for (uint8_t py = y; py < y + h; ++py) {
        for (uint8_t px = x; px < x + w; ++px) {
            const bool edge = py == y || py == y + h - 1 || px == x || px == x + w - 1;
            oled_write_pixel(px, py, on || edge);
        }
    }
}

// Each letter is a compact 3x5 glyph (bit 2 is leftmost).
static void glyph(uint8_t x, uint8_t y, const uint8_t *shape, bool inverted) {
    for (uint8_t row = 0; row < 5; ++row) {
        for (uint8_t col = 0; col < 3; ++col) {
            const bool dot = ((shape[row] >> (2 - col)) & 1) != 0;
            oled_write_pixel(x + col, y + row, inverted ? !dot : dot);
        }
    }
}

static void indicator(uint8_t x, uint8_t y, bool on, const uint8_t *letter) {
    box(x, y, 13, 12, on);
    glyph(x + 5, y + 3, letter, on);
}

static void render_status(void) {
    static const uint8_t zero[] = {7,5,5,5,7};
    static const uint8_t one[]  = {2,6,2,2,7};
    static const uint8_t two[]  = {7,1,7,4,7};
    static const uint8_t three[]= {7,1,7,1,7};
    static const uint8_t shift[]= {7,4,7,1,7}; // S
    static const uint8_t ctrl[] = {7,4,4,4,7}; // C
    static const uint8_t alt[]  = {2,5,7,5,5}; // A
    static const uint8_t gui[]  = {7,4,5,5,7}; // G
    static const uint8_t num[]  = {5,7,7,7,5}; // N
    static const uint8_t scr[]  = {7,4,7,1,7}; // S

    const uint8_t layer = get_highest_layer(layer_state | default_layer_state);
    const uint8_t mods = get_mods() | get_oneshot_mods();
    const led_t locks = host_keyboard_led_state();

    oled_set_cursor(0, 0);
    oled_write_P(PSTR("SOFLE"), true);
    oled_set_cursor(0, 1);
    oled_write_P(PSTR("LAYRS"), false);
    indicator(1, 19, layer == 0, zero);
    indicator(17, 19, layer == 1, one);
    indicator(1, 34, layer == 2, two);
    indicator(17, 34, layer == 3, three);

    oled_set_cursor(0, 6);
    oled_write_P(PSTR("MODS "), false);
    indicator(1, 62, (mods & MOD_MASK_SHIFT) != 0, shift);
    indicator(17, 62, (mods & MOD_MASK_CTRL) != 0, ctrl);
    indicator(1, 77, (mods & MOD_MASK_ALT) != 0, alt);
    indicator(17, 77, (mods & MOD_MASK_GUI) != 0, gui);

    oled_set_cursor(0, 12);
    oled_write_P(PSTR("LOCKS"), false);
    // Narrow labels: C = caps; N = num; S = scroll.
    box(0, 108, 10, 12, locks.caps_lock);
    glyph(3, 111, ctrl, locks.caps_lock);
    box(11, 108, 10, 12, locks.num_lock);
    glyph(14, 111, num, locks.num_lock);
    box(22, 108, 10, 12, locks.scroll_lock);
    glyph(25, 111, scr, locks.scroll_lock);
}

static void render_firmware(void) {
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
    oled_clear();
    if (is_keyboard_master()) {
        render_status();
    } else {
        render_firmware();
    }
    return false;
}
#endif
