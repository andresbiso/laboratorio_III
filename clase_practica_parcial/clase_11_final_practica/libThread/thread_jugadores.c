/*Standard Library*/
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include "pthread.h"
/*Headers Library*/
#include "libCore/defines.h"
#include "libCore/globals.h"
#include "libCommon/aleatorio.h"
#include "libCommon/hilos.h"
#include "libCommon/cola.h"
/*File Header*/
#include "thread_jugadores.h"

void* jugadoresThread(void* parametro)
{
  mensaje msg;
  jugador* datosThread;
  int pasosAleatorio;
  
  msg.longDest = MSG_NADIE;
  msg.intRte = MSG_NADIE;
  msg.intEvento = EVT_NINGUNO;
  memset(msg.charMensaje,0x00,LARGO_MENSAJE);

  datosThread = (jugador*)parametro;

  pasosAleatorio = 0;

  while(1)
  {
    lockMutex(&mutex);
    recibirMensaje(idColaMensajes, MSG_JUGADOR+datosThread->numeroJugador, &msg);
    switch(msg.intEvento)
    {
      case EVT_NINGUNO:
        break;
      case EVT_CAMINAR:
        pasosAleatorio = obtenerNumeroAleatorio(PASOS_MIN, PASOS_MAX);
        datosThread->cantidadPasos += pasosAleatorio;
        printf("Jugador %d: camino %d pasos", datosThread->nroJugador, pasosAleatorio);
        printf("Jugador %d: espera %d ms", datosThread->nroJugador, datosThread->intervalo);
        printf("Jugador %d: total %d pasos", datosThread->nroJugador, datosThread->cantidadPasos);
        enviarMensaje(idColaMensajes,MSG_TABLERO,datosThread->nroJugador,EVT_META,"");
        unlockMutex(&mutex);
        usleep(datosThread->intervalo*pasosAleatorio);
        lockMutex(&mutex);
        break;
      case EVT_FIN:
        unlockMutex(&mutex);
        free(pasosChar);
        return 0;
        break;
      default:
        break;
    }
    unlockMutex(&mutex);
    usleep(1000);
  }
  free(pasosChar);
  return 0;
}
