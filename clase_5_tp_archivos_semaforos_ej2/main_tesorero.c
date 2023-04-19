#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "defines.h"
#include "gestionararchivos.h"
#include "semaforos.h"
#include "funciones.h"
#include "productor.h"
#include "consumidor.h"
int main(int argc, char *argv[])
{
  int idSemaforoCajero;
  int cajeroActual;
  char* rutaArchivo;

  if (argc != 1)
  {
    printf("Uso: ./tesorero \n");
    return 0;
  }
  
  idSemaforoCajero = creoSemaforo();
  iniciaSemaforo(idSemaforoPanel, VERDE);

  rutaArchivo = (char*)malloc(100*sizeof(char));
  memset(rutaArchivo,0x00,sizeof(rutaArchivo));
  cajeroActual = 1;

  inicializarResumenes();

  while(1)
  {
    strcpy(rutaArchivo, obtenerRutaArchivoPanel(cajeroActual));
    esperaSemaforo(idSemaforoPanel);

    if (abrirLectura(rutaArchivo))
    {
      while(!esFinArchivo())
      {
        leerDepositosCajero(cajeroActual);
      }  
      cerrarArchivo();
    }

    imprimirResumen();

    if (cajeroActual < 3)
    {
      cajeroActual++;
    }
    else
    {
      cajeroACtual = 1;
    }
    levantaSemaforo(idSemaforoPanel);
    memset(rutaArchivo,0x00,sizeof(rutaArchivo));
    usleep(INTERVALO_TESORERO_MS * 1000);
  }
  free(rutaArchivo);
  return 0;
}
