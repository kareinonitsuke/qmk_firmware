#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum custom_keycodes {
  RGB_RST = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
   KC_ESC,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                                             KC_Y,                   KC_U,    KC_I,     KC_O,    KC_P,     KC_ESC,
   KC_GRV,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                                             KC_H,                   KC_J,    KC_K,     KC_L,    KC_SCLN,  KC_QUOT,
   KC_TAB,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                                             KC_N,                   KC_M,    KC_COMM,  KC_DOT,  KC_SLSH,  KC_BSLS,
             KC_LWIN, KC_NO,MO(_ADJUST),KC_LALT, LT(MO(_LOWER), KC_SPC), LCTL_T(KC_DEL),         LSFT_T(KC_BSPC),  LT(MO(_RAISE), KC_ENT), KC_BSPC, KC_NO,    KC_NO,   KC_NO
  ), 


  [_LOWER] = LAYOUT(
   KC_NO,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                                         KC_6,               KC_7,    KC_8,     KC_9,    KC_0,     KC_NO,
   KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                                                        KC_F7,              KC_F8,   KC_F9,    KC_F10,  KC_F11,   KC_F12,
   KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_LALT, KC_NO,                                                        KC_NO,              KC_NO,   KC_NO,    KC_LEFT, KC_UP,    KC_RGHT,
             KC_NO,   KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS,                KC_TRNS,          KC_TRNS,            KC_TRNS, KC_NO,    KC_NO,   KC_DOWN
  ),



  [_RAISE] = LAYOUT(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                                                      KC_CIRC,            KC_AMPR, KC_ASTR,  KC_LPRN, KC_RPRN,  KC_DQT,
    KC_NO,   KC_LPRN, KC_RPRN, KC_LCBR, KC_RCBR, KC_NO,                                                        KC_UNDS,            KC_MINS, KC_PLUS,  KC_EQL,  KC_COLN,  KC_PIPE,
    RESET,   KC_LABK, KC_RABK, KC_LBRC, KC_RBRC, KC_NO,                                                        KC_NO,              KC_NO,   KC_LABK,  KC_RABK, KC_QUES,  KC_NO,
             KC_NO,   KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS,                KC_TRNS,          KC_TRNS,            KC_TRNS, KC_NO,    KC_NO,   KC_NO
  ),


  [_ADJUST] = LAYOUT(
    RESET,   RESET,   RGB_RST, KC_NO,   KC_NO,   KC_NO,                                                        KC_NO,              KC_NO,   KC_NO,   KC_NO,    KC_NO,    KC_NO,
    KC_NO,   RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, KC_NO,                                                        KC_NO,              KC_NO,   KC_NO,   KC_NO,    KC_NO,    KC_NO,
    KC_NO,   RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, KC_NO,                                                        KC_NO,              KC_NO,   KC_NO,   KC_NO,    KC_NO,    KC_NO,
             KC_NO,   KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS,                KC_TRNS,          KC_TRNS,            KC_TRNS, KC_NO,   KC_NO,    KC_NO
  ),
};

int RGB_current_mode;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  bool result = false;
  switch (keycode) {
    #ifdef RGBLIGHT_ENABLE
      case RGB_MOD:
          if (record->event.pressed) {
            rgblight_mode(RGB_current_mode);
            rgblight_step();
            RGB_current_mode = rgblight_config.mode;
          }
        break;
      case RGB_RST:
          if (record->event.pressed) {
            eeconfig_update_rgblight_default();
            rgblight_enable();
            RGB_current_mode = rgblight_config.mode;
          }
        break;
    #endif
    default:
      result = true;
      break;
  }

  return result;
}

void matrix_init_user(void) {

}

