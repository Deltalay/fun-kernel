#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "types.h"
#define KBD_DATA_PORT_I8042_PS 0x60
#define KBD_STAUS_PORT_I8042_PS 0x64
#define KBD_LEFT_SHIFT_PS 0x2A
#define KBD_RIGHT_SHIFT_PS 0x36
#define KBD_LEFT_SHIFT_RELEASE_PS 0xAA
#define KBD_RIGHT_SHIFT_RELEASE_PS 0xB6
extern uint8_t HOLD_SHIFT;
uint8_t read_code();
void wait_for_key_release(uint8_t press_scan_code);

extern uint8_t default_keymap[];
#endif