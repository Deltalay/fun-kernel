#ifndef SCREEN_H
#define SCREEN_H

// (Your color definitions are here)
#define SCREEN_BLACK 0x00
#define SCREEN_BLUE 0x01
#define SCREEN_GREEN 0x02
#define SCREEN_CYAN 0x03
#define SCREEN_RED 0x04
#define SCREEN_PURPLE 0x05
#define SCREEN_BROWN 0x06
#define SCREEN_GRAY 0x07
#define SCREEN_DARK_GRAY 0x08
#define SCREEN_LIGHT_BLUE 0x09
#define SCREEN_LIGHT_GREEN 0x0A
#define SCREEN_LIGHT_CYAN 0x0B
#define SCREEN_LIGHT_RED 0x0C
#define SCREEN_LIGHT_PURPLE 0x0D
#define SCREEN_YELLOW 0x0E
#define SCREEN_WHITE 0x0F

void init_screen(void);
void write_screen(int fg, int bg, const char *string);

#endif