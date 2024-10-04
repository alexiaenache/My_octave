# Copyright 2023 Echipa PCLP1

# compiler setup
CC=gcc -g
CFLAGS=-Wall -Wextra -std=c99

# define targets
TARGETS = my_octave

build: $(TARGETS)

my_octave: my_octave.c
	$(CC) $(CFLAGS) my_octave.c -lm -o my_octave

pack:
	zip -FSr 321CA_EnacheAlexiaIoana_Tema2.zip README Makefile *.c *.h

clean:
	rm -f $(TARGETS)

.PHONY: pack clean
