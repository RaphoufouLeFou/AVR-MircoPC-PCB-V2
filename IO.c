#include "include/IO.h"

#include <stdlib.h>

void print(const char *str)
{
    while (*str)
    {
        AVR_Send_UART(*str);
        str++;
    }
}

void printInt(int i)
{
    char buffer[10];
    itoa(i, buffer, 10);
    print(buffer);
}

