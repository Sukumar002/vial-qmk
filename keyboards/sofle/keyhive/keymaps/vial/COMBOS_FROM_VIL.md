# Dynamic Vial combos from Vial_combos_working.vil

The .vil export includes 24 combo slots: 11 populated and 13 empty.
These are Vial EEPROM settings, not compiled defaults. Import the original .vil in Vial after an EEPROM reset to restore them; compiling keymap.c alone does not restore dynamic combos.

| Keys | Vial output |
| --- | --- |
| J + K | `LALT_T(KC_BSPACE)` |
| K + L | `LGUI_T(KC_DELETE)` |
| J + L | `LCTL_T(KC_QUOTE)` |
| D + F | `LALT_T(KC_TAB)` |
| S + D | `LGUI_T(KC_GRAVE)` |
| S + F | `LCTL_T(KC_ESCAPE)` |
| F + J | `LSFT(KC_EQUAL)` |
| D + K | `KC_MINUS` |
| S + L | `LSFT(KC_MINUS)` |
| E + F | `KC_LBRACKET` |
| I + J | `KC_RBRACKET` |

The original export has 4 layers, 8 empty macros, 2 encoder mappings per layer, and no configured tap dances or key overrides.
