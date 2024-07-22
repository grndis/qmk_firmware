#include QMK_KEYBOARD_H

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

uint16_t td_esc_lctrl_timer = 0;
bool is_td_esc_lctrl_held = false;

enum custom_keycodes {
  ALT_TAB = QK_KB_0,
  TD_ESC_LCTRL,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
		[0] = LAYOUT_65_ansi_blocker(
			KC_GRAVE, KC_1,     KC_2,     KC_3,  KC_4,  KC_5,  KC_6,    KC_7,  KC_8,    KC_9,     KC_0,     KC_MINS,  KC_EQL,  KC_BSPC,   QK_GESC,\
		    KC_TAB,  KC_Q,     KC_W,     KC_E,  KC_R,  KC_T,  KC_Y,    KC_U,  KC_I,    KC_O,     KC_P,     KC_LBRC,  KC_RBRC, KC_BSLS, KC_PGUP,\
			KC_CAPS, KC_A,     KC_S,     KC_D,  KC_F,  KC_G,  KC_H,    KC_J,  KC_K,    KC_L,     KC_SCLN,  KC_QUOT,           KC_ENT,    KC_PGDN,\
		    KC_LSFT, KC_Z,     KC_X,     KC_C,  KC_V,  KC_B,  KC_N,    KC_M,  KC_COMM, KC_DOT,   KC_SLSH,  KC_RSFT,           KC_UP,     MO(1),\
		    KC_LCTL, KC_LALT,  KC_LGUI,                KC_SPC,                KC_RGUI,           MO(1),    KC_LEFT,           KC_DOWN,   KC_RIGHT),
		[1] = LAYOUT_65_ansi_blocker(
			QK_GESC,       KC_F1,    KC_F2,   KC_F3,  KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12,  KC_DEL,   KC_HOME,\
		    ALT_TAB,       RGB_TOG,  RGB_MOD, RGB_HUI,RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_TRNS, KC_PSCR, KC_SCRL,  KC_PAUS, QK_BOOT,    KC_PGUP,\
			KC_TRNS,       RGB_SPI,  RGB_SPD, KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,          EE_CLR,  KC_PGDN,\
		    KC_LSFT,       KC_TRNS,  KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,          KC_VOLU,  KC_MUTE,\
		    KC_TRNS,       KC_TRNS,  KC_TRNS,                  KC_TRNS,                   KC_TRNS,          KC_TRNS,  KC_MPRV,          KC_VOLD,  KC_MNXT),
		[2] = LAYOUT_65_ansi_blocker(
			KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,\
		    KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,\
			KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,  KC_TRNS,\
		    KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,  KC_TRNS,\
		    KC_TRNS,  KC_TRNS,  KC_TRNS,                     KC_TRNS,                   KC_TRNS,          KC_TRNS, KC_TRNS,          KC_TRNS,  KC_TRNS),
		[3] = LAYOUT_65_ansi_blocker(
			KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,\
		    KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,\
			KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,  KC_TRNS,\
		    KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,  KC_TRNS,\
		    KC_TRNS,  KC_TRNS,  KC_TRNS,                     KC_TRNS,                   KC_TRNS,          KC_TRNS, KC_TRNS,          KC_TRNS,  KC_TRNS),
};



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint16_t td_esc_lctrl_timer;
    static bool is_td_esc_lctrl_held = false;

    switch (keycode) {
        case ALT_TAB:
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;

        case TD_ESC_LCTRL:
            if (record->event.pressed) {
                td_esc_lctrl_timer = timer_read();
                is_td_esc_lctrl_held = true;
            } else {
                if (is_td_esc_lctrl_held) {
                    if (timer_elapsed(td_esc_lctrl_timer) < TAPPING_TERM) {
                        tap_code(KC_ESC);
                    }
                    is_td_esc_lctrl_held = false;
                }
                unregister_code(KC_LCTL);
            }
            return false;

        default:
            if (is_td_esc_lctrl_held && timer_elapsed(td_esc_lctrl_timer) >= TAPPING_TERM) {
                register_code(KC_LCTL);
            }
            break;

    }
    return true;
}

void matrix_scan_user(void) { // The very important timer.
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 1000) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
    if (is_td_esc_lctrl_held && timer_elapsed(td_esc_lctrl_timer) >= TAPPING_TERM * 2) {
        is_td_esc_lctrl_held = false;
        tap_code(KC_ESC);
    }
}
