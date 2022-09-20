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

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif  // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

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



#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 750
#    endif  // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 20
#    endif  // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif      // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

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
                           NUM_TAB, LW_BSPC, RAI_DEL,  DRG_TOG,        RAI_ENT,  LW_SPC, NUM_ESC

#define LAYOUT_LAYER_POINTER                                                                                                                                        \
          _______ , _______, _______, _______,_______,               KC_BTN1,SNIPING_MODE, DRGSCRL,_______, _______, \
           _______, _______, _______,_______ ,_______,               KC_BTN2, _______, _______, _______, _______,                                                                       \
       _______,SNIPING_MODE, _______, DRGSCRL,_______,               _______, _______, _______, _______, _______,                                                                     \
                            KC_BTN2, KC_BTN1, KC_BTN3, _______,      _______, _______, _______

// Lower
#define LAYOUT_LAYER_LOWER                                                                                                  \
          G(KC_1), G(KC_2), G(KC_3),  G(KC_4),G(KC_5),                G(KC_6), G(KC_7), G(KC_8), G(KC_9),G(KC_0),            \
          KC_WBAK, KC_WFWD, KC_HOME,   KC_END, KC_APP,                KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT,  KC_F6,         \
     CTL_F1,   ALT_F2,C(G(KC_LEFT)),C(G(KC_RIGHT)), KC_F5,            KC_F5,   KC_F7,    KC_F8,  ALT_F9, CTL_F10,         \
                            _______, _______, _______,_______,        _______, _______, _______

// Raise
#define LAYOUT_LAYER_RAISE                                                                                                  \
      KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                     KC_CIRC, KC_AMPR, KC_ASTR, KC_QUOT, KC_GRV,          \
      KC_QUOT,KC_DQT,   KC_LPRN, KC_RPRN, KC_PGUP,                     KC_MINS, CTL_EQL, KC_LCBR, KC_RCBR,KC_BSLS,        \
      KC_ESC,_______,KC_ESC,KC_ENT,KC_PGDOWN,                          KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_PIPE,         \
                            _______, _______, _______, _______,        _______, _______, _______

// Adjust
#define LAYOUT_LAYER_ADJUST                                                                                                                 \
XXXXXXX, TG(LAYER_NUMPAD), KC_CAPS, XXXXXXX, XXXXXXX,                  QK_BOOT, XXXXXXX, XXXXXXX,XXXXXXX , RGB_TOG,       \
       RGB_TOG, RGB_M_R, RGB_VAI, RGB_VAD, XXXXXXX,                    XXXXXXX, KC_WBAK, KC_WFWD, KC_APP, XXXXXXX,                        \
       RGB_MOD, XXXXXXX, RGB_HUI, RGB_HUD, QK_BOOT,                    XXXXXXX , XXXXXXX, XXXXXXX, POINTER_DEFAULT_DPI_FORWARD, XXXXXXX,                       \
                            _______, _______, _______,_______,         KC_VOLD, KC_VOLU, KC_MPLY

// Numpad
#define LAYOUT_LAYER_NUMPAD                                                                                       \
   TG(LAYER_NUMPAD), KC_F7,   KC_F8,  KC_F9,  KC_F12,                   KC_CIRC,   KC_7,   KC_8,   KC_9, KC_ASTR,\
        KC_NO,       KC_F4,   KC_F5,  KC_F6,  KC_F11, 				    KC_MINS,   KC_4,   KC_5,   KC_6,  KC_EQL,\
	       KC_LSFT,  KC_F1,   KC_F2,  KC_F3,  KC_F10,				    KC_PLUS,   KC_1,   KC_2,   KC_3, KC_SLSH,\
                            _______, _______, _______,_______,          KC_ENT,    KC_0, KC_DOT


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

#define LAYOUT_wrapper(...) LAYOUT_charybdis_3x5_3(__VA_ARGS__)

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



#ifdef POINTING_DEVICE_ENABLE

#    ifdef RGB_MATRIX_ENABLE
void rgb_matrix_indicators_user(void) {
   HSV hsv = {0,0,0};

     if (IS_LAYER_ON(LAYER_POINTER)) {
        HSV hsv1 = {HSV_GREEN};
        hsv = hsv1;

    } else if (IS_LAYER_ON(LAYER_NUMPAD)) {
      HSV hsv1 = {HSV_BLUE};
        hsv = hsv1;
    } else if (IS_LAYER_ON(LAYER_RAISE)) {
        HSV hsv1 = {HSV_MAGENTA};
        hsv = hsv1;
    } else if (IS_LAYER_ON(LAYER_LOWER)) {
        HSV hsv1 = {HSV_TEAL};
        hsv = hsv1;
    }else if (IS_LAYER_ON(LAYER_ADJUST)) {
        HSV hsv1 = {HSV_PINK};
        hsv = hsv1;
    }
    if(!(hsv.v == 0 && hsv.s == 0 && hsv.v == 0)){
        if (hsv.v > rgb_matrix_get_val()) {
            hsv.v = rgb_matrix_get_val();
        }
        RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color_all(rgb.r, rgb.g,rgb.b);
    }

}
#    endif


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

#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_kb(layer_state_t state) {
    state = layer_state_set_user(state);
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif  // CHARYBDIS_AUTO_SNIPING_ON_LAYER
#endif      // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif

#ifdef POINTING_DEVICE_ENABLE
static uint16_t mouse_timer           = 0;
static uint16_t mouse_debounce_timer  = 0;
static uint8_t  mouse_keycode_tracker = 0;
bool            tap_toggling = false, enable_acceleration = false;


report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    #ifdef CONSOLE_ENABLE

#endif
#define THRESHOLD 3
     int8_t x = mouse_report.x, y = mouse_report.y;
    // mouse_report.x = 0;
    // mouse_report.y = 0;

    if (((x != 0 || y != 0) && (abs(x) >= THRESHOLD || abs(y) >= THRESHOLD || abs(x)+abs(y) >= THRESHOLD)) || (layer_state_is(LAYER_POINTER) && (abs(x)>0 || abs(y)>0))) {
        mouse_timer = timer_read();
        // if (timer_elapsed(mouse_debounce_timer) > TAPPING_TERM) {
        //     if (enable_acceleration) {
        //         x = (x > 0 ? x * x / 16 + x : -x * x / 16 + x);
        //         y = (y > 0 ? y * y / 16 + y : -y * y / 16 + y
        //     }
        //     mouse_report.x = x;
        //     mouse_report.y = y;
            if (!layer_state_is(LAYER_POINTER)) {
                layer_on(LAYER_POINTER);
                 dprint("LayerOn \n" );
            //}
        }
    } else if (timer_elapsed(mouse_timer) > POINTER_LAYER_TIMEOUT_MS && layer_state_is(LAYER_POINTER) && !mouse_keycode_tracker && !tap_toggling) {
                 dprint("Layeroff1 \n" );

        layer_off(LAYER_POINTER);
    } else if (tap_toggling) {
        if (!layer_state_is(LAYER_POINTER)) {
            layer_on(LAYER_POINTER);
                 dprint("Layeron2 \n" );

        }
    }
    return mouse_report;
}
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
        } else if(IS_LAYER_ON(LAYER_NUMPAD)) {
            if (clockwise) {
                tap_code(KC_RIGHT);
            } else {
                tap_code(KC_LEFT);
            }
        }else {
            if (clockwise) {
                tap_code(KC_WH_U);
            } else {
                tap_code(KC_WH_D);
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

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
dprint("procesrcordpoints" );
    switch (keycode) {
        case  LT(LAYER_RAISE, KC_ENT):
        case  LT(LAYER_LOWER, KC_SPC):
        case  KC_LCTL:
             layer_off(LAYER_POINTER);
             break;
//         case TT(LAYER_POINTER):
//             if (record->event.pressed) {
//                 mouse_keycode_tracker++;
//             } else {
// #if TAPPING_TOGGLE != 0
//                 if (record->tap.count == TAPPING_TOGGLE) {
//                     tap_toggling ^= 1;
// #    if TAPPING_TOGGLE == 1
//                     if (!tap_toggling) mouse_keycode_tracker -= record->tap.count + 1;
// #    else
//                     if (!tap_toggling) mouse_keycode_tracker -= record->tap.count;
// #    endif
//                 } else {
//                     mouse_keycode_tracker--;
//                 }
// #endif
//             }
//             mouse_timer = timer_read();
//             break;
        case TG(LAYER_POINTER):
            if (record->event.pressed) {
                tap_toggling ^= 1;
            }
            break;
        case MO(LAYER_POINTER):

#if (defined(KEYBOARD_bastardkb_charybdis) || defined(KEYBOARD_handwired_tractyl_manuform)) && !defined(NO_CHARYBDIS_KEYCODES)
        case SAFE_RANGE ... (CHARYBDIS_SAFE_RANGE-1):
#endif
        case KC_MS_UP ... KC_MS_WH_RIGHT:
            record->event.pressed ? mouse_keycode_tracker++ : mouse_keycode_tracker--;
            mouse_timer = timer_read();
            break;
        // case KC_ACCEL:
        //     enable_acceleration = record->event.pressed;
        //     record->event.pressed ? mouse_keycode_tracker++ : mouse_keycode_tracker--;
        //     mouse_timer = timer_read();
        //     break;
        // case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX:
        //     break;
        // case QK_MOD_TAP ... QK_MOD_TAP_MAX:
        //     if (record->event.pressed || !record->tap.count) {
        //         break;
        //     }
        case RGB_MOD:

            break;
        default:
            if (IS_NOEVENT(record->event)) break;
            if ((keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) && (((keycode >> 0x8) & 0xF) == LAYER_POINTER)) {
                record->event.pressed ? mouse_keycode_tracker++ : mouse_keycode_tracker--;
                mouse_timer = timer_read();
                break;
            }
            if (layer_state_is(LAYER_POINTER) && !mouse_keycode_tracker && !tap_toggling) {
                layer_off(LAYER_POINTER);
            }
            mouse_keycode_tracker = 0;
            mouse_debounce_timer  = timer_read();
            break;
    }
    return true;
}
#endif      // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif

void shutdown_user(void) {
#ifdef RGBLIGHT_ENABLE
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_setrgb_red();
#endif  // RGBLIGHT_ENABLE
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_color_all(RGB_RED);
    rgb_matrix_update_pwm_buffers();
#endif  // RGB_MATRIX_ENABLE
}
