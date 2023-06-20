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
#include "libCore/menus.h"
/*File Header*/
#include "thread_reina.h"

void accionesReina(int opcion, int idColaMensajes, int numeroHormiga)
{
    switch (opcion) {
      case AC_JUNTAR_COMIDA:
        printf("Hormiga %d: juntar comida\n", numeroHormiga);
        lockMutex(&mutex);
        enviarMensaje(idColaMensajes, MSG_HORMIGA + numeroHormiga, MSG_REINA, EVT_JUNTAR_COMIDA, "");
        unlockMutex(&mutex);
        break;
      case AC_JUNTAR_HOJA:
        printf("Hormiga %d: juntar hoja\n", numeroHormiga);
        lockMutex(&mutex);
        enviarMensaje(idColaMensajes, MSG_HORMIGA + numeroHormiga, MSG_REINA, EVT_JUNTAR_HOJA, "");
        unlockMutex(&mutex);
        break;
      case AC_JUNTAR_RAMA: 
        printf("Hormiga %d: juntar rama\n", numeroHormiga);
        lockMutex(&mutex);
        enviarMensaje(idColaMensajes, MSG_HORMIGA + numeroHormiga, MSG_REINA, EVT_JUNTAR_RAMA, "");
        unlockMutex(&mutex);
        break;
      case AC_JUNTAR_AGUA: 
        printf("Hormiga %d: juntar agua\n", numeroHormiga);
        lockMutex(&mutex);
        enviarMensaje(idColaMensajes, MSG_HORMIGA + numeroHormiga, MSG_REINA, EVT_JUNTAR_AGUA, "");
        unlockMutex(&mutex);
        break;
      default:
        break;
    }
}

void* reinaThread(void* parametro)
{
  mensaje msg;
  reina* datosThread;
  int recursoComida;
  int recursoHoja;
  int recursoRama;
  int recursoAgua;
  int cantHormigasFin;
  int i;
  int opcion;
  int numeroHormiga;

  msg.longDest = MSG_NADIE;
  msg.intRte = MSG_NADIE;
  msg.intEvento = EVT_NINGUNO;
  memset(msg.charMensaje,0x00,LARGO_MENSAJE);

  datosThread = (reina*)parametro;
  recursoComida = 0;
  recursoHoja = 0;
  recursoRama = 0;
  recursoAgua = 0;
  opcion = -1;
  cantHormigasFin = 0;
  numeroHormiga = -1;

  for (i = 0; i < cantidadHormigas; i++)
  {
    opcion = mostrarMenuReina(i);
    accionesReina(opcion, datosThread->idColaMensajes, i);
  }

  while(1)
  {
    lockMutex(&mutex);
    recibirMensaje(datosThread->idColaMensajes, MSG_REINA, &msg);
    unlockMutex(&mutex);
    numeroHormiga = msg.intRte - MSG_HORMIGA;
    switch(msg.intEvento)
    {
      case EVT_NINGUNO:
        break;
      case EVT_JUNTAR_COMIDA_FIN:
        printf("Hormiga %d: terminó de juntar comida\n", numeroHormiga);
        break;
      case EVT_JUNTAR_HOJA_FIN:
        printf("Hormiga %d: terminó de juntar hojas\n", numeroHormiga);
        break;
      case EVT_JUNTAR_RAMA_FIN:
        printf("Hormiga %d: terminó de juntar ramas\n", numeroHormiga);
        break;
      case EVT_JUNTAR_AGUA_FIN:
        printf("Hormiga %d: terminó de juntar agua\n", numeroHormiga);
        break;
      case EVT_FIN_HORMIGA:
        printf("Hormiga %d: finalizó su trabajo\n", numeroHormiga);
        cantHormigasFin++;
        numeroHormiga = -1;
        break;
      default:
        break;
    }

    lockMutex(&mutex);
    recursoComida = leerRecursoComida(datosThread->memoria, 0);
    recursoHoja = leerRecursoHoja(datosThread->memoria, 0);
    recursoRama = leerRecursoRama(datosThread->memoria, 0);
    recursoAgua = leerRecursoAgua(datosThread->memoria, 0);
    unlockMutex(&mutex);
    printf("Recurso Comida: %d unidades\n", recursoComida);
    printf("Recurso Hoja: %d unidades\n", recursoHoja);
    printf("Recurso Rama: %d unidades\n", recursoRama);
    printf("Recurso Agua: %d unidades\n", recursoAgua);
 
    if (cantHormigasFin >= cantidadHormigas)
    {
      printf("Reina: todas las hormigas finalizaron su trabajo\n");
      break;
    }

    if (numeroHormiga >= 0)
    {
      opcion = mostrarMenuReina(numeroHormiga);
      accionesReina(opcion, datosThread->idColaMensajes, numeroHormiga);
    }

    usleep(INTERVALO_REINA_MS * 1000);
  }
  return 0;
}
