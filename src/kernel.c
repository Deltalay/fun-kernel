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

    // User hasn't release shfit
    const uint8_t *c = default_keymap[scan_code];

    if (HOLD_SHIFT == 1)
    {
      c -= 0x20;
    }

    write_screen(SCREEN_RED, SCREEN_BLACK, &c);
    write_screen(SCREEN_RED, SCREEN_BLACK, " ");
  }
  for (;;)
  {
   
  }
}