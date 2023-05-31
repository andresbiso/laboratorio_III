CC=gcc-4.1

CFLAGS = -Wall -O4 -std=gnu89 -pedantic-errors -pthread
HEADERS = -I./
all: clean pienso 

pienso: libCore/defines.h libCore/globals.h libCommon/archivos.h libCommon/claves.h libCommon/semaforos.h libCommon/memoria.h libCommon/cola.h libCommon/hilos.h libCore/funciones.h libCore/productor.h libCore/consumidor.h
	$(CC) -o pienso main_pienso.c libCore/globals.c libCommon/archivos.c libCommon/claves.c libCommon/semaforos.c libCommon/memoria.c libCommon/cola.c libCommon/hilos.c libCore/funciones.c libCore/productor.c libCore/consumidor.c $(CFLAGS) $(HEADERS)

clean: 
	rm -rf *o pienso *.txt
