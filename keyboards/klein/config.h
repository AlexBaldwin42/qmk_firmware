/*
Copyright 2022 simian <@simian>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x3A3C
#define PRODUCT_ID      0x0001
#define DEVICE_VER      0x0001
#define MANUFACTURER   	Simian
#define PRODUCT         Klein


/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 8
#define MATRIX_COLS 5

#define DEBOUNCE 5

#define DIODE_DIRECTION ROW2COL
/*
// wiring of each half
#define MATRIX_ROW_PINS { C6, D7, E6, B4 }
#define MATRIX_COL_PINS { F6, F7, B1, B3, B2 }
*/
/* Serial settings */
#define USE_SERIAL
/* serial.c configuration for split keyboard */
//#define SOFT_SERIAL_PIN D2
//#define SPLIT_LAYER_STATE_ENABLE
//#define SPLIT_USB_DETECT
