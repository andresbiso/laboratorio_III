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
#include "libCommon/memoria_ini.h"
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
  int cantidadJugadores;
  int i;

  if (argc != 1)
  {
    printf("Uso: ./jugadores\n");
    return -1;
  }

  memoriaInicial = 0; /*NULL*/
  idMemoriaInicial = 0;
  idSemaforo = 0;
  idHilo = 0;
  cantidadJugadores = CANTIDAD_JUGADORES;

  srand(time(0));

  iniciarMutex(&mutex);
  iniciarAttr(&atributos);

  srand(time(0));

  idSemaforo = crearSemaforo();
  idColaMensajes = crearColaMensajes();
  idMemoria = (dato_memoria*)crearMemoria(sizeof(dato_memoria), &idMemoriaInicial);
  memoriaInicial = crearMemoriaInicial(&idMemoriaInicial);
  verificarMemoriaInicial(memoriaInicial, "carrera");

  limpiarPantalla();

  idHilo = (pthread_t*)malloc(sizeof(pthread_t)*cantidadJugadores);
  datosThread = (jugador*)malloc(sizeof(jugador)*cantidadJugadores);

  for (i = 0; i < cantidadJugadores; i++)
  {
    dsatosThread.idColaMensajes = idColaMensajes;
    datosThread.idSemaforo = idSemaforo;
    datosThread.idMemoria = idMemoria;
    datosThread[0].nroJugador = MSG_CONEJO;
    datosThread[0].cantidadPasos = 0;
    datosThread[0].idColaMensajes = idColaMensajes;
  }
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
  liberarMemoria(idMemoria, (char*)memoria);
  liberarColaMensajes(idColaMensajes);
  eliminarSemaforo(idSemaforo);
  destruirMutex(&mutex);
  return 0;
}
