/*Standard Library*/
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include "pthread.h"
/*Headers Library*/
#include "libCommon/semaforos.h"
#include "libCommon/aleatorio.h"
#include "libCommon/hilos.h"
#include "libCommon/cola.h"
#include "libCore/defines.h"
#include "libCore/globals.h"
#include "libCore/funciones.h"
/*File Header*/
#include "thread_jugadores.h"

void* jugadoresThread(void* parametro)
{
  mensaje msg;
  jugador* datosThread;
  int pasosAleatorio;
  int intervalo;
  int pasosJugador;
  int tiempoEspera;
  int mitadCamino;
  int finJuego;
  
  msg.longDest = MSG_NADIE;
  msg.intRte = MSG_NADIE;
  msg.intEvento = EVT_NINGUNO;
  memset(msg.charMensaje,0x00,LARGO_MENSAJE);

  datosThread = (jugador*)parametro;

  pasosAleatorio = 0;
  pasosJugador = 0;
  tiempoEspera = 0;
  mitadCamino = 0;
  finJuego = 0;

  esperarSemaforo(datosThread->idSemaforo);
  escribirNombreJugador(datosThread->memoria, datosThread->nroJugador, obtenerNombreJugador(datosThread->nroJugador));
  levantarSemaforo(datosThread->idSemaforo);
  intervalo = obtenerIntervaloJugador(datosThread->nroJugador);

  while(msg.intEvento != EVT_FIN)
  {
    lockMutex(&mutex);
    recibirMensaje(datosThread->idColaMensajes, MSG_JUGADOR + datosThread->nroJugador, &msg);
    switch(msg.intEvento)
    {
      case EVT_NINGUNO:
        break;
      case EVT_CAMINAR:
        pasosAleatorio = obtenerNumeroAleatorio(PASOS_MIN, PASOS_MAX);
        esperarSemaforo(datosThread->idSemaforo);
        pasosJugador = leerPasosJugador(datosThread->memoria, datosThread->nroJugador) + pasosAleatorio;
        escribirPasosJugador(datosThread->memoria, datosThread->nroJugador, pasosJugador);
        levantarSemaforo(datosThread->idSemaforo);
        tiempoEspera = intervalo * pasosAleatorio * 1000;
        if (mitadCamino == 0 && pasosJugador >= 50)
        {
          if (datosThread->nroJugador == 0)
          {
            tiempoEspera = 5 * 1000;
          }
          mitadCamino = 1;
        }
        printf("Jugador %d: camino %d pasos\n", datosThread->nroJugador, pasosAleatorio);
        printf("Jugador %d: espera %d ms\n", datosThread->nroJugador, tiempoEspera);
        printf("Jugador %d: total %d pasos\n", datosThread->nroJugador, pasosJugador);
        enviarMensaje(datosThread->idColaMensajes, MSG_TABLERO, MSG_JUGADOR + datosThread->nroJugador, EVT_CAMINAR_FIN, "");
        break;
      case EVT_FIN:
        finJuego = 1;
        break;
      default:
        break;
    }
    unlockMutex(&mutex);
    if (finJuego == 1)
    {
      break;
    }
    tiempoEspera = tiempoEspera != 0 ? tiempoEspera : intervalo;
    usleep(tiempoEspera);
  }
  return 0;
}
