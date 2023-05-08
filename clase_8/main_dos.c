#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "time.h"
#include "defines.h"
#include "globals.h"
#include "semaforos.h"
#include "memoria.h"
#include "funciones.h"
#include "productor.h"
#include "consumidor.h"

int main(int argc, char *argv[])
{
  int idMemoriaInicial;
  int idSemaforo;
  inicial* memoriaInicial;

  if (argc != 1)
  {
    printf("Uso: ./dos \n");
    return 0;
  }

  memoriaInicial = 0; /*NULL*/
  idMemoriaInicial = 0;
  idSemaforo = 0;


  srand(time(0));

  idSemaforo = creoSemaforo();
  
  memoriaInicial = (inicial*)creoMemoria(sizeof(inicial)*CANTIDAD, &idMemoriaInicial, CLAVE_BASE_INI);
  verificarMemoriaInicial(memoriaInicial);

  limpiarPantalla();

  while(1)
  {
    esperaSemaforo(idSemaforo);

    levantaSemaforo(idSemaforo);
    usleep(INTERVALO_JUGADOR_MS * 1000);
  }
  liberoMemoria(idMemoriaInicial, (char*)memoriaInicial);
  return 0;
}
