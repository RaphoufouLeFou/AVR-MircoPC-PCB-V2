// Made by : Raphael Clerault

#include "include/Display.h"
#include "include/driver.h"
#include "include/AvrLib.h"

#define F_CPU 20000000L

void InitUART(int baudrate)
{
    uint16_t baud = (F_CPU / (16UL * baudrate)) - 1;
    AVR_Init_UART(baud);
}

void Init(void)
{
    AVR_Init();
    InitUART(9600);
    ClearAllBuffers();
}