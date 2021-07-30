#pragma once

enum layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
    _NUMPAD
};

enum custom_keycodes { QWERTY = SAFE_RANGE, LOWER, RAISE, ADJUST, NUMPAD };

#define CTRL_TB MT(MOD_LCTL, KC_TAB)
#define ADJ_QT LT(_ADJUST, KC_QUOT)
#define ALT_X MT(MOD_LALT, KC_X)
#define ALT_DOT MT(MOD_LALT, KC_DOT)
#define ALT_F2 MT(MOD_LALT, KC_F2)
#define RSFT_F11 MT(MOD_RSFT, KC_F11)
#define CTL_F10 MT(MOD_LCTL, KC_F10)
#define ALT_F9 MT(MOD_LALT, KC_F9)
#define CTL_F1 MT(MOD_LCTL, KC_F1)
#define RSFT_TIL MT(MOD_RSFT, KC_TILD)

#define CTL_V MT(MOD_LCTL, KC_V)
#define SFT_EQ MT(MOD_LSFT, KC_EQL)
#define SFT_QT MT(MOD_RSFT, KC_QUOT)

#define SFT_A MT(MOD_LSFT, KC_A)
#define CTL_Z MT(MOD_LCTL, KC_Z)

#define SFT_SCLN MT(MOD_RSFT, KC_SCLN)
#define CTL_SLSH MT(MOD_RCTL, KC_SLSH)

#define LOW_SPC LT(_LOWER, KC_SPC)
#define RAI_EQ LT(_RAISE, KC_EQL)
#define LOW_BSP LT(_LOWER, KC_BSPC)
#define LOW_DEL LT(_LOWER, KC_DEL)
#define ADJ_GRV LT(_ADJUST, KC_GRV)

// Left-hand home row mods
#define GUI_A LGUI_T(KC_A)
#define ALT_S LALT_T(KC_S)
#define SFT_D LSFT_T(KC_D)
#define CTL_F LCTL_T(KC_F)

// Lower Home row mods
#define GUI_LB LGUI_T(KC_LABK)
#define ALT_RB LALT_T(KC_RABK)
#define SFT_LP LSFT_T(KC_LPRN)
#define CTL_RP LCTL_T(KC_RPRN)

// Right-hand home row mods
#define CTL_J RCTL_T(KC_J)
#define SFT_K RSFT_T(KC_K)
#define ALT_L LALT_T(KC_L)
#define GUI_SCLN RGUI_T(KC_SCLN)

// left-hand num layer home row mods
#define SFT_UP RSFT_T(KC_UP)

// Thumb clusters
// Left
#define NUM_TAB LT(_NUMPAD, KC_TAB)
#define LW_BSPC LT(_LOWER, KC_BSPC)
#define RAI_DEL LT(_RAISE, KC_DEL)

// Right
#define RAI_ENT LT(_RAISE, KC_ENT)
#define LW_SPC LT(_LOWER, KC_SPC)


