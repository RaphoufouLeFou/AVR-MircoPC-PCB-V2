#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <stdint.h>

void print(const char *str);
void SwapBuffer();
void DrawPixel(uint8_t x, uint8_t y, uint8_t R, uint8_t G, uint8_t B);

#endif // _DISPLAY_H_