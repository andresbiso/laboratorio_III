#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "defines.h"
#include "globals.h"
#include "funciones.h"

void verificarMemoriaIni(dato* memoria)
{
  int i;
  i = 0;
  while (memoria[i].inicializado != 1)
  {
    printf("Atención: Recuerde levantar el programa inicial \"tesorero\". Presione \"enter\" para continuar...\n");
    getchar();
  }

  limpiarPantalla();
}

void leerMemoria(dato* memoria)
{
  int i;
  i = 0;
  while (i < CANTIDAD)
  {
    if (memoria[i].listo == 1)
    {
      if (memoria[i].cajero <= CANT_MAX_CAJEROS)
      {
        memoria[i].listo = 0;
        totalCantidadDepositos++;
        totalPesosDepositos += memoria[i].importe;
        vTotalCantidadDepositos[(memoria[i].cajero)-1]++; 
        vTotalPesosDepositos[(memoria[i].cajero)-1] += memoria[i].importe;

        if (memoria[i].cheque == 0)
        {
          totalCantidadEfectivos++;
          totalPesosEfectivos += memoria[i].importe;
          vTotalCantidadEfectivos[(memoria[i].cajero)-1]++; 
          vTotalPesosEfectivos[(memoria[i].cajero)-1] += memoria[i].importe;
        }
        else
        {
          totalCantidadCheques++;
          totalPesosCheques += memoria[i].importe;
          vTotalCantidadCheques[(memoria[i].cajero)-1]++; 
          vTotalPesosCheques[(memoria[i].cajero)-1] += memoria[i].importe;
        } 
      }
    }
    i++;
  }
}
