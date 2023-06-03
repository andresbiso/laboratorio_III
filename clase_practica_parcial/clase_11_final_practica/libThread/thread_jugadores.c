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
  int idColaMensajes;
  int pasosAleatorio;
  jugador* datosThread;
  mensaje msg;
  char* pasosChar;
  
  idColaMensajes = crearColaMensajes(CLAVE_BASE);
  datosThread = (jugador*)parametro;
  msg.longDest = MSG_NADIE;
  msg.intRte = MSG_NADIE;
  msg.intEvento = EVT_NINGUNO;
  memset(msg.charMensaje,0x00,LARGO_MENSAJE);
  pasosChar = (char*)malloc(sizeof(char)*LARGO_MENSAJE);
  memset(pasosChar,0x00,LARGO_MENSAJE);
  while(1)
  {
    lockMutex(&mutex);
    recibirMensaje(idColaMensajes, MSG_CARRERA, &msg);
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
        sprintf(pasosChar, "%d",pasosAleatorio);
        enviarMensaje(idColaMensajes,MSG_CARRERA,datosThread->nroJugador,EVT_PASO,pasosChar);
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
