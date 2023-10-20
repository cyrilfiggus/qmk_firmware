// Copyright 2023 cyrilfiggus (@cyrilfiggus)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

#define LAYOUT_numpad_5x4( \
    K00,  K01,  K02,  K03, \
    K10,  K11,  K12,       \
    K20,  K21,  K22,  K13, \
    K30,  K31,  K32,       \
       K40,     K41,  K42  \
    ) { \
        { K00,   K01,  K02,  K03   }, \
        { K10,   K11,  K12,  KC_NO }, \
        { K20,   K21,  K22,  K13   }, \
        { K30,   K31,  K32,  KC_NO }, \
        { KC_NO, K40,  K41,  K42,  }, \
}
