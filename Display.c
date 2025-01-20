// Made by : Raphael Clerault

#include "include/Display.h"
#include "include/driver.h"

#include <stdlib.h>

void SwapBuffer(void)
{
    static uint8_t bufferID = 0xFF;
    AVR_Swap_Buffer(bufferID);
    bufferID = !bufferID ? 0xFF : 0;
}

void DrawPixel(uint8_t x, uint8_t y, uint8_t R, uint8_t G, uint8_t B)
{
    uint16_t color = ((R >> 3) << 11) | ((G >> 2) << 5) | (B >> 3);
    AVR_Output_Pixel(color, x, y);
}

void outputAll(uint8_t r, uint8_t g, uint8_t b)
{
    // TODO : change to AVR_Output_All
    // AVR_Output_All(((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3));
    for (uint16_t i = 0; i < 256; i++)
    {
        for (uint8_t j = 0; j < 128; j++)
        {
            DrawPixel(i, j, r, g, b);
        }
    }
}

void ClearAllBuffers(void)
{
    outputAll(0, 0, 0);
    SwapBuffer();
    outputAll(0, 0, 0);
    SwapBuffer();
}

void DrawChar(char c, uint8_t x, uint8_t y, uint8_t R, uint8_t G, uint8_t B)
{
    for (uint8_t i = 0; i < 5; i++)
    {
        for (uint8_t j = 0; j < 8; j++)
        {
            if (font[c][i] & (1 << 7 - j))
            {
                DrawPixel(x + i, y + j, R, G, B);
            }
        }
    }
}

void DrawString(const char *str, uint8_t x, uint8_t y, uint8_t R, uint8_t G, uint8_t B, DrawCharMode_t mode)
{
    uint8_t currentX = x;
    while (*str)
    {
        if(*str == '\n')
        {
            y += 9;
            currentX = x;
            str++;
            continue;
        }
        if(y >= 128 - 8)
            return;
        DrawChar(*str, currentX, y, R, G, B);
        currentX += 6;
        if(currentX >= 256 - 5 && mode != NO_CLIP)
        {
            currentX = mode == CLIP_TO_START ? 1 : x;
            y += 9;
        }
        if(y >= 128 - 8)
            return;
        if(currentX >= 256 && mode == NO_CLIP)
            return;
        str++;
    }
}