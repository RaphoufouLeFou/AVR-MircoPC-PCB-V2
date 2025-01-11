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
    for (uint16_t i = 0; i < 256; i++)
    {
        for (uint8_t j = 0; j < 128; j++)
        {
            DrawPixel(i, j, r, g, b);
        }
    }
}
