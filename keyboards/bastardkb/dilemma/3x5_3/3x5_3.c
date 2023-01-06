/**
 * Copyright 2020 Christopher Courtney <drashna@live.com> (@drashna)
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Publicw License as published by
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

#include "3x5_3.h"

/**
 * LEDs index.
 *
 * ╭────────────────────╮                 ╭────────────────────╮
 *    2   3   8   9  12                     30  27  26  21  20
 * ├────────────────────┤                 ├────────────────────┤
 *    1   4   7  10  13                     31  28  25  22  19
 * ├────────────────────┤                 ├────────────────────┤
 *    0   5   6  11  14                     32  29  24  23  18
 * ╰────────────────────╯                 ╰────────────────────╯
 *                   15  16  17     35  34  33
 *                 ╰────────────╯ ╰────────────╯
 */
// clang-format off
#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    /* Key Matrix to LED index. */
    // Left split.
    {      2,      3,      8,      9,     12 }, // Top row
    {      1,      4,      7,     10,     13 }, // Middle row
    {      0,      5,      6,     11,     14 }, // Bottom row
    {     17, NO_LED,     15,     16, NO_LED }, // Thumb cluster
#if 0
    // Underglow.
    {     20,     21,     26,     27,     30 },
    {     19,     22,     25,     28,     31 },
    {     18,     23,     24,     29,     32 },
    {     35, NO_LED,     33,     34, NO_LED },
#endif
    // Right split.
    {     38,     39,     44,     45,     48 }, // Top row
    {     37,     40,     43,     46,     49 }, // Middle row
    {     36,     41,     42,     47,     50 }, // Bottom row
    {     53, NO_LED,     51,     52, NO_LED }, // Thumb cluster
#if 0
    // Underglow.
    {     56,     57,     62,     63,     66 },
    {     55,     58,     61,     64,     67 },
    {     54,     59,     60,     65,     68 },
    {     71, NO_LED,     69,     70, NO_LED },
#endif
}, {
    /* LED index to physical position. */
    // Left split.
    /* index=0  */ {   0,  42 }, {   0,  21 }, {   0,   0 }, // col 1 (left most)
    /* index=3  */ {  18,   0 }, {  18,  21 }, {  18,  42 }, // col 2
    /* index=6  */ {  36,  42 }, {  36,  21 }, {  36,   0 },
    /* index=9  */ {  54,   0 }, {  54,  21 }, {  54,  42 },
    /* index=12 */ {  72,   0 }, {  72,  21 }, {  72,  42 },
    /* index=15 */ {  72,  64 }, {  90,  64 }, { 108,  64 }, // Thumb cluster
    // Underglow.
    /* index=18 */ {   0,   0 }, {   0,   0 }, {   0,   0 },
    /* index=21 */ {   0,   0 }, {   0,   0 }, {   0,   0 },
    /* index=24 */ {   0,   0 }, {   0,   0 }, {   0,   0 },
    /* index=27 */ {   0,   0 }, {   0,   0 }, {   0,   0 },
    /* index=30 */ {   0,   0 }, {   0,   0 }, {   0,   0 },
    /* index=33 */ {   0,   0 }, {   0,   0 }, {   0,   0 },
    // Right split.
    /* index=36 */ { 224,  42 }, { 224,  21 }, { 224,   0 }, // col 10 (right most)
    /* index=39 */ { 206,   0 }, { 206,  21 }, { 206,  42 }, // col 9
    /* index=42 */ { 188,  42 }, { 188,  21 }, { 188,   0 },
    /* index=45 */ { 170,   0 }, { 170,  21 }, { 170,  42 },
    /* index=48 */ { 152,   0 }, { 152,  21 }, { 152,  42 },
    /* index=51 */ { 152,  64 }, { 134,  64 }, { 116,  64 }, // Thumb cluster
    // Underglow.
    /* index=54 */ {   0,   0 }, {   0,   0 }, {   0,   0 },
    /* index=57 */ {   0,   0 }, {   0,   0 }, {   0,   0 },
    /* index=60 */ {   0,   0 }, {   0,   0 }, {   0,   0 },
    /* index=63 */ {   0,   0 }, {   0,   0 }, {   0,   0 },
    /* index=66 */ {   0,   0 }, {   0,   0 }, {   0,   0 },
    /* index=69 */ {   0,   0 }, {   0,   0 }, {   0,   0 },
}, {
    /* LED index to flag. */
    // Left split.
    /* index=0  */  LED_FLAG_KEYLIGHT,  LED_FLAG_KEYLIGHT,  LED_FLAG_KEYLIGHT, // col 1
    /* index=3  */  LED_FLAG_KEYLIGHT,  LED_FLAG_KEYLIGHT,  LED_FLAG_KEYLIGHT, // col 2
    /* index=6  */  LED_FLAG_KEYLIGHT,  LED_FLAG_KEYLIGHT,  LED_FLAG_KEYLIGHT,
    /* index=9  */  LED_FLAG_KEYLIGHT,  LED_FLAG_KEYLIGHT,  LED_FLAG_KEYLIGHT,
    /* index=12 */  LED_FLAG_KEYLIGHT,  LED_FLAG_KEYLIGHT,  LED_FLAG_KEYLIGHT,
    /* index=15 */  LED_FLAG_KEYLIGHT,  LED_FLAG_KEYLIGHT,  LED_FLAG_KEYLIGHT, // Thumb cluster
    // Underglow.
    /* index=18 */ LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
    /* index=21 */ LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
    /* index=24 */ LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
    /* index=27 */ LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
    /* index=30 */ LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
    /* index=33 */ LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
    // Right split.
    /* index=36 */  LED_FLAG_KEYLIGHT,  LED_FLAG_KEYLIGHT,  LED_FLAG_KEYLIGHT, // col 10
    /* index=39 */  LED_FLAG_KEYLIGHT,  LED_FLAG_KEYLIGHT,  LED_FLAG_KEYLIGHT, // col 9
    /* index=42 */  LED_FLAG_KEYLIGHT,  LED_FLAG_KEYLIGHT,  LED_FLAG_KEYLIGHT,
    /* index=45 */  LED_FLAG_KEYLIGHT,  LED_FLAG_KEYLIGHT,  LED_FLAG_KEYLIGHT,
    /* index=48 */  LED_FLAG_KEYLIGHT,  LED_FLAG_KEYLIGHT,  LED_FLAG_KEYLIGHT,
    /* index=51 */  LED_FLAG_KEYLIGHT,  LED_FLAG_KEYLIGHT,  LED_FLAG_KEYLIGHT, // Thumb cluster
    // Underglow.
    /* index=54 */ LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
    /* index=57 */ LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
    /* index=60 */ LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
    /* index=63 */ LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
    /* index=66 */ LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
    /* index=69 */ LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
} };
#endif
// clang-format on

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    oled_clear();
    oled_render();
    return OLED_ROTATION_180;
}

__attribute__((weak)) bool oled_task_user(void) {
    oled_write("Hello ", /* invert= */ false);
    oled_write_ln("DILEMMA", /* invert= */ true);
    return false;
}
#endif
