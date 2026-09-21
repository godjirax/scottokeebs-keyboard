/* Copyright 2019 Takuya Urakawa (dm9records.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "keymap_french_mac_iso.h"
#include "keycodes.h"
#include "defs.h"
#include "sendstring_french_mac_iso.h"
#include "./combos.h"
#include "./hid.h"

// #define TAPPING_TERM 250
#define IGNORE_MOD_TAP_INTERRUPT
#define TAPPING_TERM_PER_KEY

// Does not work
// enum combos {
//   AB_ESC,
//   JK_TAB,
//   QW_SFT,
//   SD_LAYER,
// };

// const uint16_t PROGMEM test_combo1[] = {KC_A, KC_B, COMBO_END};
// const uint16_t PROGMEM test_combo2[] = {KC_C, KC_D, COMBO_END};
// combo_t key_combos[COMBO_COUNT] = {
//     COMBO(test_combo1, KC_ESC),
//     COMBO(test_combo2, LCTL(KC_Z)), // keycodes with modifiers are possible too!
// };

// // const uint16_t PROGMEM CB_BSPC[]  = { FR_F, FR_D, COMBO_END };

// // combo_t key_combos[COMBO_COUNT] = {
// // 	COMBO(CB_BSPC,  KC_BSPC)
// // };

enum plaid_keycodes {
  AZERTY = SAFE_RANGE,
  QWERTY,
  FRENCH,
  CODE,
  LOWER,
  NUMBERS,
  NUMBERS_NEW,
  LED_1,
  LED_2,
  LED_3,
  LED_4,
  LED_5,
  LED_6,
  LED_7,
  LED_8,
  LED_9,
  LED_0,
  // E_GRV, // è
  // E_ACU, // é
  // E_CIR, // ê
  // A_GRV, // à
  // U_GRV,  // ù
};


// array of keys considered modifiers for led purposes
const uint16_t modifiers[] = {
    KC_LCTL,
    KC_RCTL,
    KC_LALT,   
    KC_RALT,
    KC_LSFT,
    KC_RSFT,
    KC_LGUI,
    KC_RGUI,
    CODE,
    NUMBERS,
    FRENCH,
    NUMBERS_NEW
};

//Setup consts for LED modes
#define LEDMODE_ON 1 //always on
#define LEDMODE_OFF 0 //always off
#define LEDMODE_MODS 2 //On with modifiers
#define LEDMODE_BLINKIN 3 //blinkinlights - % chance toggle on keypress
#define LEDMODE_KEY 4 //On with any keypress, off with key release
#define LEDMODE_ENTER 5 // On with enter key

//Code Layer
#define TH_DOT RALT(KC_SCLN) // …
//French Layer
// #define F_OE   RALT(KC_Q)    // œŒ
// #define F_LQUO RALT(KC_BSLS) // «
// #define F_RQUO LSA(KC_BSLS)  // »
// #define E_RQUO LSA(KC_RBRC)  // ’
// #define E_RDQU LSA(KC_LBRC)  // ”
// #define E_LQUO RALT(KC_RBRC) // ‘
// #define E_LDQU RALT(KC_LBRC) // “
// #define F_DEGR LSA(KC_8)     // °
// #define F_GRMD RALT(KC_GRV)  // `
// #define F_ACMD RALT(KC_E)    // ´
// #define F_CIMD RALT(KC_I)    // ˆ
// #define F_TRMD RALT(KC_U)    // ¨
// #define F_AE   RALT(KC_QUOT) // æÆ
// #define F_AT   RALT(KC_2)    // @
// #define F_EURO LSA(KC_2)     // €
// #define F_CCED RALT(KC_C)    // çÇ
// #define F_MDOT LSA(KC_9)     // ·
#define ALT_SHIFT LCTL(KC_LSFT)
#define _NUMBERS_NEW 6

// KQ
// #define LOWER MO(_LOWER)
// #define FRENCH MO(_RAISE)
#define NUMBERS_NEW MO(_NUMBERS_NEW)
#define M_CODE LT(_CODE, FR_M)   // tap: m, hold: code layer
#define Q_CODE LT(_CODE, FR_Q)   // tap: q, hold: code layer
#define S_NUMBERS_NEW LT(_NUMBERS_NEW, FR_S)   // tap: q, hold: code layer
#define STAR_CODE LT(_LOWER, FR_ASTR)   // tap: *, hold: lower layer
#define SPAC_FREN LT(_FRENCH, KC_SPC)   // tap: Space, hold: french layer
#define SPAC_NUM LT(_NUMBERS, KC_SPC)   // tap: Space, hold: french layer
#define L_RCTRL LT(KC_RCTL, FR_L)   // tap: Space, hold: french layer

#define LGUI_F LGUI_T(FR_F)
#define LCTL_D LALT_T(FR_D)
#define LCTL_S LCTL_T(FR_S)

#define RGUI_J RGUI_T(FR_J)
#define RCTL_K RALT_T(FR_K)
#define RCTL_L RCTL_T(FR_L)
#define COMM_RCTL RCTL_T(FR_COMM)


// ALT + TAB: utilisez LALT(KC_TAB) directement dans le keymap
#define ALT_TAB LALT(KC_TAB)

// #define M_CODE LT(_NUMBERS, FR_M)   // tap: =, hold: code layer

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Azerty
 * ,-----------------------------------------------------------------------------------------.
 * | Esc      |   A  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |   Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------------|
 * | Tab      |   Q  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |M_CODE|  Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+*-----------|
 * |   Shift  |   Z  |   X  |   C  |   V  |   B  |   N  |   ,  |   ;  |   :  |   =  | _______|
 * |------+------+------+------+------+------+------+------+------+------+------+------------|
 * | *        | Ctrl | Shift| Alt. |GUI   | SPAC_NUM|FRENCH|Shift | Alt  | Ctrl | ___ | ___  |
 * `-----------------------------------------------------------------------------------------'
 */
[_AZERTY] = LAYOUT_ortho_4x12(
    KC_ESC,  FR_A,      FR_W,             FR_E,    FR_R,    FR_T,       FR_Y,         FR_U,      FR_I,      FR_O,    FR_P,    KC_BSPC,
    KC_TAB,  Q_CODE,    S_NUMBERS_NEW,    FR_D,    FR_F,    FR_G,       FR_H,         FR_J,      FR_K,      FR_L,    M_CODE,  KC_ENT,
    KC_LSFT, FR_Z,      FR_X,             FR_C,    FR_V,    FR_B,       FR_N,         COMM_RCTL, FR_SCLN,   FR_COLN, FR_EQL,  _______ ,
    STAR_CODE, _______, KC_LCTL,          KC_LALT, KC_LGUI, SPAC_NUM,   SPAC_FREN,    KC_RSFT,   KC_RALT,   KC_RCTL, _______, _______
),

/* French Layer
 * ,-----------------------------------------------------------------------------------.
 * |   @  |   à  | ____ |   é  |   è  |   ¨  |   û  |KC_PGDN|KC_PGUP|  _   |   ô  | Bksp |
 * |------+------+------+------+------+-------------+-------+-------+------+------+------|
 * | ___  | ___  | ___  |   "  |   '  |   ˆ  | Left | Down  | Up    | Right|   €  |  $   |
 * |------+------+------+------+------+------|------+-------+-------+------+------+------|
 * | ___  | ___  |   Ç  |   ç  | ___  | ___  |   ´  |   !   | ____  |   -  | ____ | ___  |
 * |------+------+------+------+------+------+------+-------+-------+------+------+------|
 * | ___  | ___  | ___  | ____ | ____ | ____ | ____ | ____  | ____  | ____ | ____ | ____ |
 * `-----------------------------------------------------------------------------------'
 */
[_FRENCH] = LAYOUT_ortho_4x12(
    FR_AT,    FR_LAGR, _______, FR_LEAC, FR_LEGR, FR_DIAE, FR_LUGR, KC_PGDN,  KC_PGUP,  FR_UNDS, FR_OCIR,  _______,
    ALT_TAB,  _______, _______, FR_DQUO, FR_QUOT, FR_CIRC, KC_LEFT, KC_DOWN,        KC_UP,    KC_RGHT, KC_AT,    FR_EURO,
    _______,  _______, FR_CCCE, FR_LCCE, _______, _______, FR_ACUT, FR_EXLM,        _______,  FR_MINS, _______,  _______,
    _______,  _______, _______, _______, _______, _______, _______, _______,        _______,  _______, _______,  _______
),
/* Code Layer
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   &  |   <  |   [  |   ]  |   /  |      |   *  |   '  |      |      | DEL  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | ESC  |   `  |   =  |   (  |   )  |   !  |   :  |   .  |   /  |      |   @  |  $   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|+++m
 * | ____ |   |  |   >  |   {  |   }  |   %  |   +  |   -  |   #  |   …  |   \  | ____ |
 * |------+---|---+------+------+------+------+------+------+------+------+------+------|
 * |QK_MAKE| ____ | ____ | ___  | ____ |  DEL | ____ | ____ | ____ | ____ | ____ | ____ |
 * `-----------------------------------------------------------------------------------'
 */
[_CODE] = LAYOUT_ortho_4x12(
    FR_TILD, FR_AMPR, FR_LABK,   FR_LBRC, FR_RBRC, FR_SLSH, XXXXXXX, FR_ASTR, FR_QUOT, XXXXXXX, FR_UNDS, KC_DEL,
    KC_ESC,   FR_GRV,  FR_EQL,  FR_LPRN, FR_RPRN, FR_EXLM, FR_COLN, FR_DOT, FR_SLSH, XXXXXXX, FR_AT,   FR_DLR,
    _______,  FR_PIPE, FR_RABK,   FR_LCBR, FR_RCBR, FR_PERC, FR_PLUS, FR_MINS, FR_HASH, TH_DOT,  FR_BSLS, _______,
    QK_MAKE,  _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______
),
/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Home | End  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_4x12(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  _______,
    _______, KC_BRID, KC_BRIU, _______, _______, _______, _______, _______,    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+--
 ----+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |Pg Up |Pg Dn |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
// [_RAISE] = LAYOUT_ortho_4x12(
//     KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
//     KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
//     _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______,
//     _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
// ),


/* Numbers Layer
 * ,-------------------------------------------------------------------------------------------.
 * | ____ |   F1  |   F2  |   F 3    |   F4    |   F5  |   F6  |   F7  |   F8  |   F9  |   F10  | ____ |
 * |------+------+------+---------+-----------+------+------+------+------+------+------+------|
 * | ____ |      | home | page up | page down |      | Left | Down | Up   | Right|   *  | ____ |
 * |------+------+------+---------+-----------+------|------+------+------+------+------+------|
 * | ____ |      |      |         |           |      |   +  |   -  |   ,  |   .  |   /  | ____ |
 * |------+------+------+---------+-----------+------+------+------+------+------+------+------|
 * | ____ | LED_1 | LED_2 | LED_3 | LED_4 | LED_5 | LED_6 | LED_7 |  LED_8 | LED_9 | LED_0 | ____ |
 * `-------------------------------------------------------------------------------------------'
 */

[_NUMBERS] = LAYOUT_plaid_grid(
    _______, KC_F1,    KC_F2,    KC_F3,    KC_F4,      KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,    _______,
    _______, XXXXXXX, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_ASTR, _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, FR_PLUS, FR_MINS, FR_COMM, FR_DOT,  FR_SLSH, _______,
    _______, LED_1 ,LED_2 ,LED_3 ,LED_4 ,LED_5 ,LED_6 ,LED_7 , LED_8 ,LED_9 ,LED_0, _______
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |Reset |      |      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|  |Plover|      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_ortho_4x12(
    QK_BOOT,LED_1, LED_2, LED_3, LED_4, LED_5,LED_6, LED_7, LED_8, LED_9, LED_0,KC_DEL ,
    _______, _______, MU_NEXT, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, AZERTY,  CODE, FRENCH,  NUMBERS,  _______,
    _______, AU_PREV, AU_NEXT, MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_NUMBERS_NEW] = LAYOUT_ortho_4x12(
    _______, _______, _______, _______, _______, _______,     _______, FR_7   , FR_8   , FR_9   , _______, _______, 
    _______, _______, _______, _______, _______, _______,     _______, FR_4   , FR_5   , FR_6   , _______, _______, 
    _______, _______, _______, _______, _______, _______,     _______, FR_1   , FR_2   , FR_3   , _______, _______, 
    _______, _______, _______, _______, _______, _______,     _______, FR_0, FR_0   , COMM_RCTL, _______, _______
),


};

const size_t N_LAYERS = sizeof(keymaps) / (MATRIX_ROWS * MATRIX_COLS * sizeof(uint16_t));

//Setup config struct for LED
typedef union {
  uint32_t raw;
  struct {
    uint8_t  red_mode :8;
    uint8_t  green_mode :8;
  };
} led_config_t;
led_config_t led_config;

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    // escape, space and enter require a swift mod change
    // case FR_ESC:
    // case NM_SPC:
    // case CD_ENT:
    // case FR_QUO:
    //   return 150;

    // a, u, s and i require some lagging
    // because the pinky and ring fingers
    // can lag a bit
    // case LCTL_A:
    case RGUI_J:
    case RCTL_K:
    case RCTL_L:

    case LGUI_F:
    case LCTL_S:
    // case LALT_S:
    // case RALT_I:
      return 150;
    case LCTL_D:
      return 10;
    case M_CODE:
      return 10;

    default:
      return TAPPING_TERM;
    }
}

//Set leds to saved state during powerup
void keyboard_post_init_user(void) {
    debug_enable = true;
    // debug_matrix=true;
    debug_keyboard = true;

  // set LED pin modes
  setPinOutput(LED_RED);
  setPinOutput(LED_GREEN);

  // Call the post init code.
  led_config.raw = eeconfig_read_user();

  if(led_config.red_mode == LEDMODE_ON) {
      writePinHigh(LED_RED);
      
      // TODO
      // Hack to have blue led always on.
      // writePinHigh(LED_GREEN);
  }

  if(led_config.green_mode == LEDMODE_ON) {
      // writePinHigh(LED_RED);
      writePinHigh(LED_GREEN);
  }
}

void eeconfig_init_user(void) {  // EEPROM is getting reset! 
  led_config.raw = 0;
  led_config.red_mode = LEDMODE_MODS;
  led_config.green_mode = LEDMODE_ON;
  eeconfig_update_user(led_config.raw);
  eeconfig_update_user(led_config.raw);
}

layer_state_t layer_state_set_user(layer_state_t state) {
  // layer_state_set_hid(state);
  // return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
  // return update_tri_layer_state(state, _CODE, _NUMBERS, _ADJUST);
  return state;
}

void led_keypress_update(uint8_t led, uint8_t led_mode, uint16_t keycode, keyrecord_t *record) {
    switch (led_mode) {
      case LEDMODE_MODS:
        for (int i=0;i<ARRAY_SIZE(modifiers);i++) {
          if(keycode==modifiers[i]) {
            if (record->event.pressed) {
              writePinHigh(led);
            }
            else {
              writePinLow(led);
            }
          }
        }
        break;
      case LEDMODE_BLINKIN:
        if (record->event.pressed) {
          if(rand() % 2 == 1) {
            if(rand() % 2 == 0) {
              writePinLow(led);
            }
            else {
              writePinHigh(led);
            }
          }
        }
        break;
      case LEDMODE_KEY:
        if (record->event.pressed) {
          writePinHigh(led);
          return;
        }
        else {
          writePinLow(led);
          return;
        }
        break;
      case LEDMODE_ENTER:
        if (keycode==KC_ENT) {
          writePinHigh(led);
        }
        else {
          writePinLow(led);
        }
        break;

    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  // #ifdef KEYSTATS_ENABLE

    send_event_to_hid(keycode, record->event);
  // #endif

  /* If the either led mode is keypressed based, call the led updater
     then let it fall through the keypress handlers. Just to keep 
     the logic out of this procedure */
  if (led_config.red_mode >= LEDMODE_MODS && led_config.red_mode <= LEDMODE_ENTER) {
      led_keypress_update(LED_RED, led_config.red_mode, keycode, record);
  }
  if (led_config.green_mode >= LEDMODE_MODS && led_config.green_mode <= LEDMODE_ENTER) {
      led_keypress_update(LED_GREEN, led_config.green_mode, keycode, record);
  }
  switch (keycode) {
    case AZERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_AZERTY);
      }
      return false;
      break;
    // The code layer
    case CODE:
      if (record->event.pressed) {
        layer_on(_CODE);
      } else {
        layer_off(_CODE);
      }
      return false;
      break;

    // The number layer
    case NUMBERS:
      if (record->event.pressed) {
        layer_on(_NUMBERS);
      } else {
        layer_off(_NUMBERS);
      }
      return false;
      break;

    // The french layer
    case FRENCH:
      if (record->event.pressed) {
        layer_on(_FRENCH);
      } else {
        layer_off(_FRENCH);
      }
      return false;
      break;

    // The number layer
    case NUMBERS_NEW:
      if (record->event.pressed) {
        layer_on(_NUMBERS_NEW);
      } else {
        layer_off(_NUMBERS_NEW);
      }
      return false;
      break;

    case LED_1:
      if (record->event.pressed) {
        if (led_config.red_mode==LEDMODE_ON) {
            led_config.red_mode=LEDMODE_OFF;
            writePinLow(LED_RED);
        }
        else {
            led_config.red_mode=LEDMODE_ON;
            writePinHigh(LED_RED);
        }
      }
      eeconfig_update_user(led_config.raw);
      return false;
      break;
    case LED_2:
      if (record->event.pressed) {
        if (led_config.green_mode==LEDMODE_ON) {
            led_config.green_mode=LEDMODE_OFF;
            writePinLow(LED_GREEN);
        }
        else {
            led_config.green_mode=LEDMODE_ON;
            writePinHigh(LED_GREEN);
        }
      }
      eeconfig_update_user(led_config.raw);
      return false;
      break;
    case LED_3:
      led_config.red_mode=LEDMODE_MODS;
      eeconfig_update_user(led_config.raw);
      return false;
      break;
    case LED_4:
      led_config.green_mode=LEDMODE_MODS;
      eeconfig_update_user(led_config.raw);
      return false;
      break;
    case LED_5:
      led_config.red_mode=LEDMODE_BLINKIN;
      eeconfig_update_user(led_config.raw);
      return false;
      break;
    case LED_6:
      led_config.green_mode=LEDMODE_BLINKIN;
      eeconfig_update_user(led_config.raw);
      return false;
      break;
    case LED_7:
      led_config.red_mode=LEDMODE_KEY;
      eeconfig_update_user(led_config.raw);
      return false;
      break;
    case LED_8:
      led_config.green_mode=LEDMODE_KEY;
      eeconfig_update_user(led_config.raw);
      return false;
      break;
    case LED_9:
      led_config.red_mode=LEDMODE_ENTER;
      eeconfig_update_user(led_config.raw);
      return false;
      break;
    case LED_0:
      led_config.green_mode=LEDMODE_ENTER;
      eeconfig_update_user(led_config.raw);
      return false;
      break;
  }
  return true;
}
