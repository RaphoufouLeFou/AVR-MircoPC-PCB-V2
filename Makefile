CC=avr-gcc
CFLAGS=-mmcu=atmega128a -O3
TARGET=main
SRC=$(wildcard *.cpp *.S)
OBJ=$(SRC:.cpp=.obj)
OBJ:=$(OBJ:.S=.o)

AVRDUDEPATH="C:\Users\rapha\AppData\Local\Arduino15\packages\MegaCore\tools\avrdude\7.2-arduino.1/bin/avrdude"
AVRDUDECONF="C:\Users\rapha\AppData\Local\Arduino15\packages\MegaCore\hardware\avr\3.0.1/avrdude.conf"

all: $(TARGET).hex

%.obj: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).elf: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

$(TARGET).hex: $(TARGET).elf
	avr-objcopy -O ihex $< $@

flash: $(TARGET).hex
	$(AVRDUDEPATH) -C $(AVRDUDECONF) -v -p atmega128 -c usbasp -U flash:w:$(TARGET).hex

clean:
	del -f $(OBJ) $(TARGET).elf $(TARGET).hex