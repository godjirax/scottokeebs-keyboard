/* Copyright 2019 Takuya Urakawa (dm9records.com)
 * Copyright 2026 Kevin
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

#include QMK_KEYBOARD_H
#include "hid.h"
#include "keymap_french_mac_iso.h"

enum layers {
    _AZERTY,
    _FRENCH,
    _CODE,
    _NUMBERS,
    _LOWER,
    _ADJUST,
    _NUMBERS_NEW,
};

enum custom_keycodes {
    AZERTY = SAFE_RANGE,
    CODE_LAYER,
    FRENCH_LAYER,
    NUMBERS_LAYER,
    STAR_CODE,
};

#define M_CODE LT(_CODE, FR_M)
#define Q_CODE LT(_CODE, FR_Q)
#define S_NUMBERS_NEW LT(_NUMBERS_NEW, FR_S)
#define SPAC_FREN LT(_FRENCH, KC_SPC)
#define SPAC_NUM LT(_NUMBERS, KC_SPC)
#define COMM_RCTL RCTL_T(FR_COMM)
#define ALT_TAB LALT(KC_TAB)
#define TH_DOT FR_ELLP

const uint16_t PROGMEM backspace_combo[] = {FR_V, FR_C, COMBO_END};

combo_t key_combos[] = {
    COMBO(backspace_combo, KC_BSPC),
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_AZERTY] = LAYOUT_ortho_4x12(
        KC_ESC,    FR_A,     FR_W,          FR_E,    FR_R,    FR_T,      FR_Y,      FR_U,      FR_I,      FR_O,    FR_P,    KC_BSPC,
        KC_TAB,    Q_CODE,   S_NUMBERS_NEW, FR_D,    FR_F,    FR_G,      FR_H,      FR_J,      FR_K,      FR_L,    M_CODE,  KC_ENT,
        KC_LSFT,   FR_Z,     FR_X,          FR_C,    FR_V,    FR_B,      FR_N,      COMM_RCTL, FR_SCLN,   FR_COLN, FR_EQL,  _______,
        STAR_CODE, _______, KC_LCTL,        KC_LALT, KC_LGUI, SPAC_NUM,  SPAC_FREN, KC_RSFT,   KC_RALT,   KC_RCTL, _______, _______
    ),

    [_FRENCH] = LAYOUT_ortho_4x12(
        FR_AT,   FR_LAGR, _______, FR_LEAC, FR_LEGR, FR_DIAE, FR_LUGR, KC_PGDN, KC_PGUP, FR_UNDS, FR_OCIR, _______,
        ALT_TAB, _______, _______, FR_DQUO, FR_QUOT, FR_CIRC, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, FR_AT,   FR_EURO,
        _______, _______, FR_CCCE, FR_LCCE, _______, _______, FR_ACUT, FR_EXLM, _______, FR_MINS, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_CODE] = LAYOUT_ortho_4x12(
        FR_TILD, FR_AMPR, FR_LABK, FR_LBRC, FR_RBRC, FR_SLSH, XXXXXXX, FR_ASTR, FR_QUOT, XXXXXXX, FR_UNDS, KC_DEL,
        KC_ESC,  FR_GRV,  FR_EQL,  FR_LPRN, FR_RPRN, FR_EXLM, FR_COLN, FR_DOT,  FR_SLSH, XXXXXXX, FR_AT,   FR_DLR,
        _______, FR_PIPE, FR_RABK, FR_LCBR, FR_RCBR, FR_PERC, FR_PLUS, FR_MINS, FR_HASH, TH_DOT,  FR_BSLS, _______,
        QK_MAKE, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_NUMBERS] = LAYOUT_ortho_4x12(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
        _______, XXXXXXX, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_ASTR, _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, FR_PLUS, FR_MINS, FR_COMM, FR_DOT,  FR_SLSH, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_LOWER] = LAYOUT_ortho_4x12(
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, QK_BOOT,
        KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
        _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  _______,
        _______, KC_BRID, KC_BRIU, _______, _______, _______, _______, _______,    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY
    ),

    [_ADJUST] = LAYOUT_ortho_4x12(
        QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,
        _______, _______, MU_NEXT, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, AZERTY, CODE_LAYER, FRENCH_LAYER, NUMBERS_LAYER, _______,
        _______, AU_PREV, AU_NEXT, MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______,      _______,       _______,       _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______,       _______,       _______
    ),

    [_NUMBERS_NEW] = LAYOUT_ortho_4x12(
        _______, _______, _______, _______, _______, _______, _______, FR_7, FR_8, FR_9, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, FR_4, FR_5, FR_6, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, FR_1, FR_2, FR_3, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, FR_0, FR_0, COMM_RCTL, _______, _______
    ),
};
// clang-format on

const uint8_t N_LAYERS = ARRAY_SIZE(keymaps);

static bool star_pressed;
static bool star_used;

#define SCALE(value) ((value * RGB_BRIGHTNESS) / 255)

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
}

void housekeeping_task_user(void) {
    switch (get_highest_layer(layer_state | default_layer_state)) {
        case _FRENCH:
            rgblight_setrgb(0, SCALE(255), SCALE(255)); // Cyan
            return;
        case _CODE:
            rgblight_setrgb(SCALE(255), SCALE(255), 0); // Yellow
            return;
        case _NUMBERS:
            rgblight_setrgb(0, 0, SCALE(255)); // Blue
            return;
        case _LOWER:
            rgblight_setrgb(SCALE(255), SCALE(64), 0); // Orange
            return;
        case _ADJUST:
            rgblight_setrgb(SCALE(255), 0, 0); // Red
            return;
        case _NUMBERS_NEW:
            rgblight_setrgb(SCALE(128), 0, SCALE(255)); // Purple
            return;
        default:
            rgblight_setrgb(SCALE(255), SCALE(255), SCALE(255)); // White
            return;
    }
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    (void)keycode;
    (void)record;
    return TAPPING_TERM;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    send_event_to_hid(keycode, record->event);

    if (star_pressed && keycode != STAR_CODE && record->event.pressed) {
        star_used = true;
    }

    switch (keycode) {
        case STAR_CODE:
            if (record->event.pressed) {
                star_pressed = true;
                star_used    = false;
                layer_on(_LOWER);
            } else {
                layer_off(_LOWER);
                if (!star_used) {
                    tap_code16(FR_ASTR);
                }
                star_pressed = false;
            }
            return false;

        case AZERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_AZERTY);
            }
            return false;

        case CODE_LAYER:
            record->event.pressed ? layer_on(_CODE) : layer_off(_CODE);
            return false;
        case FRENCH_LAYER:
            record->event.pressed ? layer_on(_FRENCH) : layer_off(_FRENCH);
            return false;
        case NUMBERS_LAYER:
            record->event.pressed ? layer_on(_NUMBERS) : layer_off(_NUMBERS);
            return false;
    }

    return true;
}
