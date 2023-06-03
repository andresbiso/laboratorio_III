/*Standard Library*/
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "time.h"
#include "pthread.h"
/*Headers Library*/
#include "libCommon/semaforos.h"
#include "libCommon/memoria.h"
#include "libCommon/cola.h"
#include "libCommon/hilos.h"
#include "libCommon/aleatorio.h"
#include "libCommon/pantalla.h"
#include "libCore/defines.h"
#include "libCore/globals.h"
#include "libCore/funciones.h"
#include "libCore/productor.h"
#include "libCore/consumidor.h"
#include "libCore/memoria_core.h"
#include "libThread/thread_jugadores.h"

int main(int argc, char *argv[])
{
  int idColaMensajes;
  int idMemoriaInicial;
  int idSemaforo;
  inicial* memoriaInicial;
  pthread_t* idHilo;
  pthread_attr_t atributos;
  jugador* datosThread;

  if (argc != 1)
  {
    printf("Uso: ./jugadores\n");
    return -1;
  }

  memoriaInicial = 0; /*NULL*/
  idMemoriaInicial = 0;
  idSemaforo = 0;
  idHilo = 0;

  srand(time(0));

  iniciarMutex(&mutex);
  iniciarAttr(&atributos);

  srand(time(0));
  idSemaforo = crearSemaforo();
  idColaMensajes = crearColaMensajes(CLAVE_BASE);
  memoriaInicial = (inicial*)crearMemoria(sizeof(inicial), &idMemoriaInicial, CLAVE_BASE_INI);
  verificarMemoriaInicial(memoriaInicial);

  limpiarPantalla();

  idHilo = (pthread_t*)malloc(sizeof(pthread_t)*2);
  datosThread = (jugador*)malloc(sizeof(jugador)*2);

  datosThread[0].nroJugador = MSG_CONEJO;
  datosThread[0].cantidadPasos = 0;
  datosThread[0].intervalo = INTERVALO_PASO_CONEJO_MS;
  datosThread[1].nroJugador = MSG_TORTUGA;
  datosThread[1].cantidadPasos = 0;
  datosThread[1].intervalo = INTERVALO_PASO_TORTUGA_MS;
  if (!crearThread(&idHilo[0], &atributos, jugadoresThread, (void*)&datosThread[0]))
  {
    printf("Error: No se pude crear el thread\n");
    return -1;
  }
  if (!crearThread(&idHilo[1], &atributos, jugadoresThread, (void*)&datosThread[1]))
  {
    printf("Error: No se pude crear el thread\n");
    return -1;
  }
  
  joinThread(&idHilo[0]);
  joinThread(&idHilo[1]);
  free(idHilo);
  free(datosThread);
  liberarMemoria(idMemoriaInicial, (char*)memoriaInicial);
  liberarColaMensajes(idColaMensajes);
  eliminarSemaforo(idSemaforo);
  destruirMutex(&mutex);
  return 0;
}
