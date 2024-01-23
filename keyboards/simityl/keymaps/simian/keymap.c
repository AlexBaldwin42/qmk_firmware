/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_LOWER,
    LAYER_RAISE,
    LAYER_ADJUST,
    LAYER_NUMPAD,
    LAYER_POINTER,
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
#define ADJ_SLSH LT(LAYER_ADJUST, KC_SLSH)

// Thumb Cluster
#define RAI_ENT LT(LAYER_RAISE, KC_ENT)
#define LW_SPC LT(LAYER_LOWER, KC_SPC)

// Lower
#define CTL_F10 MT(MOD_LCTL, KC_F10)
#define ALT_F9 MT(MOD_LALT, KC_F9)

// Raise
// Home row mods
#define CTL_EQL RCTL_T(KC_EQL)

// Combos
enum combos{
 DF_DQT,
  SD_QT
};

const uint16_t PROGMEM df_combo[] = {LSFT_T(KC_D), LCTL_T(KC_F), COMBO_END};
const uint16_t PROGMEM sd_combo[] = {LALT_T(KC_S), LSFT_T(KC_D),  COMBO_END};

#define COMBO_COUNT 2
combo_t key_combos[COMBO_COUNT] = {
  [DF_DQT] = COMBO(df_combo, KC_DQT),
  [SD_QT] = COMBO(sd_combo, KC_QUOT)
};

// clang-format off
#define LAYOUT_LAYER_BASE                                                                                          \
         ADJ_KCQ,    KC_W,     KC_E,   KC_R,    KC_T,                  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,   \
            KC_A,    KC_S,     KC_D,   KC_F,    KC_G,                  KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,   \
            KC_Z,    KC_X,     KC_C,   KC_V,    KC_B,                  KC_N,    KC_M, KC_COMM,  KC_DOT,ADJ_SLSH,   \
                            NUM_TAB,LW_BSPC, RAI_DEL,               RAI_ENT,  LW_SPC, NUM_ESC

#define LAYOUT_LAYER_POINTER                                                                                       \
        _______, _______, _______, _______, _______,               KC_BTN1, _______, _______, _______, _______,    \
        _______, _______, _______, _______, _______,               KC_BTN2, _______, _______, _______, _______,    \
        _______, _______, _______, _______, _______,               _______, _______, _______, _______, _______,    \
                          DRGSCRL, KC_BTN1, KC_BTN2,               _______, _______, _______

// Lower
#define LAYOUT_LAYER_LOWER                                                                                         \
        G(KC_1), G(KC_2), G(KC_3),  G(KC_4),G(KC_5),               G(KC_6),  G(KC_7),G(KC_8),  G(KC_9),G(KC_0),    \
        KC_WBAK, KC_WFWD, KC_HOME,   KC_END, KC_APP,               KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT,  KC_F6,     \
 CTL_F1,ALT_F2,C(G(KC_LEFT)),C(G(KC_RIGHT)),  KC_F5,               KC_F5,   KC_F7,    KC_F8,  ALT_F9, CTL_F10,     \
                          _______, _______, _______,               _______, _______, _______

// Raise
#define LAYOUT_LAYER_RAISE                                                                                         \
        KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                KC_CIRC, KC_AMPR, KC_ASTR, KC_QUOT, KC_GRV,    \
        KC_QUOT,KC_DQT,   KC_LPRN, KC_RPRN, KC_PGUP,                KC_MINS, CTL_EQL, KC_LCBR, KC_RCBR,KC_BSLS,    \
              KC_ESC,_______,KC_ESC,KC_ENT, KC_PGDN,                KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_PIPE,   \
                          _______, _______, _______,                _______, _______, _______

// Adjust
#define LAYOUT_LAYER_ADJUST                                                                                        \
XXXXXXX,TG(LAYER_NUMPAD), KC_CAPS, XXXXXXX, XXXXXXX,                QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG,   \
        RGB_TOG, RGB_M_R, RGB_VAI, RGB_VAD, XXXXXXX,                XXXXXXX, KC_WBAK, KC_WFWD,  KC_APP, XXXXXXX,   \
        RGB_MOD,RGB_RMOD, RGB_HUI, RGB_HUD, QK_BOOT,                XXXXXXX, XXXXXXX,DPI_RMOD, DPI_MOD, XXXXXXX,   \
                          _______, _______, _______,                KC_VOLD, KC_VOLU, KC_MPLY

// Numpad
#define LAYOUT_LAYER_NUMPAD                                                                                        \
  TG(LAYER_NUMPAD), KC_F9,   KC_F8,  KC_F7,  KC_F12,                 KC_CIRC,   KC_7,   KC_8,   KC_9, KC_ASTR,     \
            KC_NO,  KC_F6,   KC_F5,  KC_F4,  KC_F11,                 KC_MINS,   KC_4,   KC_5,   KC_6,  KC_EQL,     \
          KC_LSFT,  KC_F3,   KC_F2,  KC_F1,  KC_F10,                 KC_PLUS,   KC_1,   KC_2,   KC_3, KC_SLSH,     \
                          _______, _______, _______,                 KC_ENT,    KC_0, KC_DOT


  #define _HOME_ROW_MOD_GACS(                                          \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                  \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                  \
    L20, L21, L22, L23, L24, R25, R26, R27, R28, R29,                  \
    ...)                                                               \
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
      LGUI_T(L10), LALT_T(L11), LSFT_T(L12), LCTL_T(L13),        L14,  \
            R15,  RCTL_T(R16), RSFT_T(R17), LALT_T(R18), RGUI_T(R19),  \
     LCTL_T(L20),         L21,         L22,         L23,         L24,  \
             R25,         R26,         R27,         R28,         R29,  \
      __VA_ARGS__
#define HOME_ROW_MOD_GACS(...) _HOME_ROW_MOD_GACS(__VA_ARGS__)

#define _HOME_ROW_MOD_LEFT_GACS(                                       \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                  \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                  \
    L20, L21, L22, L23, L24, R25, R26, R27, R28, R29,                  \
    ...)                                                               \
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
     LGUI_T(L10), LALT_T(L11), LSFT_T(L12), LCTL_T(L13),         L14,  \
             R15,         R16,         R17,         R18,         R19,  \
     LCTL_T(L20),         L21,         L22,         L23,         L24,  \
             R25,         R26,         R27,         R28,         R29,  \
      __VA_ARGS__
#define HOME_ROW_MOD_LEFT_GACS(...) _HOME_ROW_MOD_LEFT_GACS(__VA_ARGS__)

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
              R25,         R26,         R27,        R28,         R29,  \
      __VA_ARGS__
#define POINTER_MOD(...) _POINTER_MOD(__VA_ARGS__)

#define LAYOUT_wrapper(...) LAYOUT_split_3x5_3(__VA_ARGS__)

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

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_user(void) {
    HSV hsv = {0, 0, 0};
    if (IS_LAYER_ON(LAYER_POINTER)) {
        hsv = (HSV){HSV_GREEN};
    } else if (IS_LAYER_ON(LAYER_NUMPAD)) {
        hsv = (HSV){HSV_BLUE};
    } else if (IS_LAYER_ON(LAYER_RAISE)) {
        hsv = (HSV){HSV_MAGENTA};
    } else if (IS_LAYER_ON(LAYER_LOWER)) {
        hsv = (HSV){HSV_TEAL};
    } else if (IS_LAYER_ON(LAYER_ADJUST)) {
        hsv = (HSV){HSV_PINK};
    }
    // If hsv is not the default (0,0,0), update the RGB matrix
    if (hsv.h != 0 || hsv.s != 0 || hsv.v != 0) {
        // Cap hsv.v to the maximum brightness level
        hsv.v = MIN(hsv.v, rgb_matrix_get_val());
        RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color_all(rgb.r, rgb.g, rgb.b);
    }
    return true;
}

#endif // RGB_MATRIX_ENABLE

// This does not work with vial
#ifdef TAPPING_TERM_PER_KEY
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
#endif //TAPPING_TERM_PER_KEY

#ifdef POINTING_DEVICE_ENABLE
void pointing_device_init_user(void) {
    set_auto_mouse_enable(true);         // always required before the auto mouse feature will work
}
#endif     // POINTING_DEVICE_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (IS_LAYER_ON(LAYER_ADJUST)) {
        tap_code_delay(clockwise ? KC_VOLU : KC_VOLD, 10);
    } else if (IS_LAYER_ON(LAYER_LOWER)) {
        tap_code16(clockwise ? C(KC_TAB) : C(S(KC_TAB)));
    } else if (IS_LAYER_ON(LAYER_RAISE)) {
        for (int i = 0; i < 5; i++) {
            tap_code16(clockwise ? KC_WH_U : KC_WH_D);
        }
    } else if (IS_LAYER_ON(LAYER_NUMPAD)) {
        tap_code16(clockwise ? KC_RIGHT : KC_LEFT);
    } else {
        tap_code16(clockwise ? KC_WH_U : KC_WH_D);
    }
    return false;
}

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in
// rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif
