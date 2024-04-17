// cOPYRIGHT 2022 mARK sTOSBERG (@MARKSTOS)
// spdx-lICENSE-iDENTIFIER: gpl-2.0-OR-LATER
#include QMK_KEYBOARD_H

// TODO: enable permissive hold only for thumb keys, because i press them for layer too fast, e.g: left_layer + i for searching in vim
// Macros I need:
// 1. I define lots of dictionaries in python and objects in javascript, so i need a macro to print " = {"
// 2. open terminal in vs code
// 3. copy currently selected text, open browser workspace, send ctrl+t then paste, then send enter to do search
// 4. send ":wq", am I brave enough to use this?

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  FUNC,
  MISC,
  BACKLIT,
  MACRO_1,
  MACRO_2,
  MACRO_3,
  MACRO_4,
  MACRO_5,
  MACRO_6,
  MACRO_7
};

enum combos {
  DF_DASH,
  JK_ESC,
  FJ_TILDE
};

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum custom_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _FUNC,
  _MISC,
};

// For _QWERTY layer
#define OSM_LCTL OSM(MOD_LCTL)
#define OSM_AGR  OSM(MOD_RALT)
#define OSL_FUN  OSL(_FUNC)
#define GUI_SPC  GUI_T(KC_SPC)

#define HM_A LALT_T(KC_A)
#define HM_S LCTL_T(KC_S)
#define HM_D RSFT_T(KC_D)
#define HM_F LGUI_T(KC_F)
#define HM_J RGUI_T(KC_J)
#define HM_K RSFT_T(KC_K)
#define HM_L RCTL_T(KC_L)
#define HM_QUOT LALT_T(KC_QUOT)

#define HM_Z LALT_T(KC_Z)
#define HM_X LCTL_T(KC_X)
#define HM_C RSFT_T(KC_C)
#define HM_V LGUI_T(KC_V)
#define HM_M RGUI_T(KC_M)
#define HM_COMM RSFT_T(KC_COMM)
#define HM_DOT RCTL_T(KC_DOT)
#define HM_SLSH LALT_T(KC_SLSH)

#define LOW_TAB  LT(_LOWER, KC_TAB)
#define RSE_BSP  LT(_RAISE, KC_BSPC)
#define MSC_ESC  LT(_MISC, KC_ESC)
#define OSM_SFT  OSM(MOD_LSFT)

const uint16_t PROGMEM df_combo[] = {HM_D, HM_F, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {HM_J, HM_K, COMBO_END};
const uint16_t PROGMEM fj_combo[] = {HM_F, HM_J, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  // Add commonly used underscore to home row (i use snake case naming a lot)
  [DF_DASH]    = COMBO(df_combo, KC_UNDS),
  // For Vim, put Escape on the home row
  [JK_ESC]     = COMBO(jk_combo, KC_ESC),
  [FJ_TILDE]   = COMBO(fj_combo, KC_TILDE),
};

// Tap Dance declarations
enum {
    TD_1,
    TD_2,
    TD_3,
    TD_4,
    TD_5
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for first key, twice for second key
    // characters are tricky for tab dance, the easy to access ones are common in words too, like e, m, c
    // tab dance is not for normal characters, it is not practical, I have to find specific letters that do not repeat, until now v is the only one, accessible and not repeating
    [TD_1] = ACTION_TAP_DANCE_DOUBLE(KC_M, KC_EQL),// common => co=on
    [TD_2] = ACTION_TAP_DANCE_DOUBLE(KC_R, KC_COLON),// arrange => a:ange
    [TD_3] = ACTION_TAP_DANCE_DOUBLE(KC_V, KC_UNDS),
    [TD_4] = ACTION_TAP_DANCE_DOUBLE(KC_E, KC_MINS),// feel => f-l
    [TD_5] = ACTION_TAP_DANCE_DOUBLE(KC_RBRC, KC_EQL), //closing bracket is perfect for tab dance, it is barely ever used, since IDEs auto close it, I really needed the equal in the numbers/symbols layer
};

// For _RAISE layer
#define CTL_ESC  LCTL_T(KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,KC_E    ,    KC_R,    KC_T,                     KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_DEL  ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
 OSM(MOD_LALT),   HM_A,    HM_S,    HM_D,    HM_F,    KC_G,                     KC_H    ,HM_J    ,HM_K    ,HM_L    ,HM_QUOT ,OSM_AGR ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
 OSM(MOD_LSFT),   KC_Z,    KC_X,    KC_C,TD(TD_3),    KC_B,                     KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,OSL_FUN ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         MSC_ESC , KC_SPC, LOW_TAB,    RSE_BSP ,KC_ENT , KC_COLON
                                      //`--------------------------'  `--------------------------'
  ),

  [_LOWER] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_EXLM, KC_AT,  KC_HASH, KC_DLR,  KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______ ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_1,    KC_2,   KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______ ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, KC_TILD,KC_GRV, KC_LBRC, KC_LCBR,                       KC_RCBR ,TD(TD_5), KC_COMM,KC_DOT,  KC_SLSH, _______ ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS,  KC_TRNS, LOWER,    KC_TRNS, KC_TRNS, KC_TRNS
                                      //`--------------------------'  `--------------------------'
    ),


  [_RAISE] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, MACRO_7, XXXXXXX, KC_MINS, KC_PLUS, KC_PGUP,                      MACRO_1, MACRO_2, MACRO_3, KC_BSLS, KC_PIPE,_______ ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_HOME, KC_END , KC_UNDS, KC_EQL , KC_PGDN,                      KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, MACRO_6 ,_______ ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_PMNS, KC_PPLS, KC_COPY, KC_PSTE, KC_SCLN,                      MACRO_4, MACRO_5, KC_APP, KC_VOLD, KC_VOLU,_______ ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          CTL_ESC, KC_TRNS, XXXXXXX,    RAISE  , KC_TRNS, KC_TRNS
                                      //`--------------------------'  `--------------------------'
  ),

  [_FUNC] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_F1  , KC_F2  , KC_F3   , KC_F4 ,  KC_F5 ,                     KC_F6   , KC_F7  , KC_F8  , KC_F9  , KC_F10 ,_______ ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_F11 , KC_F12 , XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX, QK_RBT ,_______ ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,XXXXXXX ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, FUNC   , XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

  [_MISC] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,_______ ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, KC_WH_U, KC_WH_D, XXXXXXX,                     KC_MS_L , KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX,_______ ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX , KC_BTN4, KC_BTN5, XXXXXXX, XXXXXXX,XXXXXXX ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          MISC   , XXXXXXX, XXXXXXX,   KC_BTN1 ,KC_BTN2 , KC_BTN3
                                      //`--------------------------'  `--------------------------'
  )
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
      case LT(_RAISE, KC_BSPC):
            return TAPPING_TERM_THUMB;
      case LT(_LOWER, KC_TAB):
            return TAPPING_TERM_THUMB;
      default:
            return TAPPING_TERM;
    }
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case MACRO_1:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
           SEND_STRING("\e:wq");
        } else {
            // when keycode QMKBEST is released
        }
        break;

    case MACRO_2:
        if (record->event.pressed) {
           SEND_STRING(SS_LCTL(SS_LSFT("~")));
        }
        break;

    case MACRO_3:
        if (record->event.pressed) {
           SEND_STRING(SS_LCTL("`"));
        }
        break;

    case MACRO_4:
        if (record->event.pressed) {
           SEND_STRING(SS_LCTL("c") SS_LGUI("w") SS_DELAY(200) SS_LCTL("t") SS_DELAY(300) SS_LCTL("v"));
        }
        break;

    case MACRO_5:
        if (record->event.pressed) {
           SEND_STRING(" = ");
        }
        break;

    case MACRO_6:
        if (record->event.pressed) {
           SEND_STRING("g;");
        }
        break;

    case MACRO_7:
        if (record->event.pressed) {
           SEND_STRING("\e0w");
        }
        break;

    }  // end of switch block

    return true;
};

