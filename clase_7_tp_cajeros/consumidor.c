#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "defines.h"
#include "globals.h"
#include "funciones.h"

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

void verificarMemoriaIni(dato* memoria)
{
  int i;
  i = 0;
  while (memoria[i].inicializado != 1)
  {
    printf("Atención: Recuerde levantar el programa inicial \"uno\". Presione \"enter\" para continuar...\n");
    getchar();
  }

  limpiarPantalla();
}

void leerMemoria(dato* memoria)
{
  int i;
  printf("Leemos en la memoria\n");
  for (i=0; i < CANTIDAD; i++)
  {
    printf("Leído %d %c\n", memoria[i].numero, memoria[i].letra);
    sleep(1);
  }
  printf("Dejamos de leer la memoria\n");
}

void inicializarResumenes()
{
  totalCantidadDepositos = 0;
  totalCantidadEfectivos = 0;
  totalCantidadCheques = 0;

  totalPesosDepositos = 0;
  totalPesosEfectivos = 0;
  totalPesosCheques = 0;
  /*{0}: inicializa todo los elementos del array en 0*/
  vTotalCantidadDepositos = {0};
  vTotalCantidadEfectivos = {0};
  vTotalCantidadCheques = {0};

  vTotalPesosDepositos = {0};
  vTotalPesosEfectivos = {0};
  vTotalPesosCheques = {0};
}

void imprimirResumen()
{
  printf("TOTAL\n");
  printf("TC-EFEC T$-EFEC TC-CHEQ T$-CHEQ\n");
  printf("%d\t%d\t%d\t%d\n", resumenTotal.tcEfect, resumenTotal.tsEfect, resumenTotal.tcCheq, resumenTotal.tsCheq);
  printf("CAJERO1\n");
  printf("TC-EFEC T$-EFEC TC-CHEQ T$-CHEQ\n");
  printf("%d\t%d\t%d\t%d\n", resumenCajeroUno.tcEfect, resumenCajeroUno.tsEfect, resumenCajeroUno.tcCheq, resumenCajeroUno.tsCheq);
  printf("CAJERO2\n");
  printf("TC-EFEC T$-EFEC TC-CHEQ T$-CHEQ\n");
  printf("%d\t%d\t%d\t%d\n", resumenCajeroDos.tcEfect, resumenCajeroDos.tsEfect, resumenCajeroDos.tcCheq, resumenCajeroDos.tsCheq);
  printf("CAJERO3\n");
  printf("TC-EFEC T$-EFEC TC-CHEQ T$-CHEQ\n");
  printf("%d\t%d\t%d\t%d\n", resumenCajeroTres.tcEfect, resumenCajeroTres.tsEfect, resumenCajeroTres.tcCheq, resumenCajeroTres.tsCheq);
}

void leerDepositosCajeros()
{
}
