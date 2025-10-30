#ifndef KEYBOARD_H
#define KEYBOARD_H

#define KBD_DATA_PORT_I8042_PS 0x60
#define KBD_STAUS_PORT_I8042_PS 0x64
unsigned char read_code();
extern unsigned char default_keymap[];
#endif