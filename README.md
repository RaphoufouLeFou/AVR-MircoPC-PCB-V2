# AVR-MicroPC C/C++ documentation

## Introduction
This is the documentation for the AVR-MicroPC C library. This library is designed to make it easier to program the AVR-MicroPC in C/C++. The library is designed to be easy to use and understand, while still providing a lot of functionality.

## Getting started
To get started with the library, you will need to include the `include/AvrLib.h` header file in your project. This file contains all of the necessary definitions and functions to use the library.

## Display

The AVR-MicroPC output a VGA signal with a resolution of 256x128 pixels. The display is controlled by the `Display.h` header file. This file contains all of the necessary definitions and functions to control the display, and is included in the `AvrLib.h` header file.

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

## IO
The AVR-MicroPC has 16 digital IO pins that can be used as inputs or outputs. The IO pins are controlled by the `IO.h` header file. This file contains all of the necessary definitions and functions to control the IO pins, and serial comunication, and is included in the `AvrLib.h` header file.

### Functions

TODO