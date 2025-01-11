#include "include/driver.h"
#include "include/Display.h"
#include "include/IO.h"
#include "RayTracing.h"

int main(void)
{
    Init();
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