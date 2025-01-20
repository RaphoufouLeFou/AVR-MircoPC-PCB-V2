; Made by : Raphael Clerault

#include <avr/io.h>

#define RG_PORT _SFR_IO_ADDR(PORTA)
#define RG_DDR _SFR_IO_ADDR(DDRA)
#define RG_PORT_DIR 0xFF

#define GB_PORT_MEM PORTF
#define GB_DDR_MEM DDRF
#define GB_PORT_DIR 0xFF

#define AX_PORT _SFR_IO_ADDR(PORTC)
#define AX_DDR _SFR_IO_ADDR(DDRC)
#define AX_PORT_DIR 0xFF

#define AY_PORT _SFR_IO_ADDR(PORTD)
#define AY_DDR _SFR_IO_ADDR(DDRD)
#define AY_PORT_DIR 0xFF

#define ACTIVE_PORT_MEM PORTG
#define ACTIVE_DDR_MEM DDRG
#define ACTIVE_PORT_DIR (1 << 4)

;***** AVR_Init *****
;	input:
;
;	Using :
;	r25

.global AVR_Init
AVR_Init:

	ldi		r25,		0xFF
	out		RG_DDR,		r25
	out		AX_DDR,		r25
	out		AY_DDR,		r25
	clr		XH
	ldi		XL,			GB_DDR_MEM
	st		X,			r25
	ldi		XL,			ACTIVE_DDR_MEM
	st		X,			r25
	clr 	r25
	ret

;***** AVR_Output_Pixel *****
;	input:
;	r25, DataH
;	r24, DataL
;	r22, AddressX
;	r20, AddressY

.global AVR_Output_Pixel
AVR_Output_Pixel:
	out		RG_PORT,	r25
	out		AX_PORT,	r22
	out		AY_PORT,	r20
	clr		XH
	ldi		XL,			GB_PORT_MEM
	st		X,			r24
	sbi		AY_PORT,	7
	cbi		AY_PORT,	7
	ret

;***** AVR_Output_All *****
;	input:
;	r25, DataH
;	r24, DataL
;	using: 
;	r23, r22
.global AVR_Output_All
	ldi		r23,		127
	ldi		r22,		255
AVR_Output_All:
	out		RG_PORT,	r25
	clr		XH
	ldi		XL,			GB_PORT_MEM
	st		X,			r24
	sbi		AY_PORT,	7
	cbi		AY_PORT,	7
	dec		r23
	brne	AVR_Output_All
	ldi		r23,		127
	dec		r22
	brne	AVR_Output_All
	ret

;***** AVR_Swap_Buffer *****
;	using:
;	r25

.global AVR_Swap_Buffer
AVR_Swap_Buffer:
	;lds		r25,		ActiveMemory
	;eor		r25,		ACTIVE_PORT_DIR
	;sts		ActiveMemory,	r25
	clr		XH
	ldi		XL,			ACTIVE_PORT_MEM
	st		X,			r24
	ret

;***** AVR_Read_Inputs *****
;	output:
;	r25, Inputs
;	using:
;	r24

.global AVR_Read_Inputs
AVR_Read_Inputs:
	ldi		r24,				0x00
	out		_SFR_IO_ADDR(DDRB),	r24
	in		r25,				_SFR_IO_ADDR(PINB)
	ret

;***** AVR_Write_Outputs *****
;	input:
;	r25, Outputs
;	using:
;	r24

.global AVR_Write_Outputs
AVR_Write_Outputs:
	ldi		r24,				0xFF
	out		_SFR_IO_ADDR(DDRB),	r24
	out		_SFR_IO_ADDR(PORTB),r25
	ret

;***** AVR_Init_UART *****
;	input:
;	r25, BaudrateH
;	r24, BaudrateL
;	Using :
;	r25

.global AVR_Init_UART
AVR_Init_UART:
	sts		UBRR0L,		r24
	sts		UBRR0H,		r25
	ldi		r24,		(1<<RXEN0)|(1<<TXEN0)
	sts		UCSR0B,		r24
	ldi		r24,		(1<<UCSZ00)|(1<<UCSZ01)
	sts		UCSR0C,		r24
	ret

;***** AVR_Send_UART *****
;	input:
;	r24, Data
;	Using :
;	r25

.global AVR_Send_UART
AVR_Send_UART:
	lds		r25,		UCSR0A
	sbrs	r25,		UDRE0
	rjmp	AVR_Send_UART
	sts	UDR0,			r24

	ret

;***** AVR_Receive_UART *****
;	input:
;	Using :
;	r24

.global AVR_Receive_UART
AVR_Receive_UART:	
	lds		r24,		UCSR0A
	sbrs	r24,		UDRE0
	rjmp	AVR_Receive_UART
	lds		r24,		UDR0
	ret


;***** AVR_Receive_UART_String *****
;	input:
;	r25, String address H
;	r24, String address L
;	Using :
;	r23

.global AVR_Receive_UART_String
AVR_Receive_UART_String:
	mov		XH,			r25
	mov		XL,			r24
AVR_Receive_UART_String_loop:
	lds		r25,		UCSR0A
	sbrs	r25,		UDRE0
	rjmp	AVR_Receive_UART_String_loop
	lds		r24,		UDR0
	cpi		r24,		0x0A
	breq	AVR_Receive_UART_String_end
	st		X+,			r24
	call	AVR_Send_UART
	rjmp	AVR_Receive_UART_String_loop
AVR_Receive_UART_String_end:
	ldi		r24,		0x0A
	call	AVR_Send_UART
	rjmp USART_Flush
	ret
USART_Flush:
	lds		r24,		UCSR0A
	sbrs	r24,		UDRE0
	ret
	in r24,				UDR0
	rjmp USART_Flush


;***** AVR_Delay_10ms *****
;	Using :
;	r23, r22, r26, r27

.global AVR_Delay_10ms
AVR_Delay_10ms:
	ldi		r26,		62
	ldi		r27,		156
iLoop2:	
	sbiw	r26,		1
	brne	iLoop2
	nop
	ret

;***** AVR_Delay *****
;	input:
;	Using :
;	r23

#define loopCt r24

.global AVR_Delay
AVR_Delay:
	ldi		r24,		0x7f
caca:
	ldi		r26,	62
	ldi		r27,	156

iLoop:	
	sbiw	r26,	1
	brne	iLoop
	dec		r24
	brne	caca
	nop
	ret

;***** AVR_Read_Rom *****
;	input:
;	r25, AddressH
;	r24, AddressL
;	Output :
;	r24, Data

.global AVR_Read_Rom
AVR_Read_Rom:

	sbic 	_SFR_IO_ADDR(EECR),	EEWE
	rjmp 	AVR_Read_Rom
	out 	_SFR_IO_ADDR(EEARH),r25
	out 	_SFR_IO_ADDR(EEARL),r24
	sbi 	_SFR_IO_ADDR(EECR),	EERE
	in 		r24,				_SFR_IO_ADDR(EEDR)
	ret

;***** AVR_Write_Rom *****
;	input:
;	r25, AddressH
;	r24, AddressL
;	r22, DataL
.global AVR_Write_Rom
AVR_Write_Rom:

	sbic	_SFR_IO_ADDR(EECR),	EEWE
	rjmp	AVR_Write_Rom
	out		_SFR_IO_ADDR(EEARH),r25
	out		_SFR_IO_ADDR(EEARL),r24
	out		_SFR_IO_ADDR(EEDR),	r22
	sbi		_SFR_IO_ADDR(EECR),	EEMWE
	sbi		_SFR_IO_ADDR(EECR),	EEWE
	ret

;***** AVR_DEBUG *****

.global AVR_DEBUG
AVR_DEBUG:
	ldi r25,    			0xFF
	out _SFR_IO_ADDR(DDRE), r25
	out _SFR_IO_ADDR(PORTE),r24
	clr		XH
	ldi		XL,		0x64
	ldi		r25, 	0b00001111
	st		X, 	r25
	ldi		XL,		0x65
	ldi     r25,   	0xFF
	st     	X,		r25
	ret

.section .bss 
ActiveMemory:
	.byte 1