#include "include/driver.h"
#include "include/Display.h"
#include "RayTracing.h"

#define F_CPU 20000000L

void InitUART(int baudrate)
{
    uint16_t baud = (F_CPU / (16UL * baudrate)) - 1;
    AVR_Init_UART(baud);
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

void etalonateScreen()
{
    uint8_t r = 0;
    for (uint8_t i = 0; i < 9; i++)
    {
        outputAll(255, 255, r);
        print("step ");
        print(r);
        print("\n");
        SwapBuffer();
        AVR_Delay();
        r |= 1 << i;
    }
    
    
}

int main(void)
{
    AVR_Init();
    InitUART(9600);
/*
    print("Hello World!\n");
    DrawPixel(10, 10, 255, 0, 0);
    for (uint16_t i = 0; i < 256; i++)
    {
        for (uint8_t j = 0; j < 128; j++)
        {
            DrawPixel(i, j, 255, 255, 255);
        }
    }
    DrawPixel(10, 10, 0, 255, 0);

    SwapBuffer();

    AVR_Delay();
    */
   /*
    for (uint16_t i = 0; i < 256; i++)
    {
        for (uint8_t j = 0; j < 128; j++)
        {
            DrawPixel(i, j, 255, 255, 255);
        }
    }*/
/*
    for (uint16_t i = 0; i < 256; i++)
    {
        for (uint8_t j = 0; j < 128; j++)
        {
            DrawPixel(i, j, 255, 255, 255);
        }
    }
*/

    outputAll(255, 255, 255);
    SwapBuffer();
    outputAll(255, 255, 255);
    SwapBuffer();
    RayMain();
    //etalonateScreen();
    //SwapBuffer();


    print("Done!\n");

    while (1)
    {
    }
    return 0;
}