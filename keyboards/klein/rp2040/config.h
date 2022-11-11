// Copyright 2022 @geigeigeist
// SPDX-License-Identifier: GPL-2.0+

#pragma once

#include "config_common.h"

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

/* audio support */
#undef AUDIO_PIN
//#define AUDIO_PIN GP9

/* i2c */
#define I2C_DRIVER I2CD2

/* communication between sides */
#define SERIAL_PIO_USE_PIO1
#define SOFT_SERIAL_PIN GP1

// wiring of each half
#define MATRIX_ROW_PINS { GP5, GP6, GP7, GP8 }
#define MATRIX_COL_PINS { GP23, GP20, GP22, GP26, GP27  }
