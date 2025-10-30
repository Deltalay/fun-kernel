#include "screen.h"
#include "keyboard.h"
void kmain()
{
  init_screen();
  const char *hello = "Hello,\n";
  write_screen(SCREEN_GREEN, SCREEN_BLACK, hello);
  const char *prof = "Hello, CHIPBONG";
  write_screen(SCREEN_RED, SCREEN_BLACK, prof);

  for (;;)
  {
    unsigned char scan_code = read_code();
    const char *c = default_keymap[scan_code];
    
    write_screen(SCREEN_RED, SCREEN_BLACK, &c);
    write_screen(SCREEN_RED, SCREEN_BLACK, " ");
  }
}