CC=gcc-4.1

CFLAGS = -Wall -O4 -std=gnu89 -pedantic-errors -pthread
HEADERS = -I./
LIB_H = libCore/defines.h libCore/globals.h libCommon/archivos.h libCommon/claves.h libCommon/semaforos.h libCommon/memoria.h libCommon/memoria_ini.h libCommon/cola.h libCommon/hilos.h libCommon/aleatorio.h libCommon/cadenas.h libCommon/pantalla.h libCore/funciones.h libCore/productor.h libCore/consumidor.h libCore/memoria_core.h
LIB_C = libCore/globals.c libCommon/archivos.c libCommon/claves.c libCommon/semaforos.c libCommon/memoria.c libCommon/memoria_ini.c libCommon/cola.c libCommon/hilos.c libCommon/aleatorio.c libCommon/cadenas.c libCommon/pantalla.c libCore/funciones.c libCore/productor.c libCore/consumidor.c libCore/memoria_core.c
all: clean carrera jugadores 

carrera: $(LIB_H) libThread/thread_carrera.h
	$(CC) -o carrera main_carrera.c $(LIB_C) libThread/thread_carrera.c $(CFLAGS) $(HEADERS)
jugadores: $(LIB_H) libThread/thread_jugadores.h
	$(CC) -o jugadores main_jugadores.c $(LIB_C) libThread/thread_jugadores.c $(CFLAGS) $(HEADERS)

clean: 
	rm -rf *o carrera jugadores *.txt
