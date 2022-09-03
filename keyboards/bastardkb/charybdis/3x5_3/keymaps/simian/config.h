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
#undef MATRIX_ROW_PINS
#define MATRIX_ROW_PINS \
    { GP26, GP5, GP4, GP9 }
  //{ GP27, GP5, GP4, GP9 } // switched

#undef MATRIX_COL_PINS
#define MATRIX_COL_PINS \
  { GP28, GP21, GP6, GP7, GP8 }

  //{ GP28, GP15, GP6, GP7, GP8 }

#define POINTER_LAYER_TIMEOUT_MS 1500
#ifndef TAPPING_TERM
/**
 * brief Configure the global tapping term (default: 200ms).
 * If you have a lot of accidental mod activations, crank up the tapping term.
 * See docs.qmk.fm/using-qmk/software-features/tap_hold#tapping-term
 */
#    define TAPPING_FORCE_HOLD
#    define TAPPING_TERM 140
#    define TAPPING_TERM_PER_KEY
#    define IGNORE_MOD_TAP_INTERRUPT
#endif  // TAPPING_TERM

/* Define encoder pads.
 * \brief Encoder pads wired to MISO and MOSI
*/
#define ENCODER_DEFAULT_POS 0x3
#define ENCODERS_PAD_A { GP22 }
#define ENCODERS_PAD_B { GP23 }
//Encoders right define is required to prevent the trackball SPI pins from being overridden
#define ENCODERS_PAD_A_RIGHT { GP15 } //completely unused pin
#define ENCODERS_PAD_B_RIGHT { GP16 } //completely unused pin

#ifdef RGB_MATRIX_ENABLE
// Disable control of RGB matrix by keycodes (must use firmware implementation
// to control the feature).
//#    define RGB_MATRIX_DISABLE_KEYCODES

// Limit maximum brightness to keep power consumption reasonable, and avoid
// disconnects.
#    undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 100


// Rainbow swirl as startup mode.
#    define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#    define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_RAINBOW_MOVING_CHEVRON


// #define ENABLE_RGB_MATRIX_ALPHAS_MODS
#define RGB_MATRIX_KEYREACTIVE_ENABLED
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_BREATHING
#define ENABLE_RGB_MATRIX_BAND_SAT
#define ENABLE_RGB_MATRIX_BAND_VAL
#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#define ENABLE_RGB_MATRIX_CYCLE_ALL
#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
// #define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
// #define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
// #define ENABLE_RGB_MATRIX_DUAL_BEACON
// #define ENABLE_RGB_MATRIX_RAINBOW_BEACON
// #define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#define ENABLE_RGB_MATRIX_RAINDROPS
#define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
// #define ENABLE_RGB_MATRIX_HUE_BREATHING
#define ENABLE_RGB_MATRIX_HUE_PENDULUM
#define ENABLE_RGB_MATRIX_HUE_WAVE
#define ENABLE_RGB_MATRIX_PIXEL_FRACTAL
#define ENABLE_RGB_MATRIX_PIXEL_RAIN
#        define ENABLE_RGB_MATRIX_SPLASH
#        define ENABLE_RGB_MATRIX_MULTISPLASH
#        define ENABLE_RGB_MATRIX_SOLID_SPLASH
#        define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#define SPLIT_LAYER_STATE_ENABLE

#    define RGB_MATRIX_STARTUP_SPD 32

// Startup values.ith this program.  If not, see <http://www.gnu.org/licenses/>.


#    define RGB_MATRIX_STARTUP_HUE 0
#    define RGB_MATRIX_STARTUP_SAT 255
#undef    RGB_MATRIX_STARTUP_VAL
#    define RGB_MATRIX_STARTUP_VAL 70
#    define RGB_MATRIX_STARTUP_HSV RGB_MATRIX_STARTUP_HUE, RGB_MATRIX_STARTUP_SAT, RGB_MATRIX_STARTUP_VAL
#endif  // RGB_MATRIX_ENABLE

#ifdef POINTING_DEVICE_ENABLE
#define PMW3389_CS_PIN GP14
//#define PMW3360_CS_PIN GP14
//#undef PMW3360_CS_PIN
#undef SPI_SCK_PIN
#define SPI_SCK_PIN GP22
#undef SPI_MOSI_PIN
#define SPI_MOSI_PIN GP23
#undef SPI_MISO_PIN
#define SPI_MISO_PIN GP20
//#define PMW3389_CS_MODE 3
//#define PMW3389_CS_DIVISOR 64

// Near Thumbcluster Trackball
// #define POINTING_DEVICE_ROTATION_180

// Top Keyboard
// Blank

//#undef ROTATIONAL_TRANSFORM_ANGLE
//#define ROTATIONAL_TRANSFORM_ANGLE -25
//#define POINTING_DEVICE_ROTATION_90
//#undef ROTATIONAL_TRANSFORM_ANGLE
//#define ROTATIONAL_TRANSFORM_ANGLE 45

//#define PMW3360_CS_PIN B0
#undef POINTING_DEVICE_INVERT_X
#define POINTING_DEVICE_INVERT_Y
#define CHARYBDIS_DRAGSCROLL_REVERSE_Y

#    define CHARYBDIS_POINTER_ACCELERATION_ENABLE

//#define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

//#    ifndef CHARYBDIS_MINIMUM_DEFAULT_DPI
#        define CHARYBDIS_MINIMUM_DEFAULT_DPI 650
//#    endif  // CHARYBDIS_MINIMUM_DEFAULT_DPI

//#    ifndef CHARYBDIS_DEFAULT_DPI_CONFIG_STEP
#        define CHARYBDIS_DEFAULT_DPI_CONFIG_STEP 50

//#    endif  // CHARYBDIS_DEFAULT_DPI_CONFIG_STEP

#    ifndef CHARYBDIS_MINIMUM_SNIPING_DPI
#        define CHARYBDIS_MINIMUM_SNIPING_DPI 200
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
