/* Copyright 2022 masoncowen
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
  _BETA,
  _GAMMA
};

enum custom_keycodes {
  CC_RPEAT = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_ALPHA] = LAYOUT_planck_grid(
  KC_NO  , KC_G  , KC_L   , KC_P        , KC_NO , KC_NO , KC_NO , KC_NO , KC_M       , KC_U     , KC_Y  , KC_NO ,
  KC_A   , KC_S  , KC_R   , KC_T        , KC_NO , KC_NO , KC_NO , KC_NO , KC_N       , KC_E     , KC_I  , KC_O ,
  KC_W   , KC_F  , KC_SPC , KC_D        , KC_NO , KC_NO , KC_NO , KC_NO , KC_H       , CC_RPEAT , KC_C  , KC_K ,
  KC_NO  , KC_NO , KC_NO  , OSL(_GAMMA) , KC_NO , KC_NO , KC_NO , KC_NO , OSL(_BETA) , KC_NO    , KC_NO , KC_NO
),

[_BETA] = LAYOUT_planck_grid(
  KC_NO         , KC_NUHS       , KC_SCLN       , KC_COMM       , KC_NO , KC_NO , KC_NO , KC_NO , KC_DOT      , KC_QUOT , KC_GRV  , KC_NO ,
  OSM(MOD_LGUI) , OSM(MOD_LALT) , OSM(MOD_LCTL) , OSM(MOD_LSFT) , KC_NO , KC_NO , KC_NO , KC_NO , KC_B        , KC_J    , KC_Q    , KC_Z ,
  KC_MINS       , KC_LBRC       , KC_NUBS       , KC_X          , KC_NO , KC_NO , KC_NO , KC_NO , KC_V        , KC_SLSH , KC_RBRC , KC_EQL ,
  KC_NO         , KC_NO         , KC_NO         , OSL(_GAMMA)    , KC_NO , KC_NO , KC_NO , KC_NO , OSL(_BETA) , KC_NO   , KC_NO   , KC_NO
),

[_GAMMA] = LAYOUT_planck_grid(
  KC_NO  , KC_4  , KC_5  , KC_6        , KC_NO , KC_NO , KC_NO , KC_NO , KC_TAB     , KC_PGDN , KC_PGUP , KC_NO ,
  KC_0   , KC_1  , KC_2  , KC_3        , KC_NO , KC_NO , KC_NO , KC_NO , KC_LEFT    , KC_DOWN , KC_UP   , KC_RIGHT ,
  KC_ENT , KC_7  , KC_8  , KC_9        , KC_NO , KC_NO , KC_NO , KC_NO , KC_BSPC    , KC_ENT  , KC_ESC  , KC_DEL ,
  KC_NO  , KC_NO , KC_NO , OSL(_GAMMA) , KC_NO , KC_NO , KC_NO , KC_NO , OSL(_BETA) , KC_NO   , KC_NO   , KC_NO
)
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
