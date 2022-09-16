diff --git a/keyboards/bastardkb/charybdis/3x5_3/keymaps/simian/config.h b/keyboards/bastardkb/charybdis/3x5_3/keymaps/simian/config.h
index 2c4215f629..4cb4a46347 100644
--- a/keyboards/bastardkb/charybdis/3x5_3/keymaps/simian/config.h
+++ b/keyboards/bastardkb/charybdis/3x5_3/keymaps/simian/config.h
@@ -39,6 +39,10 @@
 #    define IGNORE_MOD_TAP_INTERRUPT
 #endif  // TAPPING_TERM
 
+// Industrial encoder
+#define ENCODER_RESOLUTION 2
+//#define ENCODER_RESOLUTION 4
+
 #ifdef RGB_MATRIX_ENABLE
 // Disable control of RGB matrix by keycodes (must use firmware implementation
 // to control the feature).
diff --git a/keyboards/bastardkb/charybdis/3x5_3/keymaps/simian/keymap.c b/keyboards/bastardkb/charybdis/3x5_3/keymaps/simian/keymap.c
index ad4f157ae7..cd36a6cafa 100644
--- a/keyboards/bastardkb/charybdis/3x5_3/keymaps/simian/keymap.c
+++ b/keyboards/bastardkb/charybdis/3x5_3/keymaps/simian/keymap.c
@@ -112,7 +112,7 @@ static uint16_t auto_pointer_layer_timer = 0;
 #define LAYOUT_LAYER_ADJUST                                                                                                                 \
 XXXXXXX, TG(LAYER_NUMPAD), KC_CAPS, XXXXXXX, XXXXXXX,                  QK_BOOT, XXXXXXX, XXXXXXX,XXXXXXX , RGB_TOG,       \
        RGB_TOG, RGB_M_R, RGB_VAI, RGB_VAD, XXXXXXX,                    XXXXXXX, KC_WBAK, KC_WFWD, KC_APP, XXXXXXX,                        \
-       RGB_MOD, XXXXXXX, RGB_HUI, RGB_HUD, XXXXXXX,                    XXXXXXX , XXXXXXX, XXXXXXX, POINTER_DEFAULT_DPI_FORWARD, XXXXXXX,                       \
+       RGB_MOD, XXXXXXX, RGB_HUI, RGB_HUD, QK_BOOT,                    XXXXXXX , XXXXXXX, XXXXXXX, POINTER_DEFAULT_DPI_FORWARD, XXXXXXX,                       \
                             _______, _______, _______,_______,         KC_VOLD, KC_VOLU, KC_MPLY
 
 // Numpad
@@ -310,15 +310,15 @@ bool encoder_update_user(uint8_t index, bool clockwise) {
     //if (get_highest_layer(layer_state|default_layer_state) > 0) {
         if (IS_LAYER_ON(LAYER_ADJUST)) {
             if (clockwise) {
-                tap_code_delay(KC_VOLU, 10);
-            } else {
                 tap_code_delay(KC_VOLD, 10);
+            } else {
+                tap_code_delay(KC_VOLU, 10);
             }
         } else {
             if (clockwise) {
-                tap_code(KC_WH_U);
-            } else {
                 tap_code(KC_WH_D);
+            } else {
+                tap_code(KC_WH_U);
             }
         }
     //}
diff --git a/keyboards/bastardkb/charybdis/3x5_3/keymaps/simian/rules.mk b/keyboards/bastardkb/charybdis/3x5_3/keymaps/simian/rules.mk
index 7436aff5d8..6894bd0e4d 100644
--- a/keyboards/bastardkb/charybdis/3x5_3/keymaps/simian/rules.mk
+++ b/keyboards/bastardkb/charybdis/3x5_3/keymaps/simian/rules.mk
@@ -1,5 +1,5 @@
 #EEPROM_DRIVER = spi
-POINTING_DEVICE_DRIVER = pmw3389
+#POINTING_DEVICE_DRIVER = pmw3389
 ENCODER_ENABLE = yes
 
 
diff --git a/keyboards/bastardkb/charybdis/3x5_3/v2/splinky/config.h b/keyboards/bastardkb/charybdis/3x5_3/v2/splinky/config.h
index 2929d3dd1e..222e800c55 100644
--- a/keyboards/bastardkb/charybdis/3x5_3/v2/splinky/config.h
+++ b/keyboards/bastardkb/charybdis/3x5_3/v2/splinky/config.h
@@ -24,12 +24,12 @@
     { GP28, GP15, GP6, GP7, GP8 }
 
 /* Handedness. */
-#define MASTER_RIGHT
+//#define MASTER_RIGHT
 
 // To use the handedness pin, resistors need to be installed on the adapter PCB.
 // If so, uncomment the following code, and undefine MASTER_RIGHT above.
-// #define SPLIT_HAND_PIN GP13
-// #define SPLIT_HAND_PIN_LOW_IS_LEFT  // High -> right, Low -> left.
+ #define SPLIT_HAND_PIN GP13
+ #define SPLIT_HAND_PIN_LOW_IS_LEFT  // High -> right, Low -> left.
 
 /* serial.c configuration (for split keyboard). */
 #define SOFT_SERIAL_PIN GP1
