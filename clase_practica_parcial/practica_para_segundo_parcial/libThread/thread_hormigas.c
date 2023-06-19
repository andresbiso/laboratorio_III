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
#include "thread_hormigas.h"

void* hormigasThread(void* parametro)
{
  mensaje msg;
  hormiga* datosThread;
  int recursoAleatorio;
  int recursoTotal;
  int finJuego;
  
  msg.longDest = MSG_NADIE;
  msg.intRte = MSG_NADIE;
  msg.intEvento = EVT_NINGUNO;
  memset(msg.charMensaje,0x00,LARGO_MENSAJE);

  datosThread = (hormiga*)parametro;

  recursoAleatorio = 0;
  recursoTotal = 0;
  finJuego = 0;

  while(msg.intEvento != EVT_FIN)
  {
    lockMutex(&mutex);
    recibirMensaje(datosThread->idColaMensajes, MSG_HORMIGA + datosThread->nroHormiga, &msg);
    unlockMutex(&mutex);
    switch(msg.intEvento)
    {
      case EVT_NINGUNO:
        break;
      case EVT_JUNTAR_COMIDA:
        recursoAleatorio = obtenerNumeroAleatorio(JUNTAR_MIN, JUNTAR_MAX);
        lockMutex(&mutex);
        recursoTotal = leerRecursoComida(datosThread->memoria, 0);
        unlockMutex(&mutex);
        recursoTotal += recursoAleatorio;
        lockMutex(&mutex);
        escribirRecursoComida(datosThread->memoria, 0, recursoTotal);
        unlockMutex(&mutex);
        printf("Hormiga %d: obtuvo %d recurso comida\n", datosThread->nroHormiga, recursoAleatorio);
        printf("Hormiga %d: total %d recurso comida\n", datosThread->nroHormiga, recursoTotal);
        enviarMensaje(datosThread->idColaMensajes, MSG_REINA, MSG_HORMIGA + datosThread->nroHormiga, EVT_JUNTAR_COMIDA_FIN, "");
        break;
      case EVT_JUNTAR_HOJA:
        recursoAleatorio = obtenerNumeroAleatorio(JUNTAR_MIN, JUNTAR_MAX);
        lockMutex(&mutex);
        recursoTotal = leerRecursoHoja(datosThread->memoria, 0);
        unlockMutex(&mutex);
        recursoTotal += recursoAleatorio;
        lockMutex(&mutex);
        escribirRecursoHoja(datosThread->memoria, 0, recursoTotal);
        unlockMutex(&mutex);
        printf("Hormiga %d: obtuvo %d recurso hoja\n", datosThread->nroHormiga, recursoAleatorio);
        printf("Hormiga %d: total %d recurso hoja\n", datosThread->nroHormiga, recursoTotal);
        enviarMensaje(datosThread->idColaMensajes, MSG_REINA, MSG_HORMIGA + datosThread->nroHormiga, EVT_JUNTAR_HOJA_FIN, "");
        break;
      case EVT_JUNTAR_RAMA:
        recursoAleatorio = obtenerNumeroAleatorio(JUNTAR_MIN, JUNTAR_MAX);
        lockMutex(&mutex);
        recursoTotal = leerRecursoRama(datosThread->memoria, 0);
        unlockMutex(&mutex);
        recursoTotal += recursoAleatorio;
        lockMutex(&mutex);
        escribirRecursoRama(datosThread->memoria, 0, recursoTotal);
        unlockMutex(&mutex);
        printf("Hormiga %d: obtuvo %d recurso rama\n", datosThread->nroHormiga, recursoAleatorio);
        printf("Hormiga %d: total %d recurso rama\n", datosThread->nroHormiga, recursoTotal);
        enviarMensaje(datosThread->idColaMensajes, MSG_REINA, MSG_HORMIGA + datosThread->nroHormiga, EVT_JUNTAR_RAMA_FIN, "");
        break;
      case EVT_JUNTAR_AGUA:
        recursoAleatorio = obtenerNumeroAleatorio(JUNTAR_MIN, JUNTAR_MAX);
        lockMutex(&mutex);
        recursoTotal = leerRecursoAgua(datosThread->memoria, 0);
        unlockMutex(&mutex);
        recursoTotal += recursoAleatorio;
        lockMutex(&mutex);
        escribirRecursoAgua(datosThread->memoria, 0, recursoTotal);
        unlockMutex(&mutex);
        printf("Hormiga %d: obtuvo %d recurso agua\n", datosThread->nroHormiga, recursoAleatorio);
        printf("Hormiga %d: total %d recurso agua\n", datosThread->nroHormiga, recursoTotal);
        enviarMensaje(datosThread->idColaMensajes, MSG_REINA, MSG_HORMIGA + datosThread->nroHormiga, EVT_JUNTAR_AGUA_FIN, "");
        break;
      case EVT_FIN:
        finJuego = 1;
        printf("Hormiga %d: fin de juego\n", datosThread->nroHormiga);
        break;
      default:
        break;
    }
    if (finJuego == 1)
    {
      break;
    }
    usleep(INTERVALO_HORMIGA_MS * 1000);
  }
  return 0;
}
