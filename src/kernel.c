#include "screen.h"
#include "keyboard.h"
#include "types.h"
void kmain()
{
  init_screen();
  const uint8_t *hello = "Hello,\n";
  write_screen(SCREEN_GREEN, SCREEN_BLACK, hello);
  for (;;)
  {
    uint8_t scan_code = read_code();

    
    uint8_t c = default_keymap[scan_code];
    // HOLD_SHIFT is define in keyboard.c
    // We set hold shift when the keyboard recieve
    // LSHIfT and RSHIFT is press
    // It become 0 when LSHIFT and RSHIFT is release
    if (HOLD_SHIFT == 1)
    {
      c -= 0x20;
    }
    uint8_t buf[2] = {c, 0};
    write_screen(SCREEN_RED, SCREEN_BLACK, buf);
    wait_for_key_release(scan_code);
  }
  for (;;)
  {
   
  }
}