#include QMK_KEYBOARD_H
enum {
TD_HMIN=0,
TD_MINPL,
TD_COMMIN,
    };

enum {

CTL_A    =  CTL_T(KC_A),
CTL_SCLN =  CTL_T(KC_SCLN),
ALT_S    =  ALT_T(KC_S),
ALT_L    =  ALT_T(KC_L),
SFT_Z    =  LSFT_T(KC_Z),
SFT_SLSH =  RSFT_T(KC_SLSH),
GUI_X    =  GUI_T(KC_X),
GUI_DOT  = GUI_T(KC_DOT),

LT1_B    =  LT(1,KC_B),
LT2_V    =  LT(2, KC_V),
LT3_F    =  LT(3, KC_F),
LT4_G    =  LT(4,KC_G),
LT3_FN9  =  LT(3, KC_F9),
LT3_FN8  =  LT(3, KC_F8),
LT2_FN12  =  LT(2, KC_F12),
GUI_SFT  =  LGUI(KC_LSFT),
GUI_CTL  =  LGUI(KC_LCTL),
GUI_ALT  =  LGUI(KC_LALT),
TD_CMIN  =  TD(TD_COMMIN),
TD_MPL   =  TD(TD_MINPL),
ESC_MHEN =  SAFE_RANGE,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT_ortho_3x10(
    KC_Q,   KC_W,   KC_E,    KC_R,   KC_T,    KC_Y   ,    KC_U,    KC_I,    KC_O,     KC_P,
   CTL_A,  ALT_S,   KC_D,   LT3_F,  LT4_G,    KC_H   ,    KC_J,    KC_K,   ALT_L, CTL_SCLN,
   SFT_Z,  GUI_X,   KC_C,   LT2_V,  LT1_B,    KC_N   ,    KC_M, TD_CMIN, GUI_DOT, SFT_SLSH
  ),

  [1] = LAYOUT_ortho_3x10(
    KC_F1,   KC_F2,  KC_F3,     KC_F4,  KC_COMM,     KC_DOT,   KC_7,  KC_8,  KC_9, KC_BSPC,
    KC_F5,   KC_F6,  KC_F7,   LT3_FN8,  KC_EQL,      TD_MPL,   KC_4,  KC_5,  KC_6, KC_TAB,
    KC_F9,  KC_F10,  KC_F11, LT2_FN12,  _______,       KC_0,   KC_1,  KC_2,  KC_3, KC_ENT
  ),

  [2] = LAYOUT_ortho_3x10(
    KC_EXLM,  KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
    KC_TILD, KC_PIPE,  _______,   MO(3), _______, KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_QUOT,
     KC_GRV, KC_BSLS,  _______, _______,   MO(1), KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_DQUO
  ),

  [3] = LAYOUT_ortho_3x10(
    ESC_MHEN, KC_TAB, KC_INT4, _______, _______, KC_BSPC, _______, _______, KC_DEL, KC_BSPC,
    GUI_CTL, GUI_ALT, KC_INT5, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT,  KC_SPC,
    GUI_SFT, KC_LGUI, _______, _______, QK_BOOT, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_ENT
  ),
  
  [4] = LAYOUT_ortho_3x10(
    KC_ESC,   KC_TAB, KC_INT4, KC_VOLU, _______, _______, _______, _______, KC_DEL, KC_BSPC,
    GUI_CTL, GUI_ALT, KC_INT5, KC_VOLD, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,  KC_BTN1,
    GUI_SFT, KC_LGUI, _______, KC_MUTE, QK_BOOT, KC_BTN3, KC_WH_D, KC_WH_U, KC_BTN2, KC_ENT
  )


};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  bool result = false;
  switch (keycode) {
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
};

bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
  bool result = false;
  switch (keycode) {
    case GUI_DOT:
      result = false;
      break;
    case GUI_X:
      result = false;
      break;
    case CTL_A:
      result = true;
      break;
    case ALT_S:
      result = true;
      break;
    case ALT_L:
      result = true;
      break;
    case CTL_SCLN:
      result = true;
      break;
    case SFT_Z:
      result = true;
      break;
    case SFT_SLSH:
      result = true;
      break;
    default:
      result = false;
      break;
  }
  return result;
}
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
      case CTL_A:
        return 230;
        break;
      case ALT_S:
        return 230;
        break;
      case ALT_L:
        return 230;
        break;
      case CTL_SCLN:
        return 230;
        break;
      default:
        return TAPPING_TERM;
    }
}

bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        default:
            return true;
    }
}


qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_HMIN] = ACTION_TAP_DANCE_DOUBLE(KC_H,KC_MINS),
  [TD_MINPL] = ACTION_TAP_DANCE_DOUBLE(KC_MINS,KC_PLUS),
  [TD_COMMIN]=ACTION_TAP_DANCE_DOUBLE(KC_COMM,KC_MINS)
 };

