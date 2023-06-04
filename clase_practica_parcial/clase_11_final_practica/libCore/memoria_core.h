#ifndef _MEMORIA_CORE_H
#define _MEMORIA_CORE_H
/*Headers Library*/
#include "libCore/defines.h"
struct tipo_dato_memoria
{
  int numero;
  char cadena[MAX_LARGO_CADENA];
  int cantidadJugadores;
};
typedef struct tipo_dato_memoria dato_memoria;
void configurarMemoria(dato_memoria*);
void escribirNumero(dato_memoria*, int);
int leerNumero(dato_memoria*);
void escribirCadena(dato_memoria*, char*):
char* leerCadena(dato_memoria*);
void escribirCantidadJugadores(dato_memoria*, int);
int leerCantidadJugadores(dato_memoria*);
#endif
