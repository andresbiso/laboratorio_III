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
#include "libThread/thread_carrera.h"

int main(int argc, char *argv[])
{
  int idColaMensajes;
  int idMemoriaInicial;
  inicial* memoriaInicial;
  int idSemaforo;
  pthread_t* idHilo;
  pthread_attr_t atributos;

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
  idColaMensajes = crearColaMensajes(CLAVE_BASE);
  borrarMensajes(idColaMensajes);
  memoriaInicial = (inicial*)crearMemoria(sizeof(inicial), &idMemoriaInicial, CLAVE_BASE_INI);
  configurarMemoriaInicial(memoriaInicial);

  limpiarPantalla();

  if (!crearThread(&idHilo, &atributos, carreraThread, 0))
  {
    printf("Error: No se pude crear el thread\n");
    return -1;
  }

  joinThread(&idHilo);
  liberarMemoria(idMemoriaInicial, (char*)memoriaInicial);
  liberarColaMensajes(idColaMensajes);
  eliminarSemaforo(idSemaforo);
  destruirMutex(&mutex);
  return 0;
}
