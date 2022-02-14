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
#include "print.h"
#undef LAYOUT_charybdis_3x5
#define LAYOUT_charybdis_3x5(                           \
  k00, k01, k02, k03, k04,     k44, k43, k42, k41, k40, \
  k10, k11, k12, k13, k14,     k54, k53, k52, k51, k50, \
  k20, k21, k22, k23, k24,     k64, k63, k62, k61, k60, \
            k32, k33, k30,     k70, k72                 \
)                                                       \
{                                                       \
  {   k00,   k01,   k02,   k03,   k04 },                \
  {   k10,   k11,   k12,   k13,   k14 },                \
  {   k20,   k21,   k22,   k23,   k24 },                \
  {   KC_NO, KC_NO, k32,   k33,   k30 },                \
  {   k40,   k41,   k42,   k43,   k44 },                \
  {   k50,   k51,   k52,   k53,   k54 },                \
  {   k60,   k61,   k62,   k63,   k64 },                \
  {   KC_NO, KC_NO,   KC_NO, k72, k70 },                \
}

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif  // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_LOWER,
    LAYER_RAISE,
    LAYER_ADJUST,
    LAYER_NUMPAD,
    LAYER_POINTER,
};

// Automatically enable sniping-mode on the pointer layer.
//#define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 750
#    endif  // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 6
#    endif  // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif      // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

// #define ESC_MED LT(LAYER_MEDIA, KC_ESC)
// #define SPC_NAV LT(LAYER_NAVIGATION, KC_SPC)
// #define TAB_FUN LT(LAYER_FUNCTION, KC_TAB)
// #define ENT_SYM LT(LAYER_SYMBOLS, KC_ENT)
// #define BSP_NUM LT(LAYER_NUMERAL, KC_BSPC)
//#define _L_PTR(KC) LT(LAYER_POINTER, KC)
#define _L_PTR(KC) LT(LAYER_POINTER, KC)


// Left hand
// Base
// home row mods
// #define GUI_A LGUI_T(KC_A)
// #define ALT_S LALT_T(KC_S)
// #define SFT_D LSFT_T(KC_D)
// #define CTL_F LCTL_T(KC_F)

// #define CTRL_TB MT(MOD_LCTL, KC_TAB)
// #define ALT_X MT(MOD_LALT, KC_X)
#define CTL_V MT(MOD_LCTL, KC_V)
#define CTL_Z MT(MOD_LCTL, KC_Z)

// Thumb clusters
#define NUM_TAB LT(LAYER_NUMPAD, KC_TAB)
#define LW_BSPC LT(LAYER_LOWER, KC_BSPC)
#define RAI_DEL LT(LAYER_RAISE, KC_DEL)


// Lower
// Home row mods
#define GUI_BAK LGUI_T(KC_WBAK)
#define ALT_FWD LALT_T(KC_WFWD)
#define SFT_HOME LSFT_T(KC_HOME)
#define CTL_END LCTL_T(KC_END)

#define ALT_F2 MT(MOD_LALT, KC_F2)
#define CTL_F1 MT(MOD_LCTL, KC_F1)

// Numpad layer home row mods
#define SFT_UP RSFT_T(KC_UP)


// Right hand
// Home row mods
#define CTL_J RCTL_T(KC_J)
#define SFT_K RSFT_T(KC_K)
#define ALT_L LALT_T(KC_L)
#define GUI_SCLN RGUI_T(KC_SCLN)

#define ADJ_KCQ LT(LAYER_ADJUST, KC_Q)
#define ALT_DOT MT(MOD_LALT, KC_DOT)
#define CTL_SLSH MT(MOD_RCTL, KC_SLSH)
#define ADJ_KCSLASH LT(LAYER_ADJUST, KC_SLSH)


// Thumb Cluster
#define RAI_ENT LT(LAYER_RAISE, KC_ENT)
#define LW_SPC LT(LAYER_LOWER, KC_SPC)

// Lower
#define RSFT_F11 MT(MOD_RSFT, KC_F11)
#define CTL_F10 MT(MOD_LCTL, KC_F10)
#define ALT_F9 MT(MOD_LALT, KC_F9)

// Raise
// Home row mods
#define CTL_EQL RCTL_T(KC_EQL)
// Don't work :(
// #define SFT_LCBR RSFT_T(KC_LCBR)
// #define ALT_RCBR LALT_T(KC_RCBR)
/// #define GUI_BSLS RGUI_T(KC_BSLS)

#define RSFT_TIL MT(MOD_RSFT, KC_TILD)


#define LAYOUT_LAYER_BASE                                                                                             \
        ADJ_KCQ,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P, \
        KC_A,   KC_S,   KC_D,   KC_F,    KC_G,                         KC_H,   KC_J,    KC_K,  KC_L,   KC_SCLN,  \
        KC_Z,   KC_X,    KC_C,   CTL_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT,ADJ_KCSLASH, \
                                 NUM_TAB, LW_BSPC, RAI_DEL,   RAI_ENT,  LW_SPC
// // /** Convenience row shorthands. */
#define _______________DEAD_HALF_ROW_______________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define ______________HOME_ROW_GACS_L______________ KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, XXXXXXX
#define ______________HOME_ROW_GACS_R______________ XXXXXXX, KC_LCTL, KC_LSFT, KC_LALT, KC_LGUI

// Lower
#define LAYOUT_LAYER_LOWER                                                                                                  \
     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,     KC_8,    KC_9,    KC_0,            \
     GUI_BAK,  ALT_FWD,SFT_HOME,CTL_END,  KC_APP,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT,  KC_F6,         \
     CTL_F1,   ALT_F2,   KC_F3,   KC_F4,  KC_F5,                        KC_F5,   KC_F7,    KC_8,  ALT_F9, CTL_F10,         \
                            _______, _______, _______,     _______,_______

// Raise
#define LAYOUT_LAYER_RAISE                                                                                                  \
      KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_QUOT, KC_GRV,          \
      KC_QUOT,KC_DQT,   KC_LPRN, KC_RPRN, KC_PGUP,                      KC_MINS, CTL_EQL, KC_LCBR, KC_RCBR,KC_BSLS,        \
      KC_ESC,TO(LAYER_NUMPAD),KC_QUOT,KC_ENT,KC_PGDOWN,                     KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_PIPE,         \
                                          _______, _______,_______,     _______, _______

// Adjust
#define LAYOUT_LAYER_ADJUST                                                                                                                 \
     XXXXXXX, TO(LAYER_POINTER), KC_CAPS, XXXXXXX, XXXXXXX,                      RESET, XXXXXXX, XXXXXXX, TO(LAYER_NUMPAD), RGB_TOG,       \
     RGB_TOG, RGB_M_R, RGB_VAI, RGB_VAD, XXXXXXX,                      XXXXXXX, KC_WBAK, KC_WFWD, KC_APP, XXXXXXX,                        \
     RGB_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     KC_MPLY , XXXXXXX, XXXXXXX, TO(LAYER_POINTER), XXXXXXX,                       \
                                _______, _______, _______,            KC_VOLD, KC_VOLU

// Numpad
#define LAYOUT_LAYER_NUMPAD                                                                                                 \
      TG(LAYER_NUMPAD),     KC_NO,   KC_NO,   KC_NO, TG(LAYER_NUMPAD),   KC_CIRC,   KC_P7,   KC_P8,   KC_P9, KC_ASTR,\
      KC_NO,   KC_LEFT,  SFT_UP, KC_DOWN, KC_RIGHT, 					KC_MINS,   KC_P4,   KC_P5,   KC_P6,  KC_EQL,\
	  KC_LSFT,  KC_F10,   KC_F11,  KC_F12, KC_F5, 					   KC_PLUS,   KC_P1,   KC_P2,   KC_P3, KC_SLSH,\
									       _______, _______, _______,     KC_ENT,   KC_P0

#define LAYOUT_LAYER_POINTER                                                                                                                                        \
   TG(LAYER_POINTER) ,XXXXXXX , DPI_MOD, TO(LAYER_POINTER), S_D_MOD, S_D_MOD, DPI_MOD, POINTER_DEFAULT_DPI_REVERSE, POINTER_DEFAULT_DPI_FORWARD, TG(LAYER_POINTER), \
    ______________HOME_ROW_GACS_L______________, ______________HOME_ROW_GACS_R______________,                                                                       \
    _______, DRG_TOG, _______, DRGSCRL,   EEP_RST,   SNIPING, _______, DRGSCRL,KC_BTN1 ,KC_BTN2 ,                                                                     \
                      KC_BTN2, KC_BTN1, KC_BTN3, RAI_ENT, LW_SPC
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
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
             L10,         L11,         L12,         L13,         L14,  \
             R15,         R16,         R17,         R18,         R19,  \
             L20,  _L_PTR(L21),        L22,         L23,         L24,  \
             R25,         R26,  _L_PTR(R27),        R28,         R29, \
      __VA_ARGS__
#define POINTER_MOD(...) _POINTER_MOD(__VA_ARGS__)

#define LAYOUT_wrapper(...) LAYOUT_charybdis_3x5(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT_wrapper(
    POINTER_MOD(HOME_ROW_MOD_GACS(LAYOUT_LAYER_BASE))
  ),
   [LAYER_LOWER] = LAYOUT_wrapper(LAYOUT_LAYER_LOWER),
   [LAYER_RAISE] = LAYOUT_wrapper(LAYOUT_LAYER_RAISE),
   [LAYER_ADJUST] = LAYOUT_wrapper(LAYOUT_LAYER_ADJUST),
   [LAYER_NUMPAD] = LAYOUT_wrapper(LAYOUT_LAYER_NUMPAD),
   [LAYER_POINTER] = LAYOUT_wrapper(LAYOUT_LAYER_POINTER),
};
// clang-format on




#ifdef POINTING_DEVICE_ENABLE


//#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
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
    }
    if(!(hsv.v == 0 && hsv.s == 0 && hsv.v == 0)){
        if (hsv.v > rgb_matrix_get_val()) {
            hsv.v = rgb_matrix_get_val();
        }
        RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color_all(rgb.r, rgb.g,rgb.b);
    }

}
#    endif // RGB_MATRIX_ENABLE
//#    endif //CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
// #    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
// // report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
// //     if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
// //         if (auto_pointer_layer_timer == 0) {
// //             layer_on(LAYER_POINTER);
// // #        ifdef RGB_MATRIX_ENABLE
// //             rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
// //             rgb_matrix_sethsv_noeeprom(HSV_GREEN);
// // #        endif  // RGB_MATRIX_ENABLE
// //         }
// //         auto_pointer_layer_timer = timer_read();
// //     }

// //     return mouse_report;
// // }

// void matrix_scan_kb(void) {
//     if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
//         auto_pointer_layer_timer = 0;
//         layer_off(LAYER_POINTER);
// #        ifdef RGB_MATRIX_ENABLE
//         rgb_matrix_mode_noeeprom(RGB_ATRIX_STARTUP_MODE);
// #        endif  // RGB_MATRIX_ENABLE
//     }

//     matrix_scan_user();
// }
// #    endif  // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

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

// void shutdown_user(void) {
// #ifdef RGBLIGHT_ENABLE
//     rgblight_enable_noeeprom();
//     rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
//     rgblight_setrgb_red();
// #endif  // RGBLIGHT_ENABLE
// #ifdef RGB_MATRIX_ENABLE
//     rgb_matrix_set_color_all(RGB_RED);
//     rgb_matrix_update_pwm_buffers();
// #endif  // RGB_MATRIX_ENABLE
// }

#ifdef POINTING_DEVICE_ENABLE
static uint16_t mouse_timer           = 0;
static uint16_t mouse_debounce_timer  = 0;
static uint8_t  mouse_keycode_tracker = 0;
bool            tap_toggling = false, enable_acceleration = false;


report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    #ifdef CONSOLE_ENABLE

#endif
     int8_t x = mouse_report.x, y = mouse_report.y;
    // mouse_report.x = 0;
    // mouse_report.y = 0;

    if (x != 0 && y != 0) {
        mouse_timer = timer_read();
        // if (timer_elapsed(mouse_debounce_timer) > TAPPING_TERM) {
        //     if (enable_acceleration) {
        //         x = (x > 0 ? x * x / 16 + x : -x * x / 16 + x);
        //         y = (y > 0 ? y * y / 16 + y : -y * y / 16 + y);
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
    # ifdef RGB_MATRIX_ENABLE
    // if(layer_state_is(LAYER_POINTER)){
    //     dprint("green2 \n" );
    //         rgb_matrix_sethsv_noeeprom(HSV_GREEN);
    //         rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);

    // }
#        endif  // RGB_MATRIX_ENABLE
    return mouse_report;
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
dprint("procesrcordpoints" );
    switch (keycode) {
        case  LT(LAYER_RAISE, KC_ENT):
        case  LT(LAYER_LOWER, KC_SPC):
        dprint("ltlowe" );
             layer_off(LAYER_POINTER);
             break;
        case TT(LAYER_POINTER):
            if (record->event.pressed) {
                mouse_keycode_tracker++;
            } else {
#if TAPPING_TOGGLE != 0
                if (record->tap.count == TAPPING_TOGGLE) {
                    tap_toggling ^= 1;
#    if TAPPING_TOGGLE == 1
                    if (!tap_toggling) mouse_keycode_tracker -= record->tap.count + 1;
#    else
                    if (!tap_toggling) mouse_keycode_tracker -= record->tap.count;
#    endif
                } else {
                    mouse_keycode_tracker--;
                }
#endif
            }
            mouse_timer = timer_read();
            break;
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
        case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX:
            break;
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            if (record->event.pressed || !record->tap.count) {
                break;
            }
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
