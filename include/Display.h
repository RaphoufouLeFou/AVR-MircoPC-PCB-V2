// Made by : Raphael Clerault

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <stdint.h>
#include "Fonts.h"

typedef enum
{
    NO_CLIP,
    CLIP_TO_START,
    CLIP_TO_RECT
} DrawCharMode_t;

void SwapBuffer(void);
void DrawPixel(uint8_t x, uint8_t y, uint8_t R, uint8_t G, uint8_t B);
void outputAll(uint8_t R, uint8_t G, uint8_t B);
void ClearAllBuffers(void);
void DrawChar(char c, uint8_t x, uint8_t y, uint8_t R, uint8_t G, uint8_t B);
void DrawString(const char *str, uint8_t x, uint8_t y, uint8_t R, uint8_t G, uint8_t B, DrawCharMode_t mode);

#endif // _DISPLAY_H_