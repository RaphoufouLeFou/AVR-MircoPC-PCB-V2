// Made by : Raphael Clerault

#include "include/AvrLib.h"
#include "RayTracing.h"

int main(void)
{
    Init();
    //LaunchProgram(0, 0, RayMain);
    const char str[] = "Yoooo Arthur\nC'est l'AVR-MicroPC!!";
    print(str);
    DrawString(str, 128 - 12/2 * 5, 60, 255, 255, 255, CLIP_TO_RECT);
    SwapBuffer();
    DrawString(str, 128 - 12/2 * 5, 60, 255, 255, 255, CLIP_TO_RECT);
    SwapBuffer();
    LaunchProgram(0, 0, RayMain);
    //DrawChar('D', 0, 0, 255, 255, 255);
    print("Done!\n");
    
    while (1);
    return 0;
}