FILES = src/*.c lib/*.c
FLAGS = -mmcu=atmega644p -DF_CPU=12000000UL -Os -Wall -std=c99 -Iinclude -Ilib 
# 								  12MHz

build:
	mkdir -p obj
	avr-gcc $(FLAGS) $(FILES) -o obj/main.elf
	avr-objcopy -O ihex obj/main.elf obj/main.hex
	avr-size obj/main.elf

flash: build
	avrdude -c usbasp -p m644p -U flash:w:obj/main.hex
clean:
	rm -rf obj
