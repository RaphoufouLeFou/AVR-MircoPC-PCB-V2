#include "include/Display.h"
#include "include/driver.h"

void print(const char *str)
{
    while (*str)
    {
        AVR_Send_UART(*str);
        str++;
    }
}


void SwapBuffer(void)
{
    static uint8_t bufferID = 0xFF;
    AVR_Swap_Buffer(bufferID);
    print("buffer set to ");
    print(bufferID ? "1\n" : "0\n");
    bufferID = !bufferID ? 0xFF : 0;
}

void DrawPixel(uint8_t x, uint8_t y, uint8_t R, uint8_t G, uint8_t B)
{
    uint16_t color = ((B >> 3) << 11) | ((G >> 2) << 5) | (R >> 3);
    AVR_Output_Pixel(color, x, y);
}