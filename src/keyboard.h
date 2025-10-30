#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "types.h"
#define KBD_DATA_PORT_I8042_PS 0x60
#define KBD_STAUS_PORT_I8042_PS 0x64
uint8_t read_code();
extern uint8_t default_keymap[];
#endif