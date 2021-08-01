#pragma once

enum layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
    _NUMPAD
};

enum custom_keycodes { QWERTY = SAFE_RANGE, LOWER, RAISE, ADJUST, NUMPAD };

// Left hand
// Base
// home row mods
#define GUI_A LGUI_T(KC_A)
#define ALT_S LALT_T(KC_S)
#define SFT_D LSFT_T(KC_D)
#define CTL_F LCTL_T(KC_F)

#define CTRL_TB MT(MOD_LCTL, KC_TAB)
#define ALT_X MT(MOD_LALT, KC_X)
#define CTL_V MT(MOD_LCTL, KC_V)
#define CTL_Z MT(MOD_LCTL, KC_Z)

// Thumb clusters
#define NUM_TAB LT(_NUMPAD, KC_TAB)
#define LW_BSPC LT(_LOWER, KC_BSPC)
#define RAI_DEL LT(_RAISE, KC_DEL)


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

#define ADJ_QT LT(_ADJUST, KC_QUOT)
#define ALT_DOT MT(MOD_LALT, KC_DOT)
#define CTL_SLSH MT(MOD_RCTL, KC_SLSH)

// Thumb Cluster
#define RAI_ENT LT(_RAISE, KC_ENT)
#define LW_SPC LT(_LOWER, KC_SPC)

// Lower
#define RSFT_F11 MT(MOD_RSFT, KC_F11)
#define CTL_F10 MT(MOD_LCTL, KC_F10)
#define ALT_F9 MT(MOD_LALT, KC_F9)

// Raise
// Home row mods
#define CTL_EQL RCTL_T(KC_EQL)
#define SFT_LBRC RSFT_T(KC_LBRC)
#define ALT_RBRC LALT_T(KC_RBRC)
#define GUI_BSLS RGUI_T(KC_BSLS)

#define RSFT_TIL MT(MOD_RSFT, KC_TILD)





