CC=gcc-4.1

CFLAGS = -Wall -O3 -std=gnu89 -pedantic-errors
HEADERS = -I./
all : programa

programa: funciones.h 
	$(CC) -o programa punto_1.c funciones.c $(CFLAGS) $(HEADERS)

clean: 
	rm -rf *o programa
