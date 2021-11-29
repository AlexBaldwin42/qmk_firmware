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

#define ADJ_KCQ LT(_ADJUST, KC_Q)
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
// Don't work :(
#define SFT_LCBR RSFT_T(KC_LCBR)
#define ALT_RCBR LALT_T(KC_RCBR)
#define GUI_BSLS RGUI_T(KC_BSLS)

#define RSFT_TIL MT(MOD_RSFT, KC_TILD)


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_charybdis_3x5(
  //,--------------------------------------------.                    ,----------------------------------------------
        ADJ_KCQ,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+-
        GUI_A,   ALT_S,   SFT_D,   CTL_F,    KC_G,                         KC_H,   CTL_J,    SFT_K,  ALT_L,GUI_SCLN,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+-
        CTL_Z,   ALT_X,    KC_C,   CTL_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  ALT_DOT,CTL_SLSH,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+-
                                 LW_BSPC, RAI_DEL, NUM_TAB,   RAI_ENT,  LW_SPC
                             //`--------------------------'  `--------------------------'

  ),

  [_LOWER] = LAYOUT_charybdis_3x5(
  //,--------------------------------------------.                    ,-------------------------------------------
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+-------
     GUI_BAK,  ALT_FWD,SFT_HOME,CTL_END,  KC_APP,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT,   KC_F6,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+-------
      CTL_F1,   ALT_F2,   KC_F3,   KC_F4,  KC_F5,                        KC_F5,   KC_F7,    KC_8,  ALT_F9, CTL_F10,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+-------
                            _______, _______, _______,     _______,_______
                        //`--------------------------'  `----------------'----------'
  ),

  [_RAISE] = LAYOUT_charybdis_3x5(
  //,--------------------------------------------.                    ,---------------------------------------------
      KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_GRV, KC_QUOT,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+
      KC_LABK, KC_RABK, KC_LPRN, KC_RPRN, KC_PGUP,                      KC_MINS, CTL_EQL, KC_LCBR, KC_RCBR,GUI_BSLS,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+
      KC_ESC,TO(_NUMPAD),_______,KC_ENT,KC_PGDOWN,                     KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_PIPE,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+
                                          _______, _______,_______,     _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_ADJUST] = LAYOUT_charybdis_3x5(
  //,-------------------------------------------.                    ,-----------------------------------------------
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      RESET, XXXXXXX, XXXXXXX, TO(_NUMPAD), RGB_TOG,
  //|-------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--
     RGB_TOG, RGB_M_R, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_WBAK, KC_WFWD, KC_APP, XXXXXXX,
  //|-------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--
     RGB_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|-------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--
                                _______, _______, _______,    KC_MPLY, KC_VOLD
                                      //|--------------------------'  `--------------------------'
  ),

  	[_NUMPAD] = LAYOUT_charybdis_3x5(
	//,-----------------------------------------------------.                    ,-----------------------------------------------------.
     KC_NO,     KC_NO,   KC_NO,   KC_NO, TG(_NUMPAD), 				   KC_CIRC,   KC_P7,   KC_P8,   KC_P9, KC_ASTR,
	//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_NO,   KC_LEFT,  SFT_UP, KC_DOWN, KC_RIGHT, 					KC_MINS,   KC_P4,   KC_P5,   KC_P6,  KC_EQL,
	//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
	   KC_LSFT,  KC_F10,   KC_F11,  KC_F12, KC_F5, 					   KC_PLUS,   KC_P1,   KC_P2,   KC_P3, KC_SLSH,
	//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
									       _______, _______, _______,     KC_ENT,   KC_P0
										//`--------------------------'  `--------------------------'
	)
};

// clang-format on
