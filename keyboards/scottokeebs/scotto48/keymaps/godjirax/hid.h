#pragma once

#include QMK_KEYBOARD_H

void send_event_to_hid(uint16_t keycode, keyevent_t event);
