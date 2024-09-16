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
#pragma once
#define MASTER_RIGHT

//Size reduction
#ifndef NO_DEBUG
#define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif // !NO_PRINT
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
#ifndef TAPPING_TERM
/**
 * \brief Configure the global tapping term (default: 200ms).
 *
 * If you have a lot of accidental mod activations, crank up the tapping term.
 *
 * See docs.qmk.fm/using-qmk/software-features/tap_hold#tapping-term
 */
#    define TAPPING_FORCE_HOLD
#    define TAPPING_TERM 140
#    define IGNORE_MOD_TAP_INTERRUPT
#endif  // TAPPING_TERM
/* RGB Matrix. */

// #undef RGB_MATRIX_ENABLE
#ifdef RGB_MATRIX_ENABLE
// Disable control of RGB matrix by keycodes (must use firmware implementation
// to control the feature).
#    define RGB_MATRIX_DISABLE_KEYCODES

// Limit maximum brightness to keep power consumption reasonable, and avoid
// disconnects.
#    undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 90

// Rainbow swirl as startup mode.
#    define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
// #    define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
// #    define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
// #    define ENABLE_RGB_MATRIX_RAINDROPS
// #    define ENABLE_RGB_MATRIX_HUE_PENDULUM
// #    define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
// #    define SPLIT_LAYER_STATE_ENABLE
#    define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_LEFT_RIGHT


// Slow swirl at startup.
#    define RGB_MATRIX_STARTUP_SPD 32

// Startup values.
#    define RGB_MATRIX_STARTUP_HUE 0
#    define RGB_MATRIX_STARTUP_SAT 255
#    define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
#    define RGB_MATRIX_STARTUP_HSV RGB_MATRIX_STARTUP_HUE, RGB_MATRIX_STARTUP_SAT, RGB_MATRIX_STARTUP_VAL
#endif  // RGB_MATRIX_ENABLE

//#define PMW3360_FIRMWARE_H "pmw3389_firmware.h"
//#define PMW3360_CPI 200
//#define PMW3360_CPI 3400
//#    define MAX_CPI 0x9F
#undef DIODE_DIRECTION
#define DIODE_DIRECTION COL2ROW



//#define CHARYBDIS_MINIMUM_DEFAULT_DPI 10 //  400 3200 10
//#define CHARYBDIS_DEFAULT_DPI_CONFIG_STEP 64000 // 200 400

#ifdef POINTING_DEVICE_ENABLE
#define PMW3360_CS_PIN B0
#undef POINTING_DEVICE_INVERT_X
#define POINTING_DEVICE_INVERT_Y
#define CHARYBDIS_DRAGSCROLL_REVERSE_Y

#    define CHARYBDIS_POINTER_ACCELERATION_ENABLE

#    define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

//#    ifndef CHARYBDIS_MINIMUM_DEFAULT_DPI
#        define CHARYBDIS_MINIMUM_DEFAULT_DPI 400
//#    endif  // CHARYBDIS_MINIMUM_DEFAULT_DPI

//#    ifndef CHARYBDIS_DEFAULT_DPI_CONFIG_STEP
#        define CHARYBDIS_DEFAULT_DPI_CONFIG_STEP 50
//#    endif  // CHARYBDIS_DEFAULT_DPI_CONFIG_STEP

#    ifndef CHARYBDIS_MINIMUM_SNIPING_DPI
#        define CHARYBDIS_MINIMUM_SNIPING_DPI 100
#    endif  // CHARYBDIS_MINIMUM_SNIPER_MODE_DPI
#    ifndef CHARYBDIS_SNIPING_DPI_CONFIG_STEP
#        define CHARYBDIS_SNIPING_DPI_CONFIG_STEP 50
#    endif  // CHARYBDIS_SNIPING_DPI_CONFIG_STEP

// Fixed DPI for drag-scroll.
#    ifndef CHARYBDIS_DRAGSCROLL_DPI
#        define CHARYBDIS_DRAGSCROLL_DPI 100
#    endif  // CHARYBDIS_DRAGSCROLL_DPI

#    ifndef CHARYBDIS_DRAGSCROLL_BUFFER_SIZE
#        define CHARYBDIS_DRAGSCROLL_BUFFER_SIZE 6
#    endif  // !CHARYBDIS_DRAGSCROLL_BUFFER_SIZE


#    ifndef CHARYBDIS_POINTER_ACCELERATION_FACTOR
#        define CHARYBDIS_POINTER_ACCELERATION_FACTOR 50
#    endif  // !CHARYBDIS_POINTER_ACCELERATION_FACTOR
#endif
