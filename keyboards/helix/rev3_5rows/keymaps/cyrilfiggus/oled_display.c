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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST
};

#ifdef OLED_ENABLE

    void render_status(void) {
        // Render to mode icon

        // QMK Logo Editor: https://joric.github.io/qle/
        // Logos are included in the Helix glc_font file qmk_firmware/keyboards/helix/common/glcdfont.c,
        //     this simply points to the address in that file

        static const char os_logo[][4][3] PROGMEM = {
            {
                {0x95,0x96,0}, {0xb5,0xb6,0}  // Apple Logo
            }, {
                {0x97,0x98,0}, {0xb7,0xb8,0}  // Windows Logo
            }, {
                {0x99,0x9A,0}, {0xB9,0xBA,0}  // Linux Logo
            }, {
                {0x9B,0x9C,0}, {0xBB,0xBC,0}  // Android Logo
            }
        };

        if (is_mac_mode()) {
            oled_write_P(os_logo[2][0], false);
            oled_write_P(PSTR("\n"), false);
            oled_write_P(os_logo[2][1], false);
        } else {
            oled_write_P(os_logo[0][0], false);
            oled_write_P(PSTR("\n"), false);
            oled_write_P(os_logo[0][1], false);
        }

        // Host Keyboard Layer Status
        oled_write_P(PSTR(" Layer: "), false);

        switch (get_highest_layer(layer_state)) {
            case _QWERTY:
                oled_write_P(PSTR("Base \n"), false);
                break;
            case _LOWER:
                oled_write_P(PSTR("Lower \n"), false);
                break;
            case _RAISE:
                oled_write_P(PSTR("Raise \n"), false);
                break;
            case _ADJUST:
                oled_write_P(PSTR("Adjust \n"), false);
                break;
            default:
                // Or use the write_ln shortcut over adding '\n' to the end of your string
                oled_write_ln_P(PSTR("Undefined"), false);
        }

        // Host Keyboard LED Status
        led_t led_state = host_keyboard_led_state();
        oled_write_P(led_state.num_lock     ? PSTR("NUM ")  : PSTR("    "),  false);
        oled_write_P(led_state.caps_lock    ? PSTR("CAP ")  : PSTR("    "),  false);
        oled_write_P(led_state.scroll_lock  ? PSTR("SCR ")  : PSTR("    "),  false);
        oled_write_P(is_caps_word_on()      ? PSTR("WORD ") :
                     get_oneshot_mods() == MOD_BIT(KC_LSFT) ? PSTR("SHFT ") :
                     PSTR("     "),
                    false);
        oled_write_P(get_autoshift_state()  ? PSTR("AUTO")  : PSTR("    "),  false);
    }

    static void render_logo(void) {
        // Again, just a look-up to the font file
        static const char PROGMEM qmk_logo[] = {
            0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
            0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
            0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
        };
        oled_write_P(qmk_logo, false);
    }

    const char *get_u8_str_user(uint8_t curr_num, char curr_pad) {
        /* Copy from quantum.c, change buf[4] to buf[3] */
        static char    buf[3]   = {0};
        static uint8_t last_num = 0xFF;
        static char    last_pad = '\0';
        if (last_num == curr_num && last_pad == curr_pad) {
            return buf;
        }
        last_num = curr_num;
        last_pad = curr_pad;
        return get_numeric_str(buf, sizeof(buf), curr_num, curr_pad);
    }

    static void render_rgbled_status(bool full) {
        #ifdef RGBLIGHT_ENABLE
            if (rgblight_is_enabled()) {
                if (full) {
                    oled_write_P(PSTR("M"), false);
                    oled_write(get_u8_str_user(
                        rgblight_get_mode(), ' '), false);
                    oled_write_P(PSTR(":S"), false);
                    oled_write(get_u8_str_user(
                        rgblight_get_speed() / RGBLIGHT_SPD_STEP, ' '), false);
                    oled_write_P(PSTR("; HSV:"), false);
                    oled_write(get_u8_str_user(
                        rgblight_get_hue() / RGBLIGHT_HUE_STEP, ' '), false);
                    oled_write_P(PSTR(","), false);
                    oled_write(get_u8_str_user(
                        rgblight_get_sat() / RGBLIGHT_SAT_STEP, ' '), false);
                    oled_write_P(PSTR(","), false);
                    oled_write(get_u8_str_user(
                        rgblight_get_val() / RGBLIGHT_VAL_STEP, ' '), false);
                } else {
                    oled_write_P(PSTR("M"), false);
                    oled_write(get_u8_str_user(
                        rgblight_get_mode(), ' '), false);
                }
            }
        #endif

        #ifdef RGB_MATRIX_ENABLE
            if (rgb_matrix_is_enabled()) {
                if (full) {
                    oled_write_P(PSTR("M"), false);
                    oled_write(get_u8_str_user(
                        rgb_matrix_get_mode(), ' '), false);
                    oled_write_P(PSTR(":S"), false);
                    oled_write(get_u8_str_user(
                        rgb_matrix_get_speed() / RGB_MATRIX_SPD_STEP, ' '), false);
                    oled_write_P(PSTR("; HSV:"), false);
                    oled_write(get_u8_str_user(
                        rgb_matrix_get_hue() / RGB_MATRIX_HUE_STEP, ' '), false);
                    oled_write_P(PSTR(","), false);
                    oled_write(get_u8_str_user(
                        rgb_matrix_get_sat() / RGB_MATRIX_SAT_STEP, ' '), false);
                    oled_write_P(PSTR(","), false);
                    oled_write(get_u8_str_user(
                        rgb_matrix_get_val() / RGB_MATRIX_VAL_STEP, ' '), false);
                } else {
                    oled_write_P(PSTR("M"), false);
                    oled_write(get_u8_str_user(
                        rgb_matrix_get_mode(), ' '), false);
                }
            }
        #endif
    }

    bool oled_task_user(void) {
        // Always render on the same side
        if (is_keyboard_left()) {
            render_status();
            render_rgbled_status(true);
        } else {
            render_logo();
        }
        return false;
    }

#endif  // OLED_ENABLE
