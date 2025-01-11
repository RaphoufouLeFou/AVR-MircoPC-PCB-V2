#include "include/Display.h"
#include "include/driver.h"

#include <stdlib.h>

void print(const char *str)
{
    while (*str)
    {
        AVR_Send_UART(*str);
        str++;
    }
}

void print(int i)
{
    char buffer[10];
    itoa(i, buffer, 10);
    print(buffer);
}


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