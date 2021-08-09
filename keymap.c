/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

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

#include QMK_KEYBOARD_H
#include "rgb_matrix_map.h"
#include "print.h"

enum custom_keycodes {
    KCRGB_1 = SAFE_RANGE,
    KCRGB_2,
    KCRGB_3,
    KCRGB_4,
    KCRGB_5,
    KCRGB_6,
    KCRGB_7,
    KCRGB_8,
    KCRGB_9,
    KCRGB_0
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the RESET key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backslash. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [1] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, KCRGB_1, KCRGB_2, KCRGB_3, KCRGB_4, KCRGB_5, KCRGB_6, KCRGB_7, KCRGB_8, KCRGB_9, KCRGB_0, _______, _______, _______,          RGB_TOG,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,            RGB_SPI,
        _______, RGB_M_P, RGB_M_B, RGB_M_R, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          RGB_SPD,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, RGB_VAI, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, RGB_RMOD, RGB_VAD, RGB_MOD
    ),


};


/* Time Functions */
#define TIMEOUT_THRESHOLD_DEFAULT   5    // default timeout minutes
#define TIMEOUT_THRESHOLD_MAX       140  // upper limits (2 hours and 10 minutes -- no rgb indicators above this value)
static uint16_t timeout_timer = 0;
static uint16_t timeout_counter = 0;  //in minute intervals
static uint16_t timeout_threshold = TIMEOUT_THRESHOLD_DEFAULT;

void timeout_reset_timer(void) {
    timeout_timer = timer_read();
    timeout_counter = 0;
};

void timeout_update_threshold(bool increase) {
    if (increase && timeout_threshold < TIMEOUT_THRESHOLD_MAX) timeout_threshold++;
    if (!increase && timeout_threshold > 0) timeout_threshold--;
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case KCRGB_1:
        if (record->event.pressed) {
            if (get_highest_layer(layer_state) == 1) {
                rgblight_sethsv(HSV_WHITE);
            }
        }
        break;
    case KCRGB_2:
        if (record->event.pressed) {
            if (get_highest_layer(layer_state) == 1) {
                rgblight_sethsv(HSV_GOLD);
            }
        }
        break;
    case KCRGB_3:
        if (record->event.pressed) {
            if (get_highest_layer(layer_state) == 1) {
                rgblight_sethsv(HSV_SPRINGGREEN);
            }
        }
        break;
    case KCRGB_4:
        if (record->event.pressed) {
            if (get_highest_layer(layer_state) == 1) {
                rgblight_sethsv(HSV_TEAL);
            }
        }
        break;
    case KCRGB_5:
        if (record->event.pressed) {
            if (get_highest_layer(layer_state) == 1) {
                rgblight_sethsv(HSV_CYAN);
            }
        }
        break;
    case KCRGB_6:
        if (record->event.pressed) {
            if (get_highest_layer(layer_state) == 1) {
                rgblight_sethsv(HSV_PURPLE);
            }
        }
        break;
    case KCRGB_7:
        if (record->event.pressed) {
            if (get_highest_layer(layer_state) == 1) {
                rgblight_sethsv(HSV_MAGENTA);
            }
        }
        break;
    case KCRGB_8:
        if (record->event.pressed) {
            if (get_highest_layer(layer_state) == 1) {
                rgblight_sethsv(HSV_PINK);
            }
        }
        break;
    case KCRGB_9:
        if (record->event.pressed) {
            if (get_highest_layer(layer_state) == 1) {
                rgblight_sethsv(HSV_RED);
            }
        }
        break;
    case KCRGB_0:
        if (record->event.pressed) {
            if (get_highest_layer(layer_state) == 1) {
                rgblight_sethsv(HSV_BLACK);
            }
        }
        break;
    default:
        if (record->event.pressed) { // reset activity timer
            #ifdef RGB_MATRIX_ENABLE
                rgb_matrix_enable();
            #endif
            timeout_reset_timer();
        }
        break;
    }
    return true;
};

void matrix_scan_user(void) {
    if (timeout_threshold > 0) {
        if (timer_elapsed(timeout_timer) >= 60000) { // 1 minute tick
            timeout_counter++;
            timeout_timer = timer_read();
        }
        #ifdef RGB_MATRIX_ENABLE
            if (timeout_threshold > 0 && timeout_counter >= timeout_threshold) {
                rgb_matrix_disable_noeeprom();
            }
        #endif
    } // timeout_threshold = 0 will disable timeout
};

/* RGB Functions */
#ifdef RGB_MATRIX_ENABLE
    void handle_current_animation_rgb(void) {

        // Set initial colors
        rgb_matrix_set_color(LED_F1, RGB_BLACK);
        rgb_matrix_set_color(LED_F2, RGB_BLACK);
        rgb_matrix_set_color(LED_F3, RGB_BLACK);
        rgb_matrix_set_color(LED_F4, RGB_BLACK);
        rgb_matrix_set_color(LED_F5, RGB_BLACK);
        rgb_matrix_set_color(LED_F6, RGB_BLACK);
        rgb_matrix_set_color(LED_F7, RGB_BLACK);
        rgb_matrix_set_color(LED_F8, RGB_BLACK);
        rgb_matrix_set_color(LED_F9, RGB_BLACK);
        rgb_matrix_set_color(LED_F10, RGB_BLACK);
        rgb_matrix_set_color(LED_F11, RGB_BLACK);
        rgb_matrix_set_color(LED_F12, RGB_BLACK);

        rgb_matrix_set_color(LED_ESC, RGB_WHITE);

        switch(rgb_matrix_get_mode()) {
            case 1:
                rgb_matrix_set_color(LED_F1, RGB_WHITE);
                break;
            case 2:
                rgb_matrix_set_color(LED_F2, RGB_WHITE);
                break;
            case 3:
                rgb_matrix_set_color(LED_F3, RGB_WHITE);
                break;
            case 4:
                rgb_matrix_set_color(LED_F4, RGB_WHITE);
                break;
            case 5:
                rgb_matrix_set_color(LED_F5, RGB_WHITE);
                break;
            case 6:
                rgb_matrix_set_color(LED_F6, RGB_WHITE);
                break;
            case 7:
                rgb_matrix_set_color(LED_F7, RGB_WHITE);
                break;
            case 8:
                rgb_matrix_set_color(LED_F8, RGB_WHITE);
                break;
            case 9:
                rgb_matrix_set_color(LED_F9, RGB_WHITE);
                break;
            case 10:
                rgb_matrix_set_color(LED_F10, RGB_WHITE);
                break;
            case 11:
                rgb_matrix_set_color(LED_F11, RGB_WHITE);
                break;
            case 12:
                rgb_matrix_set_color(LED_F12, RGB_WHITE);
                break;
            case 13:
                rgb_matrix_set_color(LED_ESC, RGB_RED);
                rgb_matrix_set_color(LED_F1, RGB_WHITE);
                break;
            case 14:
                rgb_matrix_set_color(LED_ESC, RGB_RED);
                rgb_matrix_set_color(LED_F2, RGB_WHITE);
                break;
            case 15:
                rgb_matrix_set_color(LED_ESC, RGB_RED);
                rgb_matrix_set_color(LED_F3, RGB_WHITE);
                break;
            case 16:
                rgb_matrix_set_color(LED_ESC, RGB_RED);
                rgb_matrix_set_color(LED_F4, RGB_WHITE);
                break;
            case 17:
                rgb_matrix_set_color(LED_ESC, RGB_RED);
                rgb_matrix_set_color(LED_F5, RGB_WHITE);
                break;
            case 18:
                rgb_matrix_set_color(LED_ESC, RGB_RED);
                rgb_matrix_set_color(LED_F6, RGB_WHITE);
                break;
            case 19:
                rgb_matrix_set_color(LED_ESC, RGB_RED);
                rgb_matrix_set_color(LED_F7, RGB_WHITE);
                break;
            case 20:
                rgb_matrix_set_color(LED_ESC, RGB_RED);
                rgb_matrix_set_color(LED_F8, RGB_WHITE);
                break;
            case 21:
                rgb_matrix_set_color(LED_ESC, RGB_RED);
                rgb_matrix_set_color(LED_F9, RGB_WHITE);
                break;
            case 22:
                rgb_matrix_set_color(LED_ESC, RGB_RED);
                rgb_matrix_set_color(LED_F10, RGB_WHITE);
                break;
            case 23:
                rgb_matrix_set_color(LED_ESC, RGB_RED);
                rgb_matrix_set_color(LED_F11, RGB_WHITE);
                break;
            case 24:
                rgb_matrix_set_color(LED_ESC, RGB_RED);
                rgb_matrix_set_color(LED_F12, RGB_WHITE);
                break;
            case 25:
                rgb_matrix_set_color(LED_ESC, RGB_GOLD);
                rgb_matrix_set_color(LED_F1, RGB_WHITE);
                break;
            case 26:
                rgb_matrix_set_color(LED_ESC, RGB_GOLD);
                rgb_matrix_set_color(LED_F2, RGB_WHITE);
                break;
            case 27:
                rgb_matrix_set_color(LED_ESC, RGB_GOLD);
                rgb_matrix_set_color(LED_F3, RGB_WHITE);
                break;
            default:
                break;
        }
    }

    void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
        switch(get_highest_layer(layer_state)) {
            case 1: // Layer 1
                // Show the color schemes in the NUM ROW
                rgb_matrix_set_color(LED_1, RGB_WHITE);
                rgb_matrix_set_color(LED_2, RGB_GOLD);
                rgb_matrix_set_color(LED_3, RGB_SPRINGGREEN);
                rgb_matrix_set_color(LED_4, RGB_TEAL);
                rgb_matrix_set_color(LED_5, RGB_CYAN);
                rgb_matrix_set_color(LED_6, RGB_PURPLE);
                rgb_matrix_set_color(LED_7, RGB_MAGENTA);
                rgb_matrix_set_color(LED_8, RGB_PINK);
                rgb_matrix_set_color(LED_9, RGB_RED);
                rgb_matrix_set_color(LED_0, RGB_BLACK);

                // Light Function Key row based on current animation
                handle_current_animation_rgb();

                // Highlight some function keys
                rgb_matrix_set_color(LED_LEFT, RGB_RED);    // Shuffle animation reverse
                rgb_matrix_set_color(LED_UP, RGB_WHITE);    // Increase brightness
                rgb_matrix_set_color(LED_RIGHT, RGB_RED);   // Shuffle animation forward
                rgb_matrix_set_color(LED_DOWN, RGB_WHITE);  // Decrease brightness
                break;
            default:
                break;
        }
    }

    // Suspend RGB when PC is powered OFF
    void suspend_power_down_user(void) {
        rgb_matrix_set_suspend_state(true);
    }

    // Enable RGB when PC is powered ON
    void suspend_wakeup_init_user(void) {
        rgb_matrix_set_suspend_state(false);
    }
#endif

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
      tap_code(KC_VOLU);
    } else {
      tap_code(KC_VOLD);
    }
    return true;
}

void keyboard_post_init_user(void) {
    timeout_timer = timer_read(); // set inital time for ide timeout

    // Debug Settings
    // debug_enable=true;
    // debug_matrix=true;
}
