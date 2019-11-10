/* Copyright 2019 karei_key
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

// Defines the keycodes used by our macros in process_record_user

enum layer_number {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST
};
enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGBRST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(\
             KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                                         KC_Y,               KC_U,    KC_I,     KC_O,    KC_P,\
   KC_GRV,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                                         KC_H,               KC_J,    KC_K,     KC_L,    KC_SCLN,  KC_QUOT,\
   KC_TAB,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                                         KC_N,               KC_M,    KC_COMM,  KC_DOT,  KC_SLSH,  KC_BSLS,\
   KC_ESC,   KC_LWIN, KC_NO,   ADJUST,  KC_LALT, LT(_LOWER, KC_SPC), LCTL_T(KC_DEL),         LSFT_T(KC_BSPC),  LT(_RAISE, KC_ENT), KC_BSPC, KC_NO,    KC_NO,   KC_NO,    KC_ESC\
  ), 

  [_RAISE] = LAYOUT(\
             KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                                                      KC_CIRC,            KC_AMPR, KC_ASTR,  KC_LPRN, KC_RPRN,\
    KC_TILD, KC_LPRN, KC_RPRN, KC_LCBR, KC_RCBR, KC_NO,                                                        KC_UNDS,            KC_MINS, KC_PLUS,  KC_EQL,  KC_COLN,  KC_DQT,\
    KC_NO,   KC_LABK, KC_RABK, KC_LBRC, KC_RBRC, KC_NO,                                                        KC_NO,              KC_NO,   KC_LABK,  KC_RABK, KC_QUES,  KC_PIPE,\
    RESET,   KC_NO,   KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS,                KC_TRNS,          KC_TRNS,            KC_TRNS, KC_NO,    KC_NO,   KC_NO,    KC_NO \
  ),

  [_LOWER] = LAYOUT(
             KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                                         KC_6,               KC_7,    KC_8,     KC_9,    KC_0,\
   KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                                                        KC_F7,              KC_F8,   KC_F9,    KC_F10,  KC_F11,   KC_F12,\
   KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_LALT, KC_NO,                                                        KC_NO,              KC_NO,   KC_NO,    KC_LEFT, KC_UP,    KC_RGHT,\
   KC_NO,    KC_NO,   KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS,                KC_TRNS,          KC_TRNS,            KC_TRNS, KC_NO,    KC_NO,   KC_DOWN,  KC_NO\
  ),

  [_ADJUST] = LAYOUT(\
             RESET,   RGB_RST,  KC_NO,   KC_NO,  KC_NO,                                                        KC_NO,              KC_NO,   KC_NO,   KC_NO,    KC_NO,\
    RESET,   RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, KC_NO,                                                        KC_NO,              KC_NO,   KC_NO,   KC_NO,    KC_NO,    KC_NO,\
    KC_NO,   RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, KC_NO,                                                        KC_NO,              KC_NO,   KC_NO,   KC_NO,    KC_NO,    KC_NO,\
    KC_NO,   KC_NO,   KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS,                KC_TRNS,          KC_TRNS,            KC_TRNS, KC_NO,   KC_NO,    KC_NO,    KC_NO\
  ) 
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
  #ifdef SSD1306OLED
    set_keylog(keycode, record);
  #endif
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        //persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      return false;
      break;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          //rgblight_mode(RGB_current_mode);
          //rgblight_step();
          //RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGB_RST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
         //eeconfig_update_rgblight_default();
          //rgblight_enable();
          //RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  return true;
}








