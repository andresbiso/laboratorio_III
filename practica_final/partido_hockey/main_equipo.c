/*Standard Library*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <signal.h>
/*Headers Library*/
#include "libCommon/memoria.h"
#include "libCommon/memoria_ini.h"
#include "libCommon/cola.h"
#include "libCommon/hilos.h"
#include "libCommon/aleatorio.h"
#include "libCommon/pantalla.h"
#include "libCommon/signals.h"
#include "libCore/defines.h"
#include "libCore/globals.h"
#include "libCore/funciones.h"
#include "libCore/productor.h"
#include "libCore/consumidor.h"
#include "libCore/memoria_core.h"
#include "libThread/thread_equipo.h"

pthread_t* idHilo;
pthread_attr_t atributos;
equipo* datosThread;

void liberarRecursos(void)
{
  free(idHilo);
  free(datosThread);
  destruirMutex(&mutex);
  destruirAttr(&atributos);
}

void manejadorSignals(int signum)
{
    if (signum == SIGINT || signum == SIGALRM)
    {
      puts("Liberando Recursos...");
      liberarRecursos();
      puts("Proceso Finalizado");
      exit(0);
    }
}

int main(int argc, char *argv[])
{
  int idColaMensajes;
  int idMemoria;
  dato_memoria* memoria;
  dato_memoria_ini* memoriaIni;
  int idMemoriaIni;
  int i;
  int nroEquipo;

  if (argc != 2)
  {
    puts("Uso: ./equipo [1-2]");
    return -1;
  }

  memoriaIni = 0; /*NULL*/
  idMemoriaIni = 0;
  memoria = 0;
  idMemoria = 0;
  idHilo = 0;
  cantidadEquipos = CANTIDAD_EQUIPOS;
  cantidadJugadoresEquipo = CANTIDAD_JUGADORES_EQUIPO;

  nroEquipo = atoi(argv[1]);
  if (nroEquipo < 1 || nroEquipo > 2)
  {
    puts("Uso: ./equipo [1-2]");
    return -1;
  }

  srand(time(0));

  iniciarMutex(&mutex);
  iniciarAttr(&atributos);
  asignarEstadoJoinableAttr(&atributos);

  crearSignal(SIGINT, manejadorSignals);
  crearSignal(SIGALRM, manejadorSignals);

  idColaMensajes = crearColaMensajes();
  memoria = (dato_memoria*)crearMemoria(sizeof(dato_memoria)*cantidadEquipos, &idMemoria);
  memoriaIni = crearMemoriaIni(&idMemoriaIni);
  crearAlarma(TIEMPO_ALARMA_DEFAULT);
  verificarMemoriaIni(memoriaIni, "partido");
  cancelarAlarma();

  limpiarPantalla();
  printf("Cantidad equipos %d\n", cantidadEquipos);

  idHilo = (pthread_t*)malloc(sizeof(pthread_t)*cantidadJugadoresEquipo);
  datosThread = (equipo*)malloc(sizeof(equipo)*cantidadJugadoresEquipo);

  for (i = 0; i < cantidadJugadoresEquipo; i++)
  {
    datosThread[i].idColaMensajes = idColaMensajes;
    datosThread[i].memoria = memoria;
    datosThread[i].nroJugador = i;
    datosThread[i].nroEquipo = nroEquipo;

    if (!crearThread(&idHilo[i], &atributos, equipoThread, (void*)&datosThread[i]))
    {
      puts("Error: No se pude crear el thread");
      return -1;
    }
  }

  for (i = 0; i < cantidadJugadoresEquipo; i++)
  {
   joinThread(&idHilo[i]);
  }

  liberarRecursos();

  configurarFinalizarMemoriaIni(memoriaIni);

  return 0;
}
