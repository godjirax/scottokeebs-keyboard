#include QMK_KEYBOARD_H
#include "keymap_french_mac_iso.h"
#include "sendstring_french_mac_iso.h"
// #include "./custom_keycodes.h"


// COMBOS !
// const uint16_t PROGMEM CB_TAB[]  = {FR_D, FR_F, COMBO_END};
// const uint16_t PROGMEM CB_ESC[]  = {FR_D, FR_S, COMBO_END};
const uint16_t PROGMEM CB_BSPC[] = {FR_V, FR_C, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    // COMBO(CB_TAB, KC_TAB),
    // COMBO(CB_ESC, KC_ESC),
    COMBO(CB_BSPC, KC_BSPC),
};
