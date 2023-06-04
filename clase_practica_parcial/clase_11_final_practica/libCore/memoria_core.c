/*Standard Library*/
#include "stdio.h"
#include "string.h"
/*Headers Library*/
#include "libCommon/pantalla.h"
/*File Header*/
#include "memoria_core.h"

void configurarMemoria(dato_memoria* memoria)
{
  memset(memoria[POS_INI_MEM].cadena,0x00,sizeof(memoria[POS_INI_MEM].cadena));
  memoria[POS_INI_MEM].numero = 0;
  memoria[POS_INI_MEM].cantidadJugadores = 0;
}

void escribirNumero(dato_memoria* memoria, int valor)
{
  memoria[POS_INI_MEM].numero = valor;
}

int leerNumero(dato_memoria* memoria)
{
  return memoria[POS_INI_MEM].numero;
}

void escribirCadena(dato_memoria* memoria, char* ptrCadena)
{
  strcpy(memoria[POS_INI_MEM].cadena, ptrCadena);
}

char* leerCadena(dato_memoria* memoria)
{
  return memoria[POS_INI_MEM].cadena;
}

void escribirCantidadJugadores(dato_memoria* memoria, int valor)
{
  memoria[POS_INI_MEM].cantidadJugadores = valor;
}

int leerCantidadJugadores(dato_memoria* memoria)
{
  return memoria[POS_INI_MEM].cantidadJugadores;
}

