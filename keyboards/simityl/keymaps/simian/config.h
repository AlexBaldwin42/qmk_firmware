/* This program is distributed in the hope that it will be useful,
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
#        define VIAL_COMBO_COUNT 2
#    endif // VIAL_ENABLE
#endif // VIA_ENABLE

/* Disable unused features. */
#define NO_ACTION_ONESHOT

#undef MASTER_RIGHT

#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

#ifndef TAPPING_TERM

#    define TAPPING_TERM 140
#    ifndef VIA_ENABLE
#       ifndef TAPPING_TERM_PER_KEY
#    		define TAPPING_TERM_PER_KEY
#       endif
#    endif
#    define PERMISSIVE_HOLD
#endif // TAPPING_TERM

#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#define AUTO_MOUSE_DEFAULT_LAYER 5
#define AUTO_MOUSE_TIME 5500
/* Charybdis-specific features. */
#define CHARYBDIS_CONFIG_SYNC

#ifdef POINTING_DEVICE_ENABLE
#    define POINTING_DEVICE_RIGHT
// Automatically enable the pointer layer when moving the trackball.  See also:
// - `CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS`
// - `CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD`
// #define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
//#    define CHARYBDIS_POINTER_ACCELERATION_ENABLE
#    undef POINTING_DEVICE_INVERT_X
#    define POINTING_DEVICE_INVERT_Y
#    define CHARYBDIS_DRAGSCROLL_REVERSE_Y
//#    define CHARYBDIS_MINIMUM_DEFAULT_DPI 1000
//#    define CHARYBDIS_DEFAULT_DPI_CONFIG_STEP 200
//#    ifndef CHARYBDIS_MINIMUM_SNIPING_DPI
//#        define CHARYBDIS_MINIMUM_SNIPING_DPI 200
//#    endif  // CHARYBDIS_MINIMUM_SNIPER_MODE_DPI
//#    ifndef CHARYBDIS_DRAGSCROLL_DPI
//#        define CHARYBDIS_DRAGSCROLL_DPI 100
//#    endif  // CHARYBDIS_DRAGSCROLL_DPI
//#    ifndef CHARYBDIS_DRAGSCROLL_BUFFER_SIZE
//#        define CHARYBDIS_DRAGSCROLL_BUFFER_SIZE 6
//#    endif  // !CHARYBDIS_DRAGSCROLL_BUFFER_SIZE
//#    ifndef CHARYBDIS_POINTER_ACCELERATION_FACTOR
//#        define CHARYBDIS_POINTER_ACCELERATION_FACTOR 50
//#    endif  // !CHARYBDIS_POINTER_ACCELERATION_FACTOR
#    define SPLIT_LAYER_STATE_ENABLE
#endif // POINTING_DEVICE_ENABLE

// Industrial encoder
//#define ENCODER_RESOLUTION 2
#define ENCODER_RESOLUTION 4
//#define ENCODER_DIRECTION_FLIP

