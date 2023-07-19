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

int calcularDestinoJugador(equipo* datosThread)
{
  return MSG_EQUIPO + ((datosThread->nroEquipo - 1) * cantidadJugadoresEquipo) + datosThread->nroJugador;
}

int calcularDestinoArquero(equipo* datosThread)
{
  int otroEquipo;
  otroEquipo = 1;
  if (datosThread->nroEquipo < cantidadEquipos)
  {
    otroEquipo = datosThread->nroEquipo + 1;
  }
  return MSG_EQUIPO + ((otroEquipo - 1) * cantidadJugadoresEquipo) + NUM_ARQUERO;
}

int calcularRemitenteEquipo(int remitente)
{
  int jugadorEquipo;
  int equipo;
  jugadorEquipo = remitente - MSG_EQUIPO;
  equipo = jugadorEquipo / cantidadJugadoresEquipo;
  return equipo;
}

void* equipoThread(void* parametro)
{
  mensaje* msg;
  equipo* datosThread;
  int golesEquipo;
  int intentosEquipo;
  int finPartido;
  int eventoPatear;

  datosThread = (equipo*)parametro;
  golesEquipo = 0;
  intentosEquipo = 0;
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
    recibirMensajeSinEspera(datosThread->idColaMensajes, calcularDestinoJugador(datosThread), msg);
    unlockMutex(&mutex);
    usleep(100 * 1000);

    if (msg->intEvento != EVT_NINGUNO)
    {
      intentosEquipo = leerIntentos(datosThread->memoria, datosThread->nroEquipo);
      intentosEquipo++;
      lockMutex(&mutex);
      escribirIntentos(datosThread->memoria, datosThread->nroEquipo, intentosEquipo);
      unlockMutex(&mutex);
      printf("equipo %s: intento -> %d\n", datosThread->nroEquipo, intentosEquipo);
    }
  
    switch(msg->intEvento)
    {
      case EVT_NINGUNO:
        break;
      case EVT_PATEAR:
        printf("Soy el jugador %d y voy a disparar al arco\n", datosThread->nroJugador);
        eventoPatear = obtenerNumeroAleatorio(EVENTO_MIN, EVENTO_MAX);
        switch(eventoPatear)
        {
          case EVT_GOL:
            printf("equipo %d: jugador %d metió gol\n", datosThread->nroEquipo, datosThread->nroJugador);
            golesEquipo = leerGoles(datosThread->memoria, datosThread->nroEquipo);
            golesEquipo++;
            if (datosThread->nroJugador == NUM_ARQUERO)
            {
              puts("¡Gol de arquero vale doble!");
              golesEquipo++;
            }
            lockMutex(&mutex);
            escribirGoles(datosThread->memoria, datosThread->nroEquipo, golesEquipo);
            enviarMensaje(datosThread->idColaMensajes, MSG_PARTIDO, calcularDestinoJugador(datosThread), EVT_GOL, "");
            enviarMensaje(datosThread->idColaMensajes, calcularDestinoArquero(datosThread), calcularDestinoJugador(datosThread), EVT_GOL, "");
            unlockMutex(&mutex);
            usleep(100 * 1000);
            printf("equipo %d: total goles -> %d\n", datosThread->nroEquipo, golesEquipo);
            break;
          case EVT_FUERA:
            printf("equipo %d: jugador %d fuera\n", datosThread->nroEquipo, datosThread->nroJugador);
            lockMutex(&mutex);
            enviarMensaje(datosThread->idColaMensajes, MSG_PARTIDO, calcularDestinoJugador(datosThread), EVT_FUERA, "");
            enviarMensaje(datosThread->idColaMensajes, calcularDestinoArquero(datosThread), calcularDestinoJugador(datosThread), EVT_FUERA, "");
            unlockMutex(&mutex);
            usleep(100 * 1000);
            break;
          default:
            break;
        }
        break;
      case EVT_GOL:
        printf("Soy el arquero del equipo %d y recibí un gol", datosThread->nroEquipo);
        break;
      case EVT_FUERA:
        printf("El equipo %d safo", calcularRemitenteEquipo(msg->intRte));
        break;
      default:
        break;
    }

    usleep(INTERVALO_EQUIPO_MS * 1000);
  }
  free(msg);
  return 0;
}
