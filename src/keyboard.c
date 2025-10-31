#include "keyboard.h"
#include "helper.h"
uint8_t HOLD_SHIFT = 0x0;
uint8_t read_code()
{
  uint8_t scan_code = 0;
  while (1)
  {
    while (!inb(KBD_STAUS_PORT_I8042_PS) & 1)
      ;

    scan_code = inb(KBD_DATA_PORT_I8042_PS);
    if (!(scan_code & 0x80))
    {
      if (scan_code == KBD_RIGHT_SHIFT_PS || scan_code == KBD_LEFT_SHIFT_PS)
      {
        HOLD_SHIFT = 1;
      }
      else
      {
        return scan_code;
      }
    }
    else
    {
      if (scan_code == KBD_LEFT_SHIFT_RELEASE_PS || scan_code == KBD_RIGHT_SHIFT_RELEASE_PS)
      {
        HOLD_SHIFT = 0;
      }
    }
  }
}
void wait_for_key_release(uint8_t press_scan_code)
{
  uint8_t release_scan_code = press_scan_code | 0x80;
  uint8_t sc;

  while (1)
  {
    while (!inb(KBD_STAUS_PORT_I8042_PS) & 1)
      ;
    sc = inb(KBD_DATA_PORT_I8042_PS);

    if (sc == KBD_LEFT_SHIFT_RELEASE_PS || sc == KBD_RIGHT_SHIFT_RELEASE_PS)
    {
      HOLD_SHIFT = 0;
    }
    else if (sc == KBD_RIGHT_SHIFT_PS || sc == KBD_LEFT_SHIFT_PS)
    {
      HOLD_SHIFT = 1;
    }
    if (sc == release_scan_code)
    {
      return;
    }

  }
}
uint8_t default_keymap[128] = {
    0,                           // 0x00 Null
    27,                          // 0x01 Escape
    '1',                         // 0x02
    '2',                         // 0x03
    '3',                         // 0x04
    '4',                         // 0x05
    '5',                         // 0x06
    '6',                         // 0x07
    '7',                         // 0x08
    '8',                         // 0x09
    '9',                         // 0x0A
    '0',                         // 0x0B
    '-',                         // 0x0C
    '=',                         // 0x0D
    '\b',                        // 0x0E Backspace
    '\t',                        // 0x0F Tab
    'q',                         // 0x10
    'w',                         // 0x11
    'e',                         // 0x12
    'r',                         // 0x13
    't',                         // 0x14
    'y',                         // 0x15
    'u',                         // 0x16
    'i',                         // 0x17
    'o',                         // 0x18
    'p',                         // 0x19
    '[',                         // 0x1A
    ']',                         // 0x1B
    '\n',                        // 0x1C Enter
    0,                           // 0x1D Left Ctrl
    'a',                         // 0x1E
    's',                         // 0x1F
    'd',                         // 0x20
    'f',                         // 0x21
    'g',                         // 0x22
    'h',                         // 0x23
    'j',                         // 0x24
    'k',                         // 0x25
    'l',                         // 0x26
    ';',                         // 0x27
    '\'',                        // 0x28
    '`',                         // 0x29
    0,                           // 0x2A Left Shift
    '\\',                        // 0x2B
    'z',                         // 0x2C
    'x',                         // 0x2D
    'c',                         // 0x2E
    'v',                         // 0x2F
    'b',                         // 0x30
    'n',                         // 0x31
    'm',                         // 0x32
    ',',                         // 0x33
    '.',                         // 0x34
    '/',                         // 0x35
    0,                           // 0x36 Right Shift
    '*',                         // 0x37 Keypad *
    0,                           // 0x38 Left Alt
    ' ',                         // 0x39 Space
    0,                           // 0x3A CapsLock
    0,                           // 0x3B F1
    0,                           // 0x3C F2
    0,                           // 0x3D F3
    0,                           // 0x3E F4
    0,                           // 0x3F F5
    0,                           // 0x40 F6
    0,                           // 0x41 F7
    0,                           // 0x42 F8
    0,                           // 0x43 F9
    0,                           // 0x44 F10
    0,                           // 0x45 NumLock
    0,                           // 0x46 ScrollLock
    '7',                         // 0x47 Keypad 7
    '8',                         // 0x48 Keypad 8
    '9',                         // 0x49 Keypad 9
    '-',                         // 0x4A Keypad -
    '4',                         // 0x4B Keypad 4
    '5',                         // 0x4C Keypad 5
    '6',                         // 0x4D Keypad 6
    '+',                         // 0x4E Keypad +
    '1',                         // 0x4F Keypad 1
    '2',                         // 0x50 Keypad 2
    '3',                         // 0x51 Keypad 3
    '0',                         // 0x52 Keypad 0
    '.',                         // 0x53 Keypad .
    0,                           // 0x54 <unused>
    0,                           // 0x55 <unused>
    0,                           // 0x56 <unused>
    0,                           // 0x57 F11
    0,                           // 0x58 F12
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0 // 0x59-0x63 padding
};
