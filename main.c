#include "include/driver.h"
#include "include/Display.h"

#define F_CPU 20000000L

void InitUART(int baudrate)
{
    uint16_t baud = (F_CPU / (16UL * baudrate)) - 1;
    AVR_Init_UART(baud);
}

int main(void)
{
    AVR_Init();
    InitUART(9600);
    print("Hello World!\n");
    DrawPixel(10, 10, 255, 0, 0);
    for (uint16_t i = 0; i < 256; i++)
    {
        for (uint8_t j = 0; j < 128; j++)
        {
            DrawPixel(i, j, 255, 255, 255);
        }
    }

    SwapBuffer();
    SwapBuffer();
    print("Done!\n");

    while (1)
    {
    }
    return 0;
}