/*
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#ifdef VIA_ENABLE
/* VIA configuration. */
#    define DYNAMIC_KEYMAP_LAYER_COUNT 16
#    ifdef VIAL_ENABLE
#        define VIAL_KEYBOARD_UID \
          { 0x44, 0x9f,  0x26, 0x53, 0xD9, 0x7B, 0x72,  0x4F }
#        define  VIAL_UNLOCK_COMBO_ROWS \
            { 0, 4 }
#        define VIAL_UNLOCK_COMBO_COLS \
            { 0, 0 }
#    endif // VIAL_ENABLE
#endif // VIA_ENABLE

#define CHARYBDIS_CONFIG_SYNC

/* Handedness. */
//#define MASTER_RIGHT

// To use the handedness pin, resistors need to be installed on the adapter PCB.
// If so, uncomment the following code, and undefine MASTER_RIGHT above.
#define SPLIT_HAND_PIN GP15
#define SPLIT_HAND_PIN_LOW_IS_LEFT  // High -> right, Low -> left.


/* SPI & PMW3360 settings. */
#define SPI_DRIVER SPID0
#define SPI_SCK_PIN GP22
#define SPI_MISO_PIN GP20
#define SPI_MOSI_PIN GP23
#define POINTING_DEVICE_CS_PIN GP16

/* Define encoder pads.
 * \brief Encoder pads wired to MISO and MOS*/
#define ENCODER_DEFAULT_POS 0x3
#define ENCODERS_PAD_A { GP22 }
#define ENCODERS_PAD_B { GP23 }
//Encoders right define is required to prevent the trackball SPI pins from being overridden
#define ENCODERS_PAD_A_RIGHT { GP15 } //completely unused pin
#define ENCODERS_PAD_B_RIGHT { GP16 } //completely unused pin

/* Reset. */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP17
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U

/* Pointing device configuration. */

// Enable use of pointing device on slave split.
#define SPLIT_POINTING_ENABLE

// Pointing device is on the right split.
#define POINTING_DEVICE_RIGHT

// Limits the frequency that the sensor is polled for motion.
#define POINTING_DEVICE_TASK_THROTTLE_MS 1

// Invert X axis on mouse reports.
#define POINTING_DEVICE_INVERT_X

/* RGB matrix support. */
#ifdef RGB_MATRIX_ENABLE
#    define SPLIT_TRANSPORT_MIRROR
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255
#    define RGB_DISABLE_WHEN_USB_SUSPENDED
//#    define RGB_MATRIX_KEYPRESSES deprecated?
/*#    define RGB_MATRIX_LED_COUNT 36
#    define RGB_MATRIX_SPLIT { 18, 18 } in info.json*/

// Startup values.
#    define RGB_MATRIX_DEFAULT_HUE 0
#    define RGB_MATRIX_DEFAULT_SAT 255
#    define RGB_MATRIX_DEFAULT_VAL 64

#    define SPLIT_LAYER_STATE_ENABLE // form layer change indicator

// Rainbow swirl as startup mode.
#    define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#    define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CYCLE_LEFT_RIGHT

// Slow swirl at startup.
#    define RGB_MATRIX_DEFAULT_SPD 32

#    ifndef __arm__
// Disable control of RGB matrix by keycodes (must use firmware implementation
// to control the feature).
#        define RGB_MATRIX_DISABLE_KEYCODES
#    else // __arm__
// Enable all animations on ARM boards since they have plenty of memory
// available for it.
#        define ENABLE_RGB_MATRIX_ALPHAS_MODS
#        define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#        define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#        define ENABLE_RGB_MATRIX_BREATHING
#        define ENABLE_RGB_MATRIX_BAND_SAT
#        define ENABLE_RGB_MATRIX_BAND_VAL
#        define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#        define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#        define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#        define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#        define ENABLE_RGB_MATRIX_CYCLE_ALL
#        define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#        define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#        define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#        define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#        define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#        define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#        define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#        define ENABLE_RGB_MATRIX_DUAL_BEACON
#        define ENABLE_RGB_MATRIX_RAINBOW_BEACON
#        define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#        define ENABLE_RGB_MATRIX_RAINDROPS
#        define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#        define ENABLE_RGB_MATRIX_HUE_BREATHING
#        define ENABLE_RGB_MATRIX_HUE_PENDULUM
#        define ENABLE_RGB_MATRIX_HUE_WAVE
#        define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#        define ENABLE_RGB_MATRIX_DIGITAL_RAIN
#        define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#        define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#        define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#        define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#        define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#        define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#        define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#        define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#        define ENABLE_RGB_MATRIX_SPLASH
#        define ENABLE_RGB_MATRIX_MULTISPLASH
#        define ENABLE_RGB_MATRIX_SOLID_SPLASH
#        define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#    endif // !__arm__
#endif
