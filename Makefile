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

test:
	mkdir -p obj
	gcc -Wall -std=c99 -Iinclude test/test_config.c -o obj/test_config
	./obj/test_config
	gcc -Wall -std=c99 -Iinclude test/test_checksum.c src/checksum.c -o obj/test_checksum
	./obj/test_checksum
	gcc -Wall -std=c99 -Iinclude test/test_stuff.c src/stuff.c -o obj/test_stuff
	./obj/test_stuff
	gcc -Wall -std=c99 -Iinclude test/test_frame.c src/frame.c -o obj/test_frame
	./obj/test_frame
	gcc -Wall -std=c99 -Iinclude test/test_frag.c src/frag.c -o obj/test_frag
	./obj/test_frag

clean:
	rm -rf obj


.PHONY: build flash clean test