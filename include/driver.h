// Made by : Raphael Clerault

#ifndef _DRIVER_H_
#define _DRIVER_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/// @brief Initialize the IO pins 
extern void AVR_Init(void);

/// @brief Output a pixel to the screen at the given address with the given color
/// @param Color 16-bit color value (5 bits blue, 6 bits green, 5 bits red)
/// @param AddressX X coordinate of the pixel (0-255)
/// @param AddressY Y coordinate of the pixel (0-127)
extern void AVR_Output_Pixel(uint16_t Color, uint8_t AddressX, uint8_t AddressY);

/// @brief Fill the screen with the given color
/// @param Color 16-bit color value (5 bits blue, 6 bits green, 5 bits red)
extern void AVR_Output_All(uint16_t Color);

/// @brief Set the active memory to the screen and the screen to the active memory
extern void AVR_Swap_Buffer(uint8_t bufferID);

/// @brief Read the input pins and return the value
/// @return input value from PORTB
extern uint8_t AVR_Read_Inputs(void);

/// @brief Write the output pins
/// @param value input value for PORTB
extern void AVR_Write_Outputs(uint8_t value);

/// @brief Initialize the UART at 9600 baud
extern void AVR_Init_UART(uint8_t baud);

/// @brief Send a byte over UART
/// @param data byte to send
extern void AVR_Send_UART(uint8_t data);

/// @brief Receive a byte over UART
/// @return received byte
extern uint8_t AVR_Receive_UART(void);

/// @brief Receive a string over UART
/// @param buffer buffer to store the received string
extern void AVR_Receive_UART_String(uint8_t *buffer);

/// @brief Delay for 1 second
extern void AVR_Delay(void);

/// @brief Delay for 10ms
extern void AVR_Delay_10ms(void);

/// @brief Read the EEPROM at the given address
/// @param adress address to read from (0-4096)
/// @return data at the given address
extern uint8_t AVR_Read_Rom(uint16_t adress);

/// @brief Write the EEPROM at the given address
/// @param adress address to write to (0-4096)
/// @param data data to write to the given address
extern void AVR_Write_Rom(uint16_t adress, uint8_t data);
extern uint16_t AVR_DEBUG(void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _DRIVER_H_