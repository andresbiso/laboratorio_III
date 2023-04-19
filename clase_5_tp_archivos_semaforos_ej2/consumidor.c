#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "defines.h"
#include "funciones.h"
#include "gestionararchivos.h"

resumen resumenCajeroUno;
resumen resumenCajeroDos;
resumen resumenCajeroTres;
resumen resumenTotal;

void leerDepositosCajero(int cajeroActual)
{
  int monto;
  int esCheque;
  monto = 0;
  valorCheque = 0;
  while(!esFinArchivo())
  {
    leerNumeroArchivo(&monto);
    leerNumeroArchivo(&valorCheque);    if (cajeroActual == 1)
    {
      resumenCajeroUno.tcEfect ++;
      resumenCajeroUno.tsEfect += monto;
      resumenCajeroUno.tcCheq ++;
      resumenCajeroUno.tsCheq += esCheque(valorCheque);
      resumenTotal.tcEfect ++;
      resumenTotal.tsEfect += monto;
      resumenTotal.tcCheq ++;
      resumenTotal.tsCheq += esCheque(valorCheque);
      backupLote(resumenCajeroUno.lote, cajeroActual);
      resumenCajeroUno.lote++;
    }

    if (cajeroActual == 2)
    {
      resumenCajeroDos.tcEfect ++;
      resumenCajeroDos.tsEfect += monto;
      resumenCajeroDos.tcCheq ++;
      resumenCajeroDos.tsCheq += esCheque(valorCheque);
      resumenTotal.tcEfect ++;
      resumenTotal.tsEfect += monto;
      resumenTotal.tcCheq ++;
      resumenTotal.tsCheq += esCheque(valorCheque);
      backupLote(resumenCajeroDos.lote, cajeroActual);
      resumenCajeroDos.lote++;
    }

    if (cajeroActual == 3)
    {
      resumenCajeroTres.tcEfect ++;
      resumenCajeroTres.tsEfect += monto;
      resumenCajeroTres.tcCheq ++;
      resumenCajeroTres.tsCheq += esCheque(valorCheque);
      resumenTotal.tcEfect ++;
      resumenTotal.tsEfect += monto;
      resumenTotal.tcCheq ++;
      resumenTotal.tsCheq += esCheque(valorCheque);
      backupLote(resumenCajeroTres.lote, cajeroActual);
      resumenCajeroTres.lote++;
    }
  }
}

void backupLote(int numLote, int numCajero)
{
  char nuevoLote[32+1];
  sprintf(nuevoLote, RUTA_ARCHIVO_LOTE_BAK, numCajero, numLote);
  renombrarArchivo(RUTA_ARCHIVO_LOTE, nuevoLote);
  limpiarArchivo(RUTA_ARCHIVO_LOTE);
  printf("Generado Backup: %s\n", nuevoLote);
}

void inicializarResumenes()
{
  resumenCajeroUno.tcEfect = 0;
  resumenCajeroUno.tsEfect = 0;
  resumenCajeroUno.tcCheq = 0;
  resumenCajeroUno.tsCheq = 0;
  resumenCajeroUno.lote = 0;

  resumenCajeroDos.tcEfect = 0;
  resumenCajeroDos.tsEfect = 0;
  resumenCajeroDos.tcCheq = 0;
  resumenCajeroDos.tsCheq = 0;
  resumenCajeroDos.lote = 0;

  resumenCajeroTres.tcEfect = 0;
  resumenCajeroTres.tsEfect = 0;
  resumenCajeroTres.tcCheq = 0;
  resumenCajeroTres.tsCheq = 0;
  resumenCajeroTres.lote = 0;

  resumenTotal.tcEfect = 0;
  resumenTotal.tsEfect = 0;
  resumenTotal.tcCheq = 0;
  resumenTotal.tsCheq = 0;
  resumenTotal.lote = 0;
}

void imprimirResumen()
{
  printf("TOTAL\n");
  printf("TC-EFEC T$-EFEC TC-CHEQ T$-CHEQ\n");
  printf("%d %d %d %d\n", resumenTotal.tcEfect, resumenTotal.tsEfect, resumenTotal.tcCheq, resumenTotal.tsCheq);
  printf("CAJERO1\n");
  printf("TC-EFEC T$-EFEC TC-CHEQ T$-CHEQ\n");
  printf("%d %d %d %d\n", resumenCajeroUno.tcEfect, resumenCajeroUno.tsEfect, resumenCajeroUno.tcCheq, resumenCajeroUno.tsCheq);
  printf("CAJERO2\n");
  printf("TC-EFEC T$-EFEC TC-CHEQ T$-CHEQ\n");
  printf("%d %d %d %d\n", resumenCajeroDos.tcEfect, resumenCajeroDos.tsEfect, resumenCajeroDos.tcCheq, resumenCajeroDos.tsCheq);
  printf("CAJERO3\n");
  printf("TC-EFEC T$-EFEC TC-CHEQ T$-CHEQ\n");
  printf("%d %d %d %d\n", resumenCajeroTres.tcEfect, resumenCajeroTres.tsEfect, resumenCajeroTres.tcCheq, resumenCajeroTres.tsCheq);

}
