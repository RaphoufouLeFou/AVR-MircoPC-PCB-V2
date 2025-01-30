// Made by : Raphael Clerault

#include "include/AvrLib.h"
#include "RayTracing.h"
#include "include/driver.h"
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
extern void RayMainAsm(void);
#ifdef __cplusplus
}
#endif // __cplusplus


int main(void)
{
    Init();
    //LaunchProgram(0, 0, RayMain);
    const char str[] = "Yoooo Arthur\nC'est l'AVR-MicroPC!!\n";
    print(str);
    DrawString(str, 128 - 12/2 * 5, 60, 255, 255, 255, CLIP_TO_RECT);
    SwapBuffer();
    DrawString(str, 128 - 12/2 * 5, 60, 255, 255, 255, CLIP_TO_RECT);
    SwapBuffer();
    RayMainAsm();
    //AVR_Output_Pixel(0xFFFFFFFF, 10, 10);
    SwapBuffer();
    //LaunchProgram(0, 0, RayMainAsm);
    //DrawChar('D', 0, 0, 255, 255, 255);
    print("Done!\n");
    
    while (1);
    return 0;
}