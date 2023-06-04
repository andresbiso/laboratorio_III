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
#include "libThread/thread_carrera.h"

int main(int argc, char *argv[])
{
  int idColaMensajes;
  int idMemoriaInicial;
  inicial* memoriaInicial;
  int idSemaforo;
  pthread_t idHilo;
  pthread_attr_t atributos;
  tablero datosThread;

  if (argc != 1)
  {
    printf("Uso: ./carrera\n");
    return -1;
  }

  memoriaInicial = 0;
  idMemoriaInicial = 0;
  idSemaforo = 0;
  idColaMensajes = 0;
  idHilo = 0;

  srand(time(0));

  iniciarMutex(&mutex);
  iniciarAttr(&atributos);

  idSemaforo = crearSemaforo();
  iniciarSemaforo(idSemaforo, VERDE);
  idColaMensajes = crearColaMensajes();
  borrarMensajes(idColaMensajes);
  idMemoria = (dato_memoria*)crearMemoria(sizeof(dato_memoria), &idMemoriaInicial);
  configurarMemoria(idMemoria);
  memoriaInicial = crearMemoriaInicial(&idMemoriaInicial);
  configurarMemoriaInicial(memoriaInicial);

  limpiarPantalla();

  datosThread.idColaMensajes = idColaMensajes;
  datosThread.idSemaforo = idSemaforo;
  datosThread.idMemoria = idMemoria;
  
  if (!crearThread(&idHilo[0], &atributos, jugadoresThread, (void*)&datosThread))
  {
    printf("Error: No se pude crear el thread\n");
    return -1;
  }

  if (!crearThread(&idHilo, &atributos, carreraThread, 0))
  {
    printf("Error: No se pude crear el thread\n");
    return -1;
  }

  joinThread(&idHilo);
  liberarMemoria(idMemoriaInicial, (char*)memoriaInicial);
  liberarMemoria(idMemoria, (char*)memoria);
  liberarColaMensajes(idColaMensajes);
  eliminarSemaforo(idSemaforo);
  destruirMutex(&mutex);
  return 0;
}
