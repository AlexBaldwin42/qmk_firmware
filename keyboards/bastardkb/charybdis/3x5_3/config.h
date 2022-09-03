/*
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
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

/* Key matrix configuration. */
#define MATRIX_ROWS 8 // Rows are doubled-up.
#define MATRIX_COLS 5

#define DIODE_DIRECTION ROW2COL

/* Set 0 if debouncing isn't needed. */
#define DEBOUNCE 5

/* Trackball angle adjustment. */
#define ROTATIONAL_TRANSFORM_ANGLE -25

/* Define encoder pads.
 * \brief Encoder pads wired to MISO and MOSI
*/
#define ENCODER_DEFAULT_POS 0x3
#define ENCODERS_PAD_A { GP22 }
#define ENCODERS_PAD_B { GP23 }
//Encoders right define is required to prevent the trackball SPI pins from being overridden
#define ENCODERS_PAD_A_RIGHT { GP15 } //completely unused pin
#define ENCODERS_PAD_B_RIGHT { GP16 } //completely unused pin

/* RGB settings. */
#define RGBLED_NUM 48
#define RGBLED_SPLIT \
    { 30, 18 }

/* RGB matrix support. */
#ifdef RGB_MATRIX_ENABLE
#    define SPLIT_TRANSPORT_MIRROR
#    define DRIVER_LED_TOTAL RGBLED_NUM
#    define RGB_MATRIX_SPLIT RGBLED_SPLIT
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 50
#    define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
#    define RGB_DISABLE_WHEN_USB_SUSPENDED
#    define RGB_MATRIX_KEYPRESSES
#endif
