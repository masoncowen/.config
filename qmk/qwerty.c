/* Copyright 2021 masoncowen
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


enum planck_layers {
  _ALPHA,
  _NUMNAV
};

enum custom_keycodes {
  CC_RPEAT = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_ALPHA] = LAYOUT_planck_grid(
  KC_Q , KC_W , KC_E , KC_R , KC_T , KC_NO , KC_NO , KC_Y , KC_U , KC_I , KC_O , KC_P ,
  KC_A , KC_S , KC_D , KC_F , KC_G , KC_NO , KC_NO , KC_H , KC_J , KC_K , KC_L , KC_SCLN ,
  KC_Z , KC_X , KC_C , KC_V , KC_B , KC_NO , KC_NO , KC_N , KC_M , KC_COMM , KC_DOT , KC_BSLS ,
  KC_NO , KC_NO , KC_NO , KC_SPC , OSM(MOD_LCTL) , KC_NO , KC_NO , OSL(_NUMNAV) , OSM(MOD_LSFT) , KC_NO , KC_NO , KC_NO
),

//TRANSPARENT keys are to be decided on
[_NUMNAV] = LAYOUT_planck_grid(
  KC_PPLS , KC_4 , KC_5 , KC_6 , KC_PAST , KC_NO , KC_NO , KC_QUOT , KC_HOME , KC_PGDN , KC_PGUP , KC_END ,
  KC_0    , KC_1 , KC_2 , KC_3 , KC_PENT , KC_NO , KC_NO , KC_BSLS , KC_LEFT , KC_DOWN , KC_UP , KC_RIGHT ,
  KC_PMNS , KC_7 , KC_8 , KC_9 , KC_PSLS , KC_NO , KC_NO , KC_NUHS , _______ , _______ , _______ , _______ ,
  KC_NO   , KC_NO , KC_NO , KC_DEL , OSM(MOD_LCTL) , KC_NO , KC_NO , KC_BSPC , OSM(MOD_LSFT) , KC_NO , KC_NO , KC_NO
)
};

const key_override_t enter_key_override = ko_make_basic(MOD_MASK_SHIFT | MOD_MASK_CTRL, KC_SPC, KC_ENT);
const key_override_t esc_key_override = ko_make_basic(MOD_MASK_CTRL, KC_SPC, KC_ESC);
const key_override_t tab_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_SPC, KC_TAB);

const key_override_t **key_overrides = (const key_override_t *[]){
  &enter_key_override,
  &esc_key_override,
  &tab_key_override,
  NULL
};

#define GET_TAP_KC(dual_role_key) dual_role_key & 0xFF
uint16_t last_keycode = KC_NO;
uint8_t last_modifier = 0;
uint8_t mod_state;
uint8_t oneshot_mod_state;

void process_repeat_key(uint16_t keycode, const keyrecord_t *record) {
	if (keycode != CC_RPEAT) {
		switch (keycode){
			case QK_DEF_LAYER ... QK_DEF_LAYER_MAX:
			case QK_MOMENTARY ... QK_MOMENTARY_MAX:
			case QK_LAYER_MOD ... QK_LAYER_MOD_MAX:
			case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
			case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
			case QK_TO ... QK_TO_MAX:
			case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
				return;
		}
		last_modifier = oneshot_mod_state > mod_state ? oneshot_mod_state : mod_state;
		switch (keycode) {
			case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
			case QK_MOD_TAP ... QK_MOD_TAP_MAX:
				if (record->event.pressed) {
					last_keycode = GET_TAP_KC(keycode);
				}
				break;
			default:
				if (record->event.pressed) {
					last_keycode = keycode;
				}
				break;
		}
	} else {
		if (record->event.pressed) {
			register_mods(last_modifier);
			register_code16(last_keycode);
		} else {
			unregister_code16(last_keycode);
			unregister_mods(last_modifier);
		}
	}
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	process_repeat_key(keycode, record);
	mod_state = get_mods();
	oneshot_mod_state = get_oneshot_mods();
	return true;
};
