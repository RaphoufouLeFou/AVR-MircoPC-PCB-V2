#include "driver.h"

int main()
{
    AVR_Init();
    AVR_Output_All(0x0000);
    AVR_Output_Pixel(0x001F, 0, 0);
    AVR_Output_Pixel(0x07E0, 1, 0);
    AVR_Output_Pixel(0xF800, 2, 0);
    AVR_Output_Pixel(0xFFFF, 3, 0);
    AVR_Swap_Buffer();
    while(1);
    return 0;
}