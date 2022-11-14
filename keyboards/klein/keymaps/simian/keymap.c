#include QMK_KEYBOARD_H
#include <stdio.h>
#include <string.h>
#include "klein.h"


enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_LOWER,
    LAYER_RAISE,
    LAYER_ADJUST,
    LAYER_NUMPAD,
    // LAYER_FUNCTION,
    // LAYER_NAVIGATION,
    // LAYER_MEDIA,
    LAYER_POINTER,
    // LAYER_NUMERAL,
    // LAYER_SYMBOLS,
};



#define _L_PTR(KC) LT(LAYER_POINTER, KC)

// Thumb clusters
#define NUM_TAB LT(LAYER_NUMPAD, KC_TAB)
#define LW_BSPC LT(LAYER_LOWER, KC_BSPC)
#define RAI_DEL LT(LAYER_RAISE, KC_DEL)
#define NUM_ESC LT(LAYER_NUMPAD, KC_ESC)

#define ALT_F2 MT(MOD_LALT, KC_F2)
#define CTL_F1 MT(MOD_LCTL, KC_F1)

// Numpad layer home row mods
#define SFT_UP RSFT_T(KC_UP)

// Right hand
#define ADJ_KCQ LT(LAYER_ADJUST, KC_Q)
#define ALT_DOT MT(MOD_LALT, KC_DOT)
#define ADJ_KCSLASH LT(LAYER_ADJUST, KC_SLSH)


// Thumb Cluster
#define RAI_ENT LT(LAYER_RAISE, KC_ENT)
#define LW_SPC LT(LAYER_LOWER, KC_SPC)

// Lower
#define CTL_F10 MT(MOD_LCTL, KC_F10)
#define ALT_F9 MT(MOD_LALT, KC_F9)

// Raise
// Home row mods
#define CTL_EQL RCTL_T(KC_EQL)



#define LAYOUT_LAYER_BASE                                                                                             \
        ADJ_KCQ,    KC_W,    KC_E,    KC_R,     KC_T,                 KC_Y,    KC_U,    KC_I,    KC_O,   KC_P, \
               KC_A,   KC_S,   KC_D,   KC_F,    KC_G,                 KC_H,   KC_J,    KC_K,  KC_L,   KC_SCLN,  \
              KC_Z,   KC_X,    KC_C,   KC_V,    KC_B,                 KC_N,    KC_M, KC_COMM,  KC_DOT,ADJ_KCSLASH, \
                           NUM_TAB, LW_BSPC, RAI_DEL,                 RAI_ENT,  LW_SPC, NUM_ESC

#define LAYOUT_LAYER_POINTER                                                                                                                                        \
          _______ , _______, _______, _______,_______,               KC_BTN1,_______, _______,_______, _______, \
           _______, _______, _______,_______ ,_______,               KC_BTN2, _______, _______, _______, _______,                                                                       \
       _______,_______, _______, _______,_______,                    _______, _______, _______, _______, _______,                                                                     \
                            _______, KC_BTN1, KC_BTN2,               _______, _______, _______

// Lower
#define LAYOUT_LAYER_LOWER                                                                                                  \
          G(KC_1), G(KC_2), G(KC_3),  G(KC_4),G(KC_5),               G(KC_6),  G(KC_7),G(KC_8),  G(KC_9),G(KC_0),            \
          KC_WBAK, KC_WFWD, KC_HOME,   KC_END, KC_APP,               KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT,  KC_F6,         \
           CTL_F1,   ALT_F2,C(G(KC_LEFT)),C(G(KC_RIGHT)),KC_F5,            KC_F5,   KC_F7,    KC_F8,  ALT_F9, CTL_F10,         \
                            _______, _______, _______,               _______, _______, _______

// Raise
#define LAYOUT_LAYER_RAISE                                                                                                  \
      KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_QUOT, KC_GRV,          \
      KC_QUOT,KC_DQT,   KC_LPRN, KC_RPRN, KC_PGUP,                   KC_MINS, CTL_EQL, KC_LCBR, KC_RCBR,KC_BSLS,        \
      KC_ESC,_______,KC_ESC,KC_ENT,KC_PGDOWN,                        KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_PIPE,         \
                            _______, _______, _______,               _______, _______, _______

// Adjust
#define LAYOUT_LAYER_ADJUST                                                                                                                 \
XXXXXXX, TG(LAYER_NUMPAD), KC_CAPS, XXXXXXX, XXXXXXX,                QK_BOOT, XXXXXXX, XXXXXXX,XXXXXXX , XXXXXXX,       \
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                  XXXXXXX, KC_WBAK, KC_WFWD, KC_APP, XXXXXXX,                        \
       XXXXXXX,XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,                  XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       \
                            _______, _______, _______,               KC_VOLD, KC_VOLU, KC_MPLY

// Numpad
#define LAYOUT_LAYER_NUMPAD                                                                                       \
   TG(LAYER_NUMPAD), KC_F9,   KC_F8,  KC_F7,  KC_F12,                KC_CIRC,   KC_7,   KC_8,   KC_9, KC_ASTR,\
        KC_NO,       KC_F6,   KC_F5,  KC_F4,  KC_F11, 			         KC_MINS,   KC_4,   KC_5,   KC_6,  KC_EQL,\
	       KC_LSFT,  KC_F3,   KC_F2,  KC_F1,  KC_F10,		      		     KC_PLUS,   KC_1,   KC_2,   KC_3, KC_SLSH,\
                            _______, _______, _______,               KC_ENT,    KC_0, KC_DOT


  #define _HOME_ROW_MOD_GACS(                                            \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                  \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                  \
    L20, L21, L22, L23, L24, R25, R26, R27, R28, R29,                  \
    ...)                                                               \
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
     LGUI_T(L10), LALT_T(L11), LSFT_T(L12), LCTL_T(L13),        L14,  \
             R15,  RCTL_T(R16), RSFT_T(R17), LALT_T(R18), RGUI_T(R19), \
     LCTL_T(L20),         L21,         L22,         L23,         L24,  \
             R25,         R26,         R27,         R28,         R29, \
      __VA_ARGS__
#define HOME_ROW_MOD_GACS(...) _HOME_ROW_MOD_GACS(__VA_ARGS__)

#define _HOME_ROW_MOD_LEFT_GACS(                                            \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                  \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                  \
    L20, L21, L22, L23, L24, R25, R26, R27, R28, R29,                  \
    ...)                                                               \
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
     LGUI_T(L10), LALT_T(L11), LSFT_T(L12), LCTL_T(L13),         L14,  \
             R15,         R16,         R17,         R18,         R19, \
     LCTL_T(L20),         L21,         L22,         L23,         L24,  \
             R25,         R26,         R27,         R28,         R29, \
      __VA_ARGS__
#define HOME_ROW_MOD_LEFT_GACS(...) _HOME_ROW_MOD_LEFT_GACS(__VA_ARGS__)

/**
 * \brief Add pointer layer keys to a layout.
 *
 * Expects a 10-key per row layout.  The layout passed in parameter must contain
 * at least 30 keycodes.
 *
 * This is meant to be used with `LAYER_ALPHAS_QWERTY` defined above, eg.:
 *
 *     POINTER_MOD(LAYER_ALPHAS_QWERTY)
 */
#define _POINTER_MOD(                                                  \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                  \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                  \
    L20, L21, L22, L23, L24, R25, R26, R27, R28, R29,                  \
    ...)                                                               \
             L00,         L01,         L02,        L03,         L04,  \
             R05,         R06, _L_PTR(R07),        R08,         R09,  \
             L10,         L11,         L12,        L13,         L14,  \
             R15,         R16,         R17,        R18,         R19,  \
             L20,         L21, _L_PTR(L22),        L23,         L24,  \
             R25,         R26,         R27,        R28,         R29, \
      __VA_ARGS__
#define POINTER_MOD(...) _POINTER_MOD(__VA_ARGS__)

#define LAYOUT_wrapper(...) LAYOUT_klein_3x5(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT_wrapper(
    POINTER_MOD(HOME_ROW_MOD_GACS(LAYOUT_LAYER_BASE))
  ),
   [LAYER_POINTER] = LAYOUT_wrapper(LAYOUT_LAYER_POINTER),
   [LAYER_LOWER] = LAYOUT_wrapper(HOME_ROW_MOD_LEFT_GACS(LAYOUT_LAYER_LOWER)),
   [LAYER_RAISE] = LAYOUT_wrapper(LAYOUT_LAYER_RAISE),
   [LAYER_ADJUST] = LAYOUT_wrapper(LAYOUT_LAYER_ADJUST),
   [LAYER_NUMPAD] = LAYOUT_wrapper(HOME_ROW_MOD_GACS(LAYOUT_LAYER_NUMPAD))

};
// clang-format on

#   ifdef TAPPING_TERM_PER_KEY

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LGUI_T(KC_A):
        case RGUI_T(KC_SCLN):
            return TAPPING_TERM + 50;
        case LALT_T(KC_S):
        case LALT_T(KC_L):
            return TAPPING_TERM + 50;
        default:
            return TAPPING_TERM;
    }
}
#   endif //TAPPING_TERM_PER_KEY


bool encoder_update_user(uint8_t index, bool clockwise) {

    //if (clockwise) {
        //tap_code(KC_WH_D);
    //} else {
        //tap_code(KC_WH_U);
    //}
    //if (get_highest_layer(layer_state|default_layer_state) > 0) {
        if (IS_LAYER_ON(LAYER_ADJUST)) {
            if (clockwise) {
                tap_code_delay(KC_VOLU, 10);
            } else {
                tap_code_delay(KC_VOLD, 10);
            }
        } else if(IS_LAYER_ON(LAYER_LOWER)) {
            if (clockwise) {
                 tap_code16(C(KC_TAB));
            } else {
                 tap_code16(C(S(KC_TAB)));
            }
        } else if(IS_LAYER_ON(LAYER_RAISE)) {
            if (clockwise) {
                tap_code16(KC_WH_U);
                tap_code16(KC_WH_U);
                tap_code16(KC_WH_U);
                tap_code16(KC_WH_U);
                tap_code16(KC_WH_U);
            } else {
                tap_code16(KC_WH_D);
                tap_code16(KC_WH_D);
                tap_code16(KC_WH_D);
                tap_code16(KC_WH_D);
                tap_code16(KC_WH_D);
            }
        } else if(IS_LAYER_ON(LAYER_NUMPAD)) {
            if (clockwise) {
                 tap_code16(KC_RIGHT);
            } else {
                 tap_code16(KC_LEFT);
            }
        } else{
            if (clockwise) {
                //tap_code(KC_WH_D);
                tap_code16(KC_WH_U);
            } else {
                //tap_code(KC_WH_U);
                 tap_code16(KC_WH_D);
            }
        }
    //}
    //} else {  /* Layer 0 */
        //if (index == 0) {
            //if (clockwise) {
                //tap_code(KC_PGDN);
            //} else {
                //tap_code(KC_PGUP);
            //}
        //}
        ////else if (index == 1) {
            ////if (clockwise) {
                ////rgb_matrix_increase_speed();
            ////} else {
                ////rgb_matrix_decrease_speed();
            ////}
        ////}
    //}
    return false;
}


