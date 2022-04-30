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

#define THREE_THUMB_RIGHT


#ifdef THREE_THUMB_RIGHT
    #undef RGBLED_NUM
    #define RGBLED_NUM 36
    #undef RGBLED_SPLIT
    #define RGBLED_SPLIT \
    { 18, 17 }

    // clang-format on

#endif //End    THREE_THUMB_RIGHT
// // Pin switchin to B6
 //#undef SERIAL_USART_TX_PIN
//#define SERIAL_USART_TX_PIN B6


// // #define SERIAL_USART_DRIVER      SD1
//#define handwiredFlex
//#define bastardPCB_A2_Pin

//#define bastardPCB just leave standard

// Wiring configuration for each half.
// Switch A2 Row1
#undef MATRIX_ROW_PINS
#define MATRIX_ROW_PINS \
{ B0, B8, A8, B9 }
#undef MATRIX_COL_PINS
#define MATRIX_COL_PINS \
{ B1, B10, B3, B4, B5 }

#ifdef bastardPCB_A2_Pin
    #undef SERIAL_USART_TX_PIN
    #define SERIAL_USART_TX_PIN A2
//#undef STM32_SERIAL_USE_USART1
  //  #undef SERIAL_USART_DRIVER
    #define SERIAL_USART_DRIVER SD2
    //#undef STM32_SERIAL_USE_USART2
    // #define STM32_SERIAL_USE_USART2 TRUE
    // #define STM32_SERIAL_USE_USART1 FALSE
#endif
#ifndef bastardPCB_A2_Pin
    #define SERIAL_USART_DRIVER SD1
#endif

#ifdef bastardPCB
    // Wiring configuration for each half.
    // Switch A2 Row1
    #undef MATRIX_ROW_PINS
    #define MATRIX_ROW_PINS \
    { B9, B8, A8, B9 }
    #undef MATRIX_COL_PINS
    #define MATRIX_COL_PINS \
    { B1, B10, B3, B4, B5 }
#endif

#ifdef handwiredFlex
    #undef DIODE_DIRECTION
    #define DIODE_DIRECTION COL2ROW
    #undef MATRIX_ROW_PINS
    #define MATRIX_ROW_PINS \
    { B15, B9, B8, A8}

    //{ B15, A2, B8, A8} hand wired
    #undef MATRIX_COL_PINS
    #define MATRIX_COL_PINS \
    { B0, B5, B10, B3, B4}
    //  { B0, B1, B10, B3, B4}
    //   { B0, B1, B1
    //   { B0, B1, B10, B3, B4, B5 }
    //   //{ B0, B1, B10, B3, B4, B5 } Original switch for broken header
#endif


#define POINTER_LAYER_TIMEOUT_MS 1000
#ifndef TAPPING_TERM
/**
 * brief Configure the global tapping term (default: 200ms).
 *
 * If you have a lot of accidental mod activations, crank up the tapping term.
 *
 * See docs.qmk.fm/using-qmk/software-features/tap_hold#tapping-term
 */
#    define TAPPING_FORCE_HOLD
#    define TAPPING_TERM 140
#    define IGNORE_MOD_TAP_INTERRUPT
#endif  // TAPPING_TERM




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
// #define ENABLE_RGB_MATRIX_RAINDROPS
 #define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
// #define ENABLE_RGB_MATRIX_HUE_BREATHING
 #define ENABLE_RGB_MATRIX_HUE_PENDULUM
// #define ENABLE_RGB_MATRIX_HUE_WAVE
 #define ENABLE_RGB_MATRIX_PIXEL_FRACTAL
 #define ENABLE_RGB_MATRIX_PIXEL_RAIN
 #define SPLIT_LAYER_STATE_ENABLE
// Slow swirl at startup.
#    define RGB_MATRIX_STARTUP_SPD 32

// Startup values.ith this program.  If not, see <http://www.gnu.org/licenses/>.


#    define RGB_MATRIX_STARTUP_HUE 0
#    define RGB_MATRIX_STARTUP_SAT 255
#    define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
#    define RGB_MATRIX_STARTUP_HSV RGB_MATRIX_STARTUP_HUE, RGB_MATRIX_STARTUP_SAT, RGB_MATRIX_STARTUP_VAL
#endif  // RGB_MATRIX_ENABLE

//#define PMW3360_FIRMWARE_H "pmw3389_firmware.h"
//#define PMW3360_CPI 200
//#define PMW3360_CPI 3400
//#    define MAX_CPI 0x9F




//#define CHARYBDIS_MINIMUM_DEFAULT_DPI 1  //  400 3200 10
//#define CHARYBDIS_DEFAULT_DPI_CONFIG_STEP 1// 200 400

#ifdef POINTING_DEVICE_ENABLE
#define PMW3389_CS_PIN B14

#define PMW3389_CS_MODE 3
#define PMW3389_CS_DIVISOR 64
//#define PMW3360_FIRMWARE_H "pmw3389_firmware.h"
//#  define PMW3360_CPI 64000
//   define MAX_CPI 0xFF  // limits to 0--119, should be max cpi/100

#undef ROTATIONAL_TRANSFORM_ANGLE
#define ROTATIONAL_TRANSFORM_ANGLE -25
#define POINTING_DEVICE_ROTATION_90

//#define PMW3360_CS_PIN B0
#undef POINTING_DEVICE_INVERT_X
#define POINTING_DEVICE_INVERT_Y
#define CHARYBDIS_DRAGSCROLL_REVERSE_Y

#    define CHARYBDIS_POINTER_ACCELERATION_ENABLE

//#define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

//#    ifndef CHARYBDIS_MINIMUM_DEFAULT_DPI
#        define CHARYBDIS_MINIMUM_DEFAULT_DPI 400
//#    endif  // CHARYBDIS_MINIMUM_DEFAULT_DPI

//#    ifndef CHARYBDIS_DEFAULT_DPI_CONFIG_STEP
#        define CHARYBDIS_DEFAULT_DPI_CONFIG_STEP 50

//#    endif  // CHARYBDIS_DEFAULT_DPI_CONFIG_STEP

#    ifndef CHARYBDIS_MINIMUM_SNIPING_DPI
#        define CHARYBDIS_MINIMUM_SNIPING_DPI 2
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
