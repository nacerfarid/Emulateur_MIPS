all: emul-mips

emul-mips: mips.o mips_instructions.o mips_decoding.o
	gcc -o emul-mips mips.o mips_instructions.o mips_decoding.o -W -Wall -ansi -pedantic -lm

mips.o: mips.c
	gcc -o mips.o -c mips.c -W -Wall -ansi -pedantic

mips_instructions.o: mips_instructions.c
	gcc -o mips_instructions.o -c mips_instructions.c -W -Wall -ansi -pedantic

mips_decoding.o: mips_decoding.c
	gcc -o mips_decoding.o -c mips_decoding.c -W -Wall -ansi -pedantic

clean:
	rm *.o
