#pragma once

// Unique Vial identity for this custom Sofle Keyhive build.
#define VIAL_KEYBOARD_UID { 0x53, 0x4F, 0x46, 0x4C, 0x45, 0x4B, 0x48, 0x31 }

// Four physical corner keys to unlock Vial.
#define VIAL_UNLOCK_COMBO_ROWS { 0, 5, 3, 8 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 0, 0, 0 }

// Constrain dynamic storage for ATmega32U4/Elite-C.
#define DYNAMIC_KEYMAP_LAYER_COUNT 4
#define DYNAMIC_KEYMAP_MACRO_COUNT 8
#define VIAL_COMBO_ENTRIES 8

// Mod-tap is a core QMK feature and remains available without a feature flag.
#define TAPPING_TERM 200
