// Copyright 2023 cyrilfiggus (@cyrilfiggus)
// SPDX-License-Identifier: GPL-2.0-or-later

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
#define OSM_SFT OSM(MOD_LSFT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_ortho_4x12_1x2uC(
        QK_GESC, KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC,
        KC_TAB , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_ENT ,
        OSM_SFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_UP  , KC_QUOT,
        KC_LCTL, KC_NO  , KC_LGUI, KC_LALT, LOWER,      KC_SPC ,       RAISE  , KC_SLSH, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_LOWER] = LAYOUT_ortho_4x12_1x2uC(
        XXXXXXX, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_DEL ,
        XXXXXXX, KC_LBRC, KC_RBRC, XXXXXXX, XXXXXXX, KC_PSLS, KC_PAST, KC_4   , KC_5   , KC_6   , KC_PDOT, _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MINS, KC_EQL,  KC_1   , KC_2   , KC_3   , KC_PGUP, KC_INS,
        _______, _______, _______, _______, _______,    KC_BSPC,       _______, KC_BSLS, KC_HOME, KC_PGDN, KC_END
    ),
    [_RAISE] = LAYOUT_ortho_4x12_1x2uC(
        XXXXXXX, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_PSCR,
        XXXXXXX, KC_F11 , KC_F12 , KC_SCRL, KC_PAUS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPRV, KC_VOLU, KC_MNXT,
        _______, _______, _______, _______, _______,    KC_DEL ,       _______, XXXXXXX, KC_MUTE, KC_VOLD, KC_MPLY
    ),
    [_ADJUST] = LAYOUT_ortho_4x12_1x2uC(
        KC_NUM,  RGB_MOD, RGB_SPI, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_RBT,
        AS_TOGG, RGB_RMOD,RGB_SPD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, _______, AG_NORM, AG_SWAP, _______,    RGB_TOG,       _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
