// Copyright 2023 cyrilfiggus (@cyrilfiggus)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layer_names {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST
};

#define LOWER   MO(_LOWER)
#define RAISE   MO(_RAISE)
#define ADJUST  MO(_ADJUST)
#define LO_SLS  LT(1, KC_PSLS)
#define RA_AST  LT(2, KC_PAST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /*  Numlock ON             Numlock OFF
   * ,-------------------.  ,-------------------.
   * | NL | /  | *  | -  |  | NL | /  | *  | -  |
   * |----|----|----|----|  |----|----|----|----|
   * | 7  | 8  | 9  |    |  |HOME| UP |PgUp|    |
   * |----|----|----| +  |  |----|----|----| +  |
   * | 4  | 5  | 6  |    |  |LEFT| XX |RGHT|    |
   * |----|----|----|----|  |----|----|----|----|
   * | 1  | 2  | 3  |    |  |END | DN |PgDn|    |
   * |----|----|----| En |  |----|----|----| En |
   * |    0    | .  |    |  |   INS   |DEL |    |
   * `-------------------'  `-------------------'
   *
   * QK_RBT is on the same key as Bootmagic, so just keep holding it down to flash.
   */

    [_BASE] = LAYOUT_numpad_5x4(
        KC_NUM,  LO_SLS,  RA_AST,  KC_PMNS,
        KC_P7,   KC_P8,   KC_P9,
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,   KC_P2,   KC_P3,
            KC_P0,        KC_PDOT, KC_PENT
    ),

    [_LOWER] = LAYOUT_numpad_5x4(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,
            KC_TRNS,      KC_BSPC, KC_TRNS
    ),

    [_RAISE] = LAYOUT_numpad_5x4(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,
            XXXXXXX,      XXXXXXX, XXXXXXX
    ),

    [_ADJUST] = LAYOUT_numpad_5x4(
        XXXXXXX, XXXXXXX, XXXXXXX, QK_RBT,
        XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,
            XXXXXXX,      XXXXXXX, XXXXXXX
    ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
