#include QMK_KEYBOARD_H


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
  _LAYER0 = 0,
  _LAYER1,
  _LAYER2,
  _LAYER3,
  _LAYER4,
};

enum custom_keycodes {
  RGB_RST = SAFE_RANGE,
  ESC_MHEN = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 [_LAYER0] = LAYOUT(
  KC_NO, KC_Q       , KC_W       , KC_E , LT(1,KC_R)   , KC_T      , KC_Y , KC_U         , KC_I   , KC_O         , KC_P          , KC_NO,
  KC_NO, CTL_T(KC_A), ALT_T(KC_S), KC_D , LT(3,KC_F)   , LT(4,KC_G), KC_H , KC_J         , KC_K   , ALT_T(KC_L)  , CTL_T(KC_SCLN), KC_NO,
  KC_NO, SFT_T(KC_Z), GUI_T(KC_X), KC_C , LT(2,KC_V)   , KC_B, KC_N , KC_M         , KC_COMM, GUI_T(KC_DOT), SFT_T(KC_SLSH), KC_NO,
  KC_NO, KC_NO      , KC_NO      , KC_NO, KC_NO        , KC_NO     , KC_NO, KC_NO, KC_NO  , KC_NO        , KC_NO         , KC_NO
  ),

[_LAYER1] = LAYOUT(
  KC_NO, KC_F1 , KC_F2 , KC_F3 , KC_TRNS, KC_F10, KC_1  , KC_2   , KC_3  , KC_4   , KC_5   , KC_NO,
  KC_NO, KC_F4 , KC_F5 , KC_F6 , KC_TRNS, KC_F11 , KC_6  , KC_7   , KC_8  , KC_9   , KC_0   , KC_NO,
  KC_NO, KC_F7 , KC_F8 , KC_F9 , KC_NO  , KC_F12, KC_QUOT, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_NO,
  KC_NO, KC_NO , KC_NO , KC_NO , KC_NO  , KC_NO, KC_NO , KC_NO  , KC_NO , KC_NO  , KC_NO  , KC_NO
  ), 

[_LAYER2] = LAYOUT(
  KC_NO, KC_TILD, KC_PIPE, KC_DQUO, KC_NO  , KC_NO , KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC, KC_NO,
  KC_NO, KC_GRV , KC_BSLS, KC_QUOT, KC_TRNS, KC_TRNS, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_NO,
  KC_NO, KC_LSFT, KC_LGUI, MO(4)  , KC_TRNS, KC_NO  , KC_DQUO, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_NO,
  KC_NO, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO
  ),

[_LAYER3] = LAYOUT(
  KC_NO  , ESC_MHEN     , KC_TAB        , KC_INT4, KC_NO  , KC_NO , KC_BSPC , KC_NO , KC_NO , KC_DEL , KC_BSPC, KC_NO,
  KC_TRNS, LGUI(KC_LCTL), LGUI(KC_LALT) , KC_SPC , KC_TRNS, KC_F10, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_SPC, KC_NO,  
  KC_TRNS, LGUI(KC_LSFT), KC_LGUI       , KC_INT5 , KC_TRNS, KC_NO , KC_HOME, KC_PGDN, KC_PGUP, KC_END , KC_ENT , KC_NO,
  KC_NO  , KC_NO        , KC_NO         , KC_NO  , KC_NO  , KC_NO , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO , KC_NO
  ),

[_LAYER4] = LAYOUT(
  //,-----------------------------------------------------|                 |-----------------------------------------------------.
      _______, RGB_RST, RGB_MOD , RGB_SPI, XXXXXXX, KC_VOLU,                       RGB_RST, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
      _______, RGB_TOG, RGB_HUI , RGB_SAI, RGB_VAI, KC_VOLD,                       KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_BTN1,KC_NO,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
      _______, QK_BOOT,QK_REBOOT, XXXXXXX, KC_MUTE, KC_TRNS,                       KC_BTN3, KC_WH_D, KC_WH_U, KC_BTN2, KC_NO ,KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
               _______, _______ , _______, _______, _______,   QK_BOOT,   QK_BOOT, _______, _______, _______, _______, _______
          //`------------------------------------------------------------------------------------------------------------'
  )

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
      case ESC_MHEN:
        if(record->event.pressed) {
         register_code(KC_ESC); 
         register_code(KC_INT5);
        }
        result = true;
        break;
      
    default:
      result = true;
      break;
  }

  return result;
}
