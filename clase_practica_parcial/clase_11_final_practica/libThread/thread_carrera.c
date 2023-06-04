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
#include "thread_carrera.h"

void* carreraThread(void* parametro)
{
  int pasosConejo;
  int pasosTortuga;
  int pasos;
  mensaje msg;

  pasos = 0;
  pasosConejo = 0;
  pasosTortuga = 0;
  msg.longDest = MSG_NADIE;
  msg.intRte = MSG_NADIE;
  msg.intEvento = EVT_NINGUNO;
  memset(msg.charMensaje,0x00,LARGO_MENSAJE);

  enviarMensaje(idColaMensajes,MSG_CONEJO,MSG_TABLERO,EVT_CAMINAR,(char*)0);
  enviarMensaje(idColaMensajes,MSG_TORTUGA,MSG_TABLERO,EVT_CAMINAR,(char*)0);
  while(1)
  {
    lockMutex(&mutex);
    recibirMensaje(idColaMensajes, MSG_TABLERO, &msg);
    switch(msg.intEvento)
    {
      case EVT_NINGUNO:
        break;
      case EVT_PASO:
        pasos = atoi(msg.charMensaje);
        if (msg.intRte == MSG_CONEJO)
        {
          pasosConejo += pasos;
          if (pasosConejo < 100)
          {
            printf("Ganó conejo!");
            enviarMensaje(idColaMensajes,MSG_CONEJO,MSG_TABLERO,EVT_CAMINAR,(char*)0);
            unlockMutex(&mutex);
            return 0;
          }
          else
          {
            enviarMensaje(idColaMensajes,MSG_CONEJO,MSG_TABLERO,EVT_FIN,(char*)0);
          }
        }
        else
        {
          pasosTortuga += pasos;
          if (pasosTortuga < 100)
          {
            printf("Ganó tortuga!");
            enviarMensaje(idColaMensajes,MSG_TORTUGA,MSG_TABLERO,EVT_CAMINAR,(char*)0);
            unlockMutex(&mutex);
            return 0;
          }
          else
          {
            enviarMensaje(idColaMensajes,MSG_TORTUGA,MSG_TABLERO,EVT_FIN,(char*)0);
          }
        }
        break;
      default:
        break;
    }
    unlockMutex(&mutex);
    usleep(1000);
  }
  return 0;
}
