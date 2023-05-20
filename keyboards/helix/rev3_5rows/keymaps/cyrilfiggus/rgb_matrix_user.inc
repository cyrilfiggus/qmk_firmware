RGB_MATRIX_EFFECT(keytype_light_effect)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

    extern led_config_t g_led_config;

    bool keytype_light_effect(effect_params_t* params) {

        RGB_MATRIX_USE_LIMITS(led_min, led_max);
        uint8_t layer = get_highest_layer(layer_state | default_layer_state);

        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {

                uint8_t index = g_led_config.matrix_co[row][col];

                if (index >= led_min && index <= led_max && index != NO_LED) {

                    uint16_t key = keymap_key_to_keycode(layer, (keypos_t){col, row});
                    uint16_t hue = rgb_matrix_get_hue();
                    uint16_t sat = rgb_matrix_get_sat();
                    uint16_t val = rgb_matrix_get_val();

                    /* If transparent, check layers below until a non-transparent key is found */
                    int i = 0;
                    while (key == KC_TRNS) {
                        key = keymap_key_to_keycode(layer - i, (keypos_t){col, row});
                        i ++;
                    }

                    /* Reference codes in quantum/keycodes.h */
                    if (key >= KC_A && key <= KC_Z) {                   // alphas
                        sat = 0;    // White
                    } else if ((key >= KC_1 && key <= KC_0) ||          // numbers
                               (key >= KC_P1 && key <= KC_P0)) {
                        hue = 36;   // Gold
                    } else if ((key >= KC_ENTER &&                      // symbols
                                key <= KC_SLASH) ||
                               (key >= KC_KP_SLASH && key <= KC_PENT) ||
                               key == KC_PDOT ||
                               key == KC_PEQL ||
                               key == QK_GRAVE_ESCAPE) {
                        hue = 128;  // Cyan
                    } else if ((key >= KC_F1 && key <= KC_F12) ||       // f-keys
                                key == KC_PAUSE) {
                        hue = 36;   // Gold
                    } else if (key == KC_CAPS_LOCK ||                   // toggles
                               key == KC_PRINT_SCREEN ||
                               key == KC_SCROLL_LOCK ||
                               key == KC_NUM_LOCK ||
                               key == RGB_TOG ||
                               key == QK_AUTO_SHIFT_TOGGLE ||
                               key == QK_COMBO_TOGGLE ||
                               key == QK_ONE_SHOT_TOGGLE ||
                               key == QK_SECURE_TOGGLE ||
                               key == QK_CAPS_WORD_TOGGLE ||
                               key == QK_AUTOCORRECT_TOGGLE ||
                               key == DB_TOGG ||
                               key == QK_RBT) {
                        hue = 0;    // Red
                    } else if (IS_MAGIC_KEYCODE(key)) {                 // magic
                        hue = 0;    // Red
                    } else if (IS_QK_LAYER_TAP(key) ||                  // layers
                               IS_QK_LAYER_MOD(key) ||
                               IS_QK_TO(key) ||
                               IS_QK_MOMENTARY(key) ||
                               IS_QK_DEF_LAYER(key) ||
                               IS_QK_TOGGLE_LAYER(key) ||
                               IS_QK_ONE_SHOT_LAYER(key) ||
                               IS_QK_LAYER_TAP_TOGGLE(key)) {
                        hue = 234;  // Pink
                    } else if ((key >= KC_INSERT && key <= KC_UP) ||    // nav + arrows
                               (key >= KC_AUDIO_MUTE &&
                                key <= KC_MEDIA_PLAY_PAUSE)) {
                        hue = 191;  // Purple
                    } else if (IS_MODIFIER_KEYCODE(key) ||              // modifiers
                               IS_QK_ONE_SHOT_MOD(key)) {
                        hue = 21;   // Orange
                    } else if (IS_RGB_KEYCODE(key) ||                   // rgb changers
                               IS_BACKLIGHT_KEYCODE(key) ||
                               IS_QK_LIGHTING(key)) {
                        hue = 191;  // Purple
                    } else if (IS_MOUSE_KEYCODE(key)) {                 // mouse keys
                        hue = 85;   // Green
                    } else if (key == KC_NO) {                          // off
                        val = 0;
                    } else {                                            // undefined
                        hue = 170;  // Blue
                    }

                    HSV hsv = {hue, sat, val};
                    RGB rgb = hsv_to_rgb(hsv);
                    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                }
            }
        }
        return rgb_matrix_check_finished_leds(led_max);
    }

#endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
