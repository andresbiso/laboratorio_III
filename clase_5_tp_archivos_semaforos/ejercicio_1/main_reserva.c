#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include "defines.h"
#include "gestionararchivos.h"
#include "semaforos.h"
#include "funciones.h"
#include "consumidor.h"
int main(int argc, char *argv[])
{
  int numLote;
  int idSemaforo;
  if (argc != 1)
  {
    printf("Uso: ./reserva \n");
    return 0;
  }
  
  numLote = 0;
  idSemaforo = creoSemaforo();
  iniciaSemaforo(idSemaforo, VERDE);
  
  while(1)
  {
    printf("Esperando Acceso...\n");
    esperaSemaforo(idSemaforo);
    if (!abrirLectura(RUTA_ARCHIVO_LOTE))
    {
      printf("Hubo un error al querer abrir el archivo\n");
      return 0;
    }
    printf("Acceso Obtenido...\n");
    leerReservas();
    cerrarArchivo();
    backupLote(numLote);
    numLote++;
    levantaSemaforo(idSemaforo);
    sleep(10);
  }
  return 0;
}

void backupLote(int numLote)
{
  char[12+1] nuevoLote;
  sprintf(nuevoLote, RUTA_ARCHIVO_LOTE_BACK, numLote);
  renombrarArchivo(RUTA_ARCHIVO_LOTE);
  limpiarARchivo();
}
