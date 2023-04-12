#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include "defines.h"
#include "gestionararchivos.h"
#include "semaforos.h"
#include "funciones.h"
#include "productor.h"
int main(int argc, char *argv[])
{
  int idSemaforo;
  if (argc != 1)
  {
    printf("Uso: ./carga \n");
    return 0;
  }
  
  idSemaforo = creoSemaforo();
  
  iniciaSemaforo(idSemaforo, VERDE);
  
  while(1)
  {
    printf("Esperando Acceso...\n");
    esperaSemaforo(idSemaforo);
    if (!abrirAdicion(RUTA_ARCHIVO_LOTE))
    {
      printf("Hubo un error al querer abrir el archivo\n");
      return 0;
    }
    printf("Acceso Obtenido...\n");
    escribirReservas();
    cerrarArchivo();
    levantaSemaforo(idSemaforo);
    sleep(10);
  }
  return 0;
}
