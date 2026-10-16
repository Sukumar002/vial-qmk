// Copyright 2026
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "vial.h"
#include "dynamic_keymap.h"
#include "oled.c"

enum sofle_layers { BASE, LOWER, RAISE, ADJUST };

// Default keymap reconstructed from Vial_combos_working.vil (matrix order).
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
        KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_GRV,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
        KC_GRV, LSFT_T(KC_A), KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, RSFT_T(KC_SCLN), KC_QUOT,
        LCTL_T(KC_ESC), LCTL_T(KC_Z), KC_X, KC_C, KC_V, KC_B, KC_MUTE, KC_MPLY, KC_N, KC_M, KC_COMM, KC_DOT, RCTL_T(KC_SLSH), RCTL_T(KC_DEL),
        KC_LCTL, KC_APP, LGUI_T(KC_DEL), LALT_T(KC_ENT), LT(1, KC_SPC), LT(2, KC_ENT), LALT_T(KC_SPC), LGUI_T(KC_BSPC), KC_APP, KC_RCTL
    ),
    [LOWER] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, _______,
        _______, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, _______,
        _______, KC_EQL, KC_MINS, LSFT(KC_EQL), LSFT(KC_LBRC), LSFT(KC_RBRC), _______, _______, KC_EQL, KC_MINS, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [RAISE] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, MAGIC_UNSWAP_LALT_LGUI, MAGIC_SWAP_LALT_LGUI, _______, KC_SCRL, KC_PGUP, _______, KC_UP, _______, KC_HOME, KC_BSPC,
        _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_NUM, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_END, _______,
        _______, KC_UNDO, KC_CUT, KC_COPY, KC_PSTE, KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [ADJUST] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, LOWER, RAISE, ADJUST);
}

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [BASE]   = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD), ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    [LOWER]  = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [RAISE]  = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [ADJUST] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};

// These are reset-time defaults for the existing 24 Vial-editable combo slots.
// Existing EEPROM customizations are not changed during normal operation.
#ifdef VIAL_COMBO_ENABLE
void vial_combo_defaults_user(void) {
    const vial_combo_entry_t combo_0 = { .input = {KC_J, KC_K, KC_NO, KC_NO}, .output = LALT_T(KC_BSPC) };
    dynamic_keymap_set_combo(0, &combo_0);
    const vial_combo_entry_t combo_1 = { .input = {KC_K, KC_L, KC_NO, KC_NO}, .output = LGUI_T(KC_DEL) };
    dynamic_keymap_set_combo(1, &combo_1);
    const vial_combo_entry_t combo_2 = { .input = {KC_J, KC_L, KC_NO, KC_NO}, .output = LCTL_T(KC_QUOT) };
    dynamic_keymap_set_combo(2, &combo_2);
    const vial_combo_entry_t combo_3 = { .input = {KC_D, KC_F, KC_NO, KC_NO}, .output = LALT_T(KC_TAB) };
    dynamic_keymap_set_combo(3, &combo_3);
    const vial_combo_entry_t combo_4 = { .input = {KC_S, KC_D, KC_NO, KC_NO}, .output = LGUI_T(KC_GRV) };
    dynamic_keymap_set_combo(4, &combo_4);
    const vial_combo_entry_t combo_5 = { .input = {KC_S, KC_F, KC_NO, KC_NO}, .output = LCTL_T(KC_ESC) };
    dynamic_keymap_set_combo(5, &combo_5);
    const vial_combo_entry_t combo_6 = { .input = {KC_F, KC_J, KC_NO, KC_NO}, .output = LSFT(KC_EQL) };
    dynamic_keymap_set_combo(6, &combo_6);
    const vial_combo_entry_t combo_7 = { .input = {KC_D, KC_K, KC_NO, KC_NO}, .output = KC_MINS };
    dynamic_keymap_set_combo(7, &combo_7);
    const vial_combo_entry_t combo_8 = { .input = {KC_S, KC_L, KC_NO, KC_NO}, .output = LSFT(KC_MINS) };
    dynamic_keymap_set_combo(8, &combo_8);
    const vial_combo_entry_t combo_9 = { .input = {KC_E, KC_F, KC_NO, KC_NO}, .output = KC_LBRC };
    dynamic_keymap_set_combo(9, &combo_9);
    const vial_combo_entry_t combo_10 = { .input = {KC_I, KC_J, KC_NO, KC_NO}, .output = KC_RBRC };
    dynamic_keymap_set_combo(10, &combo_10);
}
#endif
