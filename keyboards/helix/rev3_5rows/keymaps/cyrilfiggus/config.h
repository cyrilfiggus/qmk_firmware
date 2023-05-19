/*
Copyright 2020 yushakobo

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

/* List of config options:
https://github.com/qmk/qmk_firmware/blob/master/docs/config_options.md#the-configh-file
*/

#pragma once

/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 7
#define DIODE_DIRECTION COL2ROW
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3, B2 }
#define MATRIX_ROW_PINS { D4, C6, D7, E6, B4 }

/* Split hand configration */
/* Use "-bl avrdude-split-left" on Atmega, and "-bl uf2-split-left" on RP2040 */
#undef SPLIT_HAND_MATRIX_GRID
#undef SPLIT_HAND_MATRIX_GRID_LOW_IS_RIGHT
#define EE_HANDS                    // Only works if SPLIT_HAND_PIN and SPLIT_HAND_MATRIX_GRID are not defined
#define SPLIT_LAYER_STATE_ENABLE    // Ensures the current layer state is available on the slave when using the QMK-provided split transport.
#define SPLIT_MODS_ENABLE           // Enables transmitting modifier state (normal, weak and oneshot) to the non primary side of the split keyboard
#define SPLIT_LED_STATE_ENABLE      // Ensures the current host indicator state (caps/num/scroll) is available on the slave when using the QMK-provided split transport.
#define SOFT_SERIAL_PIN D2          // Also needs 'SPLIT_KEYBOARD = yes' in rules.mk

/* Handwired encoder settings */
#undef ENCODERS_PAD_A
#undef ENCODERS_PAD_B
#define ENCODERS_PAD_A { B5 }
#define ENCODERS_PAD_B { B6 }
#define ENCODER_RESOLUTIONS { 4 }

/* RGB lighting */
#define RGB_DI_PIN D3
#define RGBLED_NUM 64

#ifdef RGBLIGHT_ENABLE
    // Needed if both halves of the board have RGB LEDs wired directly to the RGB output pin on the controllers
    //   instead of passing the output of the left half to the input of the right half. Uses I2C along with keypresses.
    // #define RGBLIGHT_SPLIT  // When RGBLED_SPLIT is defined, 'RGBLIGHT_SPLIT' is implicitly defined.
    #define RGBLED_SPLIT { 32, 32 }
    #undef RGBLIGHT_LIMIT_VAL
    #define RGBLIGHT_LIMIT_VAL 120
    #undef RGBLIGHT_HUE_STEP
    #define RGBLIGHT_HUE_STEP 12
    #undef RGBLIGHT_SAT_STEP
    #define RGBLIGHT_SAT_STEP 12
    #undef RGBLIGHT_VAL_STEP
    #define RGBLIGHT_VAL_STEP 12
    #undef RGBLIGHT_SPD_STEP
    #define RGBLIGHT_SPD_STEP 12
    #define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_STATIC_LIGHT
    #define RGBLIGHT_DEFAULT_HUE 0
    #define RGBLIGHT_DEFAULT_SAT 0
    #define RGBLIGHT_DEFAULT_VAL 100
    #define RGBLIGHT_DEFAULT_SPD 0

    #define RGBLIGHT_LAYERS             // Needed for RGB lighting layers
    #define RGBLIGHT_LAYERS_RETAIN_VAL  // RGB layers use the current brightness


    // #define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
    #undef RGBLIGHT_ANIMATIONS
    #undef RGBLIGHT_EFFECT_RAINBOW_MOOD
    #undef RGBLIGHT_EFFECT_RAINBOW_SWIRL
    #undef RGBLIGHT_EFFECT_STATIC_GRADIENT
    // #undef RGBLIGHT_EFFECT_RGB_TEST     // For whatever reason, this needs to be commented out in order for layer change colors to work.
#endif

#ifdef RGB_MATRIX_ENABLE
    #define RGB_MATRIX_LED_COUNT RGBLED_NUM
    #define RGB_MATRIX_SPLIT {32, 32}
    #undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 120 // limits maximum brightness of LEDs to 150 out of 255. Higher may cause the controller to crash.
    #undef RGB_MATRIX_HUE_STEP
    #define RGB_MATRIX_HUE_STEP 10
    #undef RGB_MATRIX_SAT_STEP
    #define RGB_MATRIX_SAT_STEP 10
    #undef RGB_MATRIX_VAL_STEP
    #define RGB_MATRIX_VAL_STEP 10
    #undef RGB_MATRIX_SPD_STEP
    #define RGB_MATRIX_SPD_STEP 10
    #define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR
    #define RGB_MATRIX_DEFAULT_HUE 0
    #define RGB_MATRIX_DEFAULT_SAT 0
    #define RGB_MATRIX_DEFAULT_VAL 100
    #define RGB_MATRIX_DEFAULT_SPD 100
    #define RGB_MATRIX_TIMEOUT 60000

    #define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON

    #undef RGB_DISABLE_WHEN_USB_SUSPENDED
    #undef RGB_MATRIX_FRAMEBUFFER_EFFECTS
#endif

/* Mousekeys settings */
#ifdef MOUSEKEY_ENABLE
    #define MOUSEKEY_INTERVAL 16
    #define MOUSEKEY_OFFSET 1
    #define MOUSEKEY_MAX_SPEED 3
    #define MOUSEKEY_TIME_TO_MAX 50
#endif

/* Custom font */
#define OLED_FONT_H "keyboards/helix/common/glcdfont.c"

/* Esc on L side, below encoder */
#define BOOTMAGIC_LITE_ROW 1
#define BOOTMAGIC_LITE_COLUMN 0

/* Auto Shift settings */
#define AUTO_SHIFT_TIMEOUT 200
// #define AUTO_SHIFT_REPEAT

/* Caps Word settings */
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD
#define CAPS_WORD_IDLE_TIMEOUT 2000

/* One Shot Mods settings */
// #define NO_ACTION_ONESHOT       // disable one-shot modifiers
#define ONESHOT_TIMEOUT 1000

/* Tapping settings */
#define TAPPING_TOGGLE 3
#define TAPPING_TERM 200

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#undef LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#undef LOCKING_RESYNC_ENABLE

/* For replacing Atmega Pro Micro with RP2040 version
 * Activated by default on Sparkfun ProMicro 2040
 *
 * Must remove "#include <stdio.h>" from kb-level "config.h" for conversion to work.
 * Compile with CONVERT_TO=promicro_rp2040 in rules.mk
 * Flash by double-tapping RESET button
 */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET                  // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U     // Timeout window in ms in which the double tap can occur.
// #define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP17         // Specify a optional status led by GPIO number which blinks when entering the bootloader
