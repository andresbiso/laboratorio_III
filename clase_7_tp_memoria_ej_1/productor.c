#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "defines.h"
#include "globals.h"
#include "funciones.h"
#include "semaforos.h"

void iniciarMemoria(dato* memoria)
{
  int i;
  i = 0;
  memoria[i].nombreJugador = 0; /*NULL*/
  memoria[i].numeroPensado = 0;
  memoria[i].estadoAcierto = 0;
  memoria[i].inicializado = 1;
}

void escribirNumero(dato* memoria, int numeroPensado)
{
  int i;
  i = 0;

  memoria[i].nombreJugador = 0; /*NULL*/
  memoria[i].numeroPensado = numeroPensado;
  memoria[i].estadoAcierto = 0;
  memoria[i].inicializado = 1;
  while (posicion == -1 && i < CANTIDAD)
  {
    if (memoria[i].listo == 0)
    {
      posicion = i;
      memoria[posicion].cajero = cajero;
      memoria[posicion].importe = importe;
      memoria[posicion].cheque = cheque;
      memoria[posicion].listo = 1;

      printf("Posición\t%d\n", posicion);
      printf("Cajero\t%d\n", memoria[posicion].cajero);
      printf("Importe\t%d\n", memoria[posicion].importe);
      printf("Cheque\t%d\n", memoria[posicion].cheque);
      printf("Listo\t%d\n", memoria[posicion].listo);
    }
    i++;
  }
}
