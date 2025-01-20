# Made by : Raphael Clerault
MCU = atmega128a
F_CPU = 20000000L
CFLAGS = -O3 -w -mmcu=$(MCU) -DF_CPU=$(F_CPU)
LDFLAGS = -O3 -Wl,--gc-sections,--section-start=.FAR_MEM1=0x10000,--section-start=.FAR_MEM2=0x20000,--section-start=.FAR_MEM3=0x30000 -mmcu=$(MCU) -w -flto -g
OBJCOPY_FLAGS = -Oihex -R.eeprom
SRCS = $(wildcard *.c *.cpp *.S)
OBJS = $(SRCS:.c=.o) $(SRCS:.cpp=.o) $(SRCS:.S=.o)
TARGET = main

all: $(TARGET).hex

%.o: %.c
	avr-g++ -c $(CFLAGS) $< -o $@

%.o: %.cpp
	avr-g++ -c $(CFLAGS) $< -o $@

%.o: %.S
	avr-g++ -c $(CFLAGS) $< -o $@

$(TARGET).elf: $(OBJS)
	avr-gcc $(LDFLAGS) $(wildcard *.o) -o $@

$(TARGET).hex: $(TARGET).elf
	avr-objcopy $(OBJCOPY_FLAGS) $< $@
	avr-size -C -x $<
	Run.bat

clean:
	del -f *.o $(TARGET).elf $(TARGET).hex