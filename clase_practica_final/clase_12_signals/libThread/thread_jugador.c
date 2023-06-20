/*Standard Library*/
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include "pthread.h"
/*Headers Library*/
#include "libCommon/aleatorio.h"
#include "libCommon/hilos.h"
#include "libCommon/cola.h"
#include "libCore/defines.h"
#include "libCore/globals.h"
#include "libCore/funciones.h"
/*File Header*/
#include "thread_jugador.h"

void* jugadorThread(void* parametro)
{
  mensaje msg;
  partido* datosThread;
  int golesJugador;
  msg.longDest = MSG_NADIE;
  msg.intRte = MSG_NADIE;
  msg.intEvento = EVT_NINGUNO;
  memset(msg.charMensaje,0x00,LARGO_MENSAJE);

  datosThread = (partido*)parametro;
  golesJugador = 0;

  while(1)
  {
    lockMutex(&mutex);
    recibirMensaje(datosThread->idColaMensajes, MSG_JUGADOR + datosThread->nroJugador, &msg);
    unlockMutex(&mutex);
    switch(msg.intEvento)
    {
      case EVT_NINGUNO:
        break;
      case EVT_GOL:
        printf("Jugador %s: metió gol\n", nomJugador);
        lockMutex(&mutex);
        golesJugador = leerGoles(datosThread->memoria, numJugador);
        golesJugador++;
        escribirGoles(datosThread->memoria, numJugador, golesJugador);
        unlockMutex(&mutex);
        printf("Jugador %s: total goles -> %d\n", nomJugador, golesJugador);
        break;
      case EVT_FUERA:
        printf("Jugador %s: fuera\n", nomJugador);
        break;
      case EVT_PALO:
        printf("Jugador %s: palo\n", nomJugador);
        break;
      case EVT_ATAJA:
        printf("Jugador %s: atajado\n", nomJugador);
        break;
      default:
        break;
    }
 
    if (leerFinPartido(datosThread->memoria, datosThread->numJugador) == 1)
    {
      printf("Jugador %s: finalizó de jugar\n", datosThread->nomJugador);
      break;
    }

    usleep(INTERVALO_JUGADOR_MS * 1000);
  }
  return 0;
}
