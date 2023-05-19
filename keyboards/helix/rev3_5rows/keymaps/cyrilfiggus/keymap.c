/* Copyright 2020 yushakobo
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

#include QMK_KEYBOARD_H

enum layer_names {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST
};

#define LOWER   MO(_LOWER)
#define RAISE   MO(_RAISE)
#define ADJUST  MO(_ADJUST)
#define SPC_FN1 LT(1, KC_SPC)
#define SPC_FN2 LT(2, KC_SPC)
#define TT_LOW  TT(LOWER)       // Hold for MO(LOWER), tap TAP_TOGGLE times to toggle layer ON, and again for OFF
#define TT_RAI  TT(RAISE)
#define OSM_SFT OSM(MOD_LSFT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        KC_MUTE, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
        QK_GESC, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
        OSM_SFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LBRC, KC_RBRC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_QUOT,
        KC_LCTL, LOWER,   KC_LGUI, KC_LALT, KC_SPC,  SPC_FN1, KC_MINS, KC_EQL,  TT_RAI,  KC_BSLS, KC_SLSH, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_LOWER] = LAYOUT(
        XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
        XXXXXXX, KC_F11,  KC_F12,  KC_PSCR, KC_SCRL, KC_PAUS,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, KC_INS,
        _______, _______, _______, _______, _______, _______, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, KC_HOME, KC_PGDN, KC_END
    ),

    [_RAISE] = LAYOUT(
        KC_NUM,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, KC_BTN3, XXXXXXX, XXXXXXX, _______,
        AS_TOGG, RGB_MOD, RGB_SPI, RGB_HUI, RGB_SAI, RGB_VAI,                   XXXXXXX, KC_BTN1, KC_MS_U, KC_BTN2 ,XXXXXXX, _______,
        XXXXXXX, RGB_RMOD,RGB_SPD, RGB_HUD, RGB_SAD, RGB_VAD,                   XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, _______,
        KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPRV, KC_VOLU, KC_MNXT,
        _______, _______, AG_NORM, AG_SWAP, _______, _______, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, KC_MUTE, KC_VOLD, KC_MPLY
    ),

    [_ADJUST] =  LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    )
};

#ifdef ENCODER_MAP_ENABLE

    const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
        [0] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
        [1] = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
        [2] = {ENCODER_CCW_CW(RGB_SAD, RGB_SAI)},
        [3] = {ENCODER_CCW_CW(RGB_HUD, RGB_HUI)}
    };

#endif  // ENCODER_MAP_ENABLE

#ifdef RGBLIGHT_ENABLE
    // Make all colour names the same length, group colours with types of keys
    #define OFF_    HSV_OFF         // White
    #define ZERO    0               // Colour selected by RGBA keys

    #define MODS    HSV_ORANGE      // Modifiers
    #define SYMS    HSV_CYAN        // Symbols
    #define NUMS    HSV_GOLD        // Numbers
    #define ARRS    HSV_PURPLE      // Arrows

    #define FCNS    HSV_GOLDENROD   // F Keys
    #define PRTS    HSV_RED         // Print Screen

    #define TOGS    HSV_RED         // Toggle keys

    #define MARR    HSV_ORANGE      // Mouse directions
    #define MBUT    HSV_MAGENTA     // Mouse buttons
    #define MSPD    HSV_AZURE       // Mouse speed

    #define RGBA    HSV_BLUE        // RGB backlighting

    #define MO_L    HSV_PINK        // Lower Layer
    #define MO_R    HSV_PINK        // Raise Layer
    #define MO_A    HSV_PINK        // Adjust Layer

    const rgblight_segment_t PROGMEM qwerty_left[] = RGBLIGHT_LAYER_SEGMENTS(
        { 5,1,ARRS},{ 4,1,NUMS},{ 3,1,NUMS},{ 2,1,NUMS},{ 1,1,NUMS},{ 0,1,NUMS},
        { 6,1,SYMS},{ 7,0,ZERO},{ 8,0,ZERO},{ 9,0,ZERO},{10,0,ZERO},{11,0,ZERO},
        {17,1,SYMS},{16,0,ZERO},{15,0,ZERO},{14,0,ZERO},{13,0,ZERO},{12,0,ZERO},
        {18,1,MODS},{19,0,ZERO},{20,0,ZERO},{21,0,ZERO},{22,0,ZERO},{23,0,ZERO},{24,1,SYMS},
        {31,1,MODS},{30,1,MO_L},{29,1,MODS},{28,1,MODS},{27,1,MO_R},{26,1,MO_L},{25,1,SYMS}
    );

    const rgblight_segment_t PROGMEM qwerty_right[] = RGBLIGHT_LAYER_SEGMENTS(
                    {32,1,NUMS},{33,1,NUMS},{34,1,NUMS},{35,1,NUMS},{36,1,NUMS},{37,1,ARRS},
                    {43,0,ZERO},{42,0,ZERO},{41,0,ZERO},{40,0,ZERO},{39,0,ZERO},{38,1,SYMS},
                    {44,0,ZERO},{45,0,ZERO},{46,0,ZERO},{47,0,ZERO},{48,1,SYMS},{49,1,SYMS},
        {56,1,SYMS},{55,0,ZERO},{54,0,ZERO},{53,1,SYMS},{52,1,SYMS},{51,1,ARRS},{50,1,SYMS},
        {57,1,SYMS},{58,1,MO_R},{59,1,SYMS},{60,1,SYMS},{61,1,ARRS},{62,1,ARRS},{63,1,ARRS}
    );

    const rgblight_segment_t PROGMEM lower_left[] = RGBLIGHT_LAYER_SEGMENTS(
        { 5,1,OFF_},{ 4,1,FCNS},{ 3,1,FCNS},{ 2,1,FCNS},{ 1,1,FCNS},{ 0,1,FCNS},
        { 6,1,OFF_},{ 7,1,FCNS},{ 8,1,FCNS},{ 9,1,PRTS},{10,1,FCNS},{11,1,OFF_},
        {17,1,OFF_},{16,1,OFF_},{15,1,OFF_},{14,1,OFF_},{13,1,OFF_},{12,1,OFF_},
        {18,1,MODS},{19,1,OFF_},{20,1,OFF_},{21,1,OFF_},{22,1,OFF_},{23,1,OFF_},{24,1,OFF_},
        {31,1,MODS},{30,1,MO_L},{29,1,MODS},{28,1,MODS},{27,1,MO_R},{26,1,MO_L},{25,1,OFF_}
    );

    const rgblight_segment_t PROGMEM lower_right[] = RGBLIGHT_LAYER_SEGMENTS(
                    {32,1,FCNS},{33,1,FCNS},{34,1,FCNS},{35,1,FCNS},{36,1,FCNS},{37,1,ARRS},
                    {43,1,OFF_},{42,1,OFF_},{41,1,OFF_},{40,1,OFF_},{39,1,OFF_},{38,1,SYMS},
                    {44,1,OFF_},{45,1,OFF_},{46,1,OFF_},{47,1,OFF_},{48,1,OFF_},{49,1,SYMS},
        {56,1,OFF_},{55,1,OFF_},{54,1,OFF_},{53,1,OFF_},{52,1,OFF_},{51,1,ARRS},{50,1,ARRS},
        {57,1,OFF_},{58,1,MO_A},{59,1,OFF_},{60,1,OFF_},{61,1,ARRS},{62,1,ARRS},{63,1,ARRS}
    );

    const rgblight_segment_t PROGMEM raise_left[] = RGBLIGHT_LAYER_SEGMENTS(
        { 5,1,TOGS},{ 4,1,OFF_},{ 3,1,OFF_},{ 2,1,OFF_},{ 1,1,OFF_},{ 0,1,OFF_},
        { 6,1,TOGS},{ 7,1,RGBA},{ 8,1,RGBA},{ 9,1,RGBA},{10,1,RGBA},{11,1,RGBA},
        {17,1,OFF_},{16,1,RGBA},{15,1,RGBA},{14,1,RGBA},{13,1,RGBA},{12,1,RGBA},
        {18,1,TOGS},{19,1,OFF_},{20,1,OFF_},{21,1,OFF_},{22,1,OFF_},{23,1,OFF_},{24,1,OFF_},
        {31,1,MODS},{30,1,MO_A},{29,1,TOGS},{28,1,TOGS},{27,1,MO_R},{26,1,MO_L},{25,1,OFF_}
    );

    const rgblight_segment_t PROGMEM raise_right[] = RGBLIGHT_LAYER_SEGMENTS(
                    {32,1,OFF_},{33,1,OFF_},{34,1,MBUT},{35,1,OFF_},{36,1,OFF_},{37,1,ARRS},
                    {43,1,OFF_},{42,1,MBUT},{41,1,MARR},{40,1,MBUT},{39,1,OFF_},{38,1,SYMS},
                    {44,1,OFF_},{45,1,MARR},{46,1,MARR},{47,1,MARR},{48,1,OFF_},{49,1,SYMS},
        {56,1,OFF_},{55,1,OFF_},{54,1,OFF_},{53,1,OFF_},{52,1,ARRS},{51,1,ARRS},{50,1,ARRS},
        {57,1,OFF_},{58,1,MO_R},{59,1,OFF_},{60,1,OFF_},{61,1,ARRS},{62,1,ARRS},{63,1,ARRS}
    );

    const rgblight_segment_t PROGMEM adjust_left[] = RGBLIGHT_LAYER_SEGMENTS(
        { 5,1,OFF_},{ 4,1,OFF_},{ 3,1,OFF_},{ 2,1,OFF_},{ 1,1,OFF_},{ 0,1,OFF_},
        { 6,1,OFF_},{ 7,1,OFF_},{ 8,1,OFF_},{ 9,1,OFF_},{10,1,OFF_},{11,1,OFF_},
        {17,1,OFF_},{16,1,OFF_},{15,1,OFF_},{14,1,OFF_},{13,1,OFF_},{12,1,OFF_},
        {18,1,MODS},{19,1,OFF_},{20,1,OFF_},{21,1,OFF_},{22,1,OFF_},{23,1,OFF_},{24,1,OFF_},
        {31,1,MODS},{30,1,MO_L},{29,1,MODS},{28,1,MODS},{27,1,MO_R},{26,1,MO_L},{25,1,OFF_}
    );

    const rgblight_segment_t PROGMEM adjust_right[] = RGBLIGHT_LAYER_SEGMENTS(
                    {32,1,OFF_},{33,1,OFF_},{34,1,OFF_},{35,1,OFF_},{36,1,OFF_},{37,1,ARRS},
                    {43,1,OFF_},{42,1,OFF_},{41,1,OFF_},{40,1,OFF_},{39,1,OFF_},{38,1,SYMS},
                    {44,1,OFF_},{45,1,OFF_},{46,1,OFF_},{47,1,OFF_},{48,1,OFF_},{49,1,SYMS},
        {56,1,OFF_},{55,1,OFF_},{54,1,OFF_},{53,1,OFF_},{52,1,OFF_},{51,1,OFF_},{50,1,OFF_},
        {57,1,OFF_},{58,1,MO_A},{59,1,OFF_},{60,1,OFF_},{61,1,OFF_},{62,1,OFF_},{63,1,OFF_}
    );

    // Now define the array of layers. Later layers take precedence
    const rgblight_segment_t* const PROGMEM rgb_left[] = RGBLIGHT_LAYERS_LIST(
        qwerty_left,
        lower_left,
        raise_left,
        adjust_left
    );

    const rgblight_segment_t* const PROGMEM rgb_right[] = RGBLIGHT_LAYERS_LIST(
        qwerty_right,
        lower_right,
        raise_right,
        adjust_right
    );

    void keyboard_post_init_user(void) {
        if (is_keyboard_left()) {
            rgblight_layers = rgb_left;
        } else {
            rgblight_layers = rgb_right;
        }
    }

    layer_state_t default_layer_state_set_user(layer_state_t state) {
        rgblight_set_layer_state(0, layer_state_cmp(state, _QWERTY));
        return state;
    }

    layer_state_t layer_state_set_user(layer_state_t state) {
        rgblight_set_layer_state(1, layer_state_cmp(state, _LOWER));
        rgblight_set_layer_state(2, layer_state_cmp(state, _RAISE));
        return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    }

#else
    layer_state_t layer_state_set_user(layer_state_t state) {
        return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    }

#endif  // RGBLIGHT_ENABLE

#ifdef RGB_MATRIX_ENABLE
    #include "split_util.h"

    #ifdef RGB_MATRIX_ENABLE
        led_config_t g_led_config = {
            {
                // Key Matrix to LED Index
                // g_led_config.matrix_co
                { 5,  4,  3,  2,  1,  0, NO_LED},
                { 6,  7,  8,  9, 10, 11, NO_LED},
                {17, 16, 15, 14, 13, 12, NO_LED},
                {18, 19, 20, 21, 22, 23,     24},
                {31, 30, 29, 28, 27, 26,     25},
                {37, 36, 35, 34, 33, 32, NO_LED},
                {38, 39, 40, 41, 42, 43, NO_LED},
                {49, 48, 47, 46, 45, 44, NO_LED},
                {50, 51, 52, 53, 54, 55,     56},
                {63, 62, 61, 60, 59, 58,     57},
            }, {
                // LED Index to Physical Position
                // g_led_config.point
                { 86,  0}, { 68,  0}, { 51,  0}, { 34,  0}, { 17,  0}, {  0,  0},
                {  0, 16}, { 17, 16}, { 34, 16}, { 51, 16}, { 68, 16}, { 86, 16},
                { 86, 32}, { 68, 32}, { 51, 32}, { 34, 32}, { 17, 32}, {  0, 32},
                {  0, 48}, { 17, 48}, { 34, 48}, { 51, 48}, { 68, 48}, { 86, 48}, {103, 48},
                {103, 64}, { 86, 64}, { 68, 64}, { 51, 64}, { 34, 64}, { 17, 64}, {  0, 64},
                {137,  0}, {155,  0}, {172,  0}, {189,  0}, {206,  0}, {224,  0},
                {224, 16}, {206, 16}, {189, 16}, {172, 16}, {155, 16}, {137, 16},
                {137, 32}, {155, 32}, {172, 32}, {189, 32}, {206, 32}, {224, 32},
                {224, 48}, {206, 48}, {189, 48}, {172, 48}, {155, 48}, {137, 48}, {120, 48},
                {120, 64}, {137, 64}, {155, 64}, {172, 64}, {189, 64}, {206, 64}, {224, 64}
            }, {
                // LED Index to Flag
                // g_led_config.flags
                4, 4, 4, 4, 4, 1,
                1, 4, 4, 4, 4, 4,
                4, 4, 4, 4, 4, 1,
                1, 4, 4, 4, 4, 4, 4,
                1, 1, 1, 1, 1, 1, 1,
                4, 4, 4, 4, 4, 1,
                1, 4, 4, 4, 4, 4,
                4, 4, 4, 4, 4, 1,
                1, 4, 4, 4, 4, 4, 4,
                1, 1, 1, 1, 1, 1, 1,
            }
        };
    #endif  // RGB_MATRIX_ENABLE

#endif
