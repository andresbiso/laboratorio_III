/*Standard Library*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
/*Headers Library*/
#include "libCommon/aleatorio.h"
#include "libCommon/hilos.h"
#include "libCommon/cola.h"
#include "libCore/defines.h"
#include "libCore/globals.h"
#include "libCore/funciones.h"
/*File Header*/
#include "thread_equipo.h"

void* equipoThread(void* parametro)
{
  mensaje* msg;
  equipo* datosThread;
  int golesequipo;
  int intentosequipo;
  int finPartido;

  datosThread = (equipo*)parametro;
  golesequipo = 0;
  intentosequipo = 0;
  finPartido = 0;

  msg = (mensaje*)malloc(sizeof(mensaje));

  while(1)
  {
    finPartido = leerFinPartido(datosThread->memoria, datosThread->nroEquipo);

    if (finPartido == 1)
    {
      printf("equipo %d: jugador %d finalizó de jugar\n", datosThread->nroJugador);
      break;
    }
    
    memset(msg, 0x00, sizeof(mensaje));
    msg->longDest = MSG_NADIE;
    msg->intRte = MSG_NADIE;
    msg->intEvento = EVT_NINGUNO;

    lockMutex(&mutex);
    recibirMensajeSinEspera(datosThread->idColaMensajes, MSG_EQUIPO + ((datosThread->nroEquipo - 1) * cantidadJugadoresEquipo) + datosThread->nroJugador , msg);
    unlockMutex(&mutex);
    usleep(100 * 1000);

    if (msg->intEvento != EVT_NINGUNO)
    {
      intentosequipo = leerIntentos(datosThread->memoria, datosThread->nroequipo);
      intentosequipo++;
      lockMutex(&mutex);
      escribirIntentos(datosThread->memoria, datosThread->nroequipo, intentosequipo);
      unlockMutex(&mutex);
      printf("equipo %s: intento -> %d\n", datosThread->nombreequipo, intentosequipo);
    }
  
    switch(msg->intEvento)
    {
      case EVT_NINGUNO:
        break;
      case EVT_GOL:
        printf("equipo %s: metió gol\n", datosThread->nombreequipo);
        golesequipo = leerGoles(datosThread->memoria, datosThread->nroequipo);
        golesequipo++;
        lockMutex(&mutex);
        escribirGoles(datosThread->memoria, datosThread->nroequipo, golesequipo);
        enviarMensaje(datosThread->idColaMensajes, MSG_PARTIDO, MSG_equipo + datosThread->nroequipo, EVT_GOL, "");
        unlockMutex(&mutex);
        usleep(100 * 1000);
        printf("equipo %s: total goles -> %d\n", datosThread->nombreequipo, golesequipo);
        break;
      case EVT_FUERA:
        printf("equipo %s: fuera\n", datosThread->nombreequipo);
        lockMutex(&mutex);
        enviarMensaje(datosThread->idColaMensajes, MSG_PARTIDO, MSG_equipo + datosThread->nroequipo, EVT_FUERA, "");
        unlockMutex(&mutex);
        usleep(100 * 1000);
        break;
      case EVT_PALO:
        printf("equipo %s: palo\n", datosThread->nombreequipo);
        lockMutex(&mutex);
        enviarMensaje(datosThread->idColaMensajes, MSG_PARTIDO, MSG_equipo + datosThread->nroequipo, EVT_PALO, "");
        unlockMutex(&mutex);
        usleep(100 * 1000);
        break;
      case EVT_ATAJA:
        printf("equipo %s: atajado\n", datosThread->nombreequipo);
        lockMutex(&mutex);
        enviarMensaje(datosThread->idColaMensajes, MSG_PARTIDO, MSG_equipo + datosThread->nroequipo, EVT_ATAJA, "");
        unlockMutex(&mutex);
        usleep(100 * 1000);
        break;
      default:
        break;
    }

    usleep(INTERVALO_EQUIPO_MS * 1000);
  }
  free(msg);
  return 0;
}
