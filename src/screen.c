#include "screen.h"

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define VIDEO_MEMORY 0xB8000

volatile char *vga_buffer = (volatile char *)VIDEO_MEMORY;
int cursor_x = 0;
int cursor_y = 0;

static void scroll_screen()
{
  int i;
  for (i = 0; i < (SCREEN_HEIGHT - 1) * SCREEN_WIDTH * 2; i++)
  {
    vga_buffer[i] = vga_buffer[i + (SCREEN_WIDTH * 2)];
  }

  for (i = (SCREEN_HEIGHT - 1) * SCREEN_WIDTH * 2; i < SCREEN_HEIGHT * SCREEN_WIDTH * 2; i += 2)
  {
    vga_buffer[i] = ' ';
    vga_buffer[i + 1] = 0x0F;
  }

  cursor_y = SCREEN_HEIGHT - 1;
  cursor_x = 0;
}

static void put_char(char c, int fg, int bg)
{
  unsigned char attr = ((bg & 0x0F) << 4) | (fg & 0x0F);

  if (c == '\n')
  {
    cursor_x = 0;
    cursor_y++;
  }

  else
  {
    int offset = (cursor_y * SCREEN_WIDTH + cursor_x) * 2;
    vga_buffer[offset] = c;
    vga_buffer[offset + 1] = attr;
    cursor_x++;
  }

  if (cursor_x >= SCREEN_WIDTH)
  {
    cursor_x = 0;
    cursor_y++;
  }

  if (cursor_y >= SCREEN_HEIGHT)
  {
    scroll_screen();
  }
}

void init_screen()
{
  int i;
  for (i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
  {
    vga_buffer[i * 2] = ' ';
    vga_buffer[i * 2 + 1] = 0x0F;
  }
  cursor_x = 0;
  cursor_y = 0;
}

void write_screen(int fg, int bg, const uint8_t *string)
{
  for (const char *s = string; *s; s++)
  {
    put_char(*s, fg, bg);
  }
}