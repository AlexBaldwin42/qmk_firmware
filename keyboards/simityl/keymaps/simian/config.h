/* This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

/* Disable unused features. */

#undef MASTER_RIGHT

#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

#ifndef TAPPING_TERM
#    define TAPPING_TERM 140
#    ifndef TAPPING_TERM_PER_KEY
#        define TAPPING_TERM_PER_KEY
#    endif
#    define PERMISSIVE_HOLD
#endif // TAPPING_TERM

#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#define AUTO_MOUSE_DEFAULT_LAYER 5
#define AUTO_MOUSE_TIME 3500

#ifdef POINTING_DEVICE_ENABLE
#    define POINTING_DEVICE_RIGHT
#    undef POINTING_DEVICE_INVERT_X
#    define POINTING_DEVICE_INVERT_Y
#    define CHARYBDIS_DRAGSCROLL_REVERSE_Y
#    define SPLIT_LAYER_STATE_ENABLE
#endif // POINTING_DEVICE_ENABLE

// Industrial encoder
//#define ENCODER_RESOLUTION 2
#define ENCODER_RESOLUTION 4
//#define ENCODER_DIRECTION_FLIP

