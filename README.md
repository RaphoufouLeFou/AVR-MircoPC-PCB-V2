# AVR-MicroPC C/C++ documentation

## Introduction
This is the documentation for the AVR-MicroPC C library. This library is designed to make it easier to program the AVR-MicroPC in C/C++. The library is designed to be easy to use and understand, while still providing a lot of functionality.

## Getting started
To get started with the library, you will need to include the `include/AvrLib.h` header file in your project. This file contains all of the necessary definitions and functions to use the library.
The Main function NEED to be structured as follows:
```c
int main(void)
{
    Init();

    // Your code here

    while (1)
    {
        // Other code here
    }

    return 0; // Never reached but needed to compile
}
```

## Display

The AVR-MicroPC output a VGA signal with a resolution of 256x128 pixels in 4:3 format. The display is controlled by the `Display.h` header file. This file contains all of the necessary definitions and functions to control the display, and is included in the `AvrLib.h` header file.

### Functions

```c
void DrawPixel(uint8_t x, uint8_t y, uint8_t R, uint8_t G, uint8_t B);
```
This function draws a pixel at the specified coordinates with the specified color. The `x` and `y` parameters specify the coordinates of the pixel, and the `R`, `G`, and `B` parameters specify the color of the pixel. R, G, and B should be in the range 0-255.

```c
void outputAll(uint8_t R, uint8_t G, uint8_t B);
```
This function sets the color of all pixels on the display to the specified color. The `R`, `G`, and `B` parameters specify the color of the pixels. R, G, and B should be in the range 0-255. It is recommended to use this function to clear the display before drawing new pixels.

```c
void SwapBuffer(void);
```
This function swaps the display buffer. This function should be called after drawing all of the pixels on the display to update the display with the new pixel data.

```c
void ClearAllBuffers(void);
```
This function clears all of the display buffers. This function can be used to clear the display before drawing new pixels.

```c
void DrawChar(char c, uint8_t x, uint8_t y, uint8_t R, uint8_t G, uint8_t B);
```
This function draws a character at the specified coordinates with the specified color. The `c` parameter specifies the character to draw, the `x` and `y` parameters specify the coordinates of the character, and the `R`, `G`, and `B` parameters specify the color of the character. R, G, and B should be in the range 0-255.

```c
void DrawString(const char *str, uint8_t x, uint8_t y, uint8_t R, uint8_t G, uint8_t B, DrawCharMode_t mode);
```
This function draws a string at the specified coordinates with the specified color. The `str` parameter specifies the string to draw, the `x` and `y` parameters specify the coordinates of the string, and the `R`, `G`, and `B` parameters specify the color of the string. R, G, and B should be in the range 0-255. The `mode` parameter specifies the mode in which to draw the characters. The `mode` parameter should be one of the following values:
- `NO_CLIP` - In case of overflow, the characters will be drawn outside the screen.
- `CLIP_TO_START` - In case of overflow, the characters will be drawn from the start of the screen.
- `CLIP_TO_RECT` - In case of overflow, the characters will be drawn at the same `x` position, but the `y` position will be incremented.
A newline character (`\n`) will move the `y` position to the next line.

## IO
The AVR-MicroPC has 16 digital IO pins that can be used as inputs or outputs. The IO pins are controlled by the `IO.h` header file. This file contains all of the necessary definitions and functions to control the IO pins, and serial comunication, and is included in the `AvrLib.h` header file.

### Functions

```c
void print(const char *str);
```
This function sends a string over the UART0 port. The `str` parameter specifies the string to send.

```c
void printInt(int i);
```
This function sends an integer over the UART0 port. The `i` parameter specifies the integer to send.

## OS

The AVR-MicroPC has a simple operating system that can be used to run one task at a time. The operating system is controlled by the `OS.h` header file. This file contains all of the necessary definitions and functions to control the operating system, and is included in the `AvrLib.h` header file.

### Functions

```c
int LaunchProgram(int argc, char **argv, int (*program)(int, char **));
```
This function launches a new program in a new task. The `argc` parameter specifies the number of arguments, the `argv` parameter specifies the arguments, and the `program` parameter specifies the program to run. The program should be a function that takes an integer and a pointer to a string array as arguments, and returns the exit code of the program.
FOR NOW, AS ONLY ONE TASK CAN BE RUN AT A TIME, THIS FUNCTION WILL NEVER RETURN.

## Examples

### RayTracing

This example demonstrates how to use the display functions to draw a simple ray-traced scene. The example draws a sphere, a cube, and a plane, and uses ray tracing to calculate the color of each pixel on the display.
The scene takes around 38 minutes to render, so be patient.
```c
#include "AvrLib.h"
#include "RayTracing.h"

int main(void)
{
    Init();
    LaunchProgram(0, 0, RayMain);
    return 0;
}
```

## Compiling

To compile your program, just run the following command:
```bash
make
```
This will compile your program and automatically upload it to the AVR-MicroPC, if it is connected.