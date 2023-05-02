#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "defines.h"
#include "globals.h"
#include "semaforos.h"
#include "memoria.h"
#include "funciones.h"
#include "consumidor.h"

int main(int argc, char *argv[])
{
  int idMemoria;
  int idSemaforo;
  int aleatorio;
  int i;
  int j;
  int posicion;
  dato* memoria;

  int totalCantidadDepositos;
  int totalCantidadEfectivos;
  int totalCantidadCheques;

  int totalPesosDepositos;
  int totalPesosEfectivos;
  int totalPesosCheques;

  int vTotalCantidadDepositos[CANT_MAX_CAJEROS];
  int vTotalCantidadEfectivos[CANT_MAX_CAJEROS];
  int vTotalCantidadCheques[CANT_MAX_CAJEROS];

  int vTotalPesosDepositos[CANT_MAX_CAJEROS];
  int vTotalPesosEfectivos[CANT_MAX_CAJEROS];
  int vTotalPesosCheques[CANT_MAX_CAJEROS];

  if (argc != 1)
  {
    printf("Uso: ./tesorero \n");
    return 0;
  }

  memoria = 0; /*NULL*/
  idMemoria = 0;
  idSemaforo = 0;
  aleatorio = 0;
  i = 0;
  j = 0;
  posicion = 0;

  totalCantidadDepositos = 0;
  totalCantidadEfectivos = 0;
  totalCantidadCheques = 0;

  totalPesosDepositos = 0;
  totalPesosEfectivos = 0;
  totalPesosCheques = 0;

  vTotalCantidadDepositos = {0};
  vTotalCantidadEfectivos = {0};
  vTotalCantidadCheques = {0};

  vTotalPesosDepositos = {0};
  vTotalPesosEfectivos = {0};
  vTotalPesosCheques = {0};

  srand(time(0));

  idSemaforo = creoSemaforo();
  iniciaSemaforo(idSemaforo, VERDE);
  memoria = (dato*)creoMemoria(sizeof(dato)*CANTIDAD_DEPOSITOS, &idMemoria, CLAVE_BASE);

 /* verificarMemoriaIni(memoria);*/

  while(1)
  {
    leerMemoria(memoria);
    sleep(INTERVALO_DOS_S);
  }
  liberoMemoria(idMemoria, (char*)memoria);
  return 0;
}
