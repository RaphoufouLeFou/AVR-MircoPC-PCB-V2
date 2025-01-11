avr-g++ -c -O3 -w -mmcu=ATmega128a -DF_CPU=20000000L main.c -o out.o
avr-g++ -c -O3 -w -mmcu=ATmega128a -DF_CPU=20000000L driver.S -o driver.o
avr-g++ -c -O3 -w -mmcu=ATmega128a -DF_CPU=20000000L Display.c -o Display.o
avr-g++ -c -O3 -w -mmcu=ATmega128a -DF_CPU=20000000L RayTracing.cpp -o RayTracing.o
avr-gcc -O3 -Wl,--gc-sections,--section-start=.FAR_MEM1=0x10000,--section-start=.FAR_MEM2=0x20000,--section-start=.FAR_MEM3=0x30000 -mmcu=atmega128a -w -flto -g RayTracing.o driver.o out.o Display.o -o main.elf
avr-objcopy -Oihex -R.eeprom main.elf main.hex -v
avr-size -C -x main.elf
Run.bat