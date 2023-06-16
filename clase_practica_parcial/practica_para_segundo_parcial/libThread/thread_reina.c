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
#include "libCommon/semaforos.h"
#include "libCore/defines.h"
#include "libCore/globals.h"
#include "libCore/funciones.h"
/*File Header*/
#include "thread_reina.h"

void* reinaThread(void* parametro)
{
  mensaje msg;
  reina* datosThread;
  int recursoComida;
  int recursoHoja;
  int recursoRama;
  int recursoAgua;
  int finJuego;
  int i;
  int opcion;
  int hormigaNumero;

  msg.longDest = MSG_NADIE;
  msg.intRte = MSG_NADIE;
  msg.intEvento = EVT_NINGUNO;
  memset(msg.charMensaje,0x00,LARGO_MENSAJE);

  datosThread = (reina*)parametro;
  recursoComida = 0;
  recursoHoja = 0;
  recursoRama = 0;
  recursoAgua = 0;
  opcion = 0;
  finJuego = 0;
  hormigaNumero = -1;

  for (i = 0; i < cantidadHormigas; i++)
  {
    opcion = -1;
    while(opcion < 1 || opcion > 4)
    {
      printf("Hormiga %d\n", i);
      printf("Opcion 1: Juntar Comida\n");
      printf("Opcion 2: Juntar Hoja\n");
      printf("Opcion 3: Juntar Rama\n");
      printf("Opcion 4: Juntar Agua\n");

      printf("Ingresar Opcion:\n");
      scanf("%d",&opcion); 
    }

    switch (opcion) {
      case AC_JUNTAR_COMIDA:
        printf("Hormiga %d: Juntar Comida\n", i);
        enviarMensaje(datosThread->idColaMensajes, MSG_HORMIGA + i, MSG_REINA, EVT_JUNTAR_COMIDA, "");
        break;
      case AC_JUNTAR_HOJA:
        printf("Hormiga %d: Juntar Hoja\n", i);
        enviarMensaje(datosThread->idColaMensajes, MSG_HORMIGA + i, MSG_REINA, EVT_JUNTAR_HOJA, "");  
        break;
      case AC_JUNTAR_RAMA: 
        printf("Hormiga %d: Juntar Rama\n", i);
        enviarMensaje(datosThread->idColaMensajes, MSG_HORMIGA + i, MSG_REINA, EVT_JUNTAR_RAMA, "");
        break;
      case AC_JUNTAR_AGUA: 
        printf("Hormiga %d: Juntar Agua\n", i);
        enviarMensaje(datosThread->idColaMensajes, MSG_HORMIGA + i, MSG_REINA, EVT_JUNTAR_AGUA, "");
        break;
      default:
        break;
    }
  }

  while(1)
  {
    lockMutex(&mutex);
    recibirMensaje(datosThread->idColaMensajes, MSG_REINA, &msg);
    hormigaNumero = msg.intRte - MSG_HORMIGA;
    switch(msg.intEvento)
    {
      case EVT_NINGUNO:
        break;
      case EVT_JUNTAR_COMIDA_FIN:
        printf("Hormiga %d: terminó de juntar comida\n", hormigaNumero);
        esperarSemaforo(datosThread->idSemaforo);
        recursoComida = leerRecursoComida(datosThread->memoria, 0);
        levantarSemaforo(datosThread->idSemaforo);
        break;
      case EVT_JUNTAR_HOJA_FIN:
        printf("Hormiga %d: terminó de juntar hojas\n", hormigaNumero);
        esperarSemaforo(datosThread->idSemaforo);
        recursoHoja = leerRecursoHoja(datosThread->memoria, 0);
        levantarSemaforo(datosThread->idSemaforo);
        break;
      case EVT_JUNTAR_RAMA_FIN:
        printf("Hormiga %d: terminó de juntar ramas\n", hormigaNumero);
        esperarSemaforo(datosThread->idSemaforo);
        recursoRama = leerRecursoRama(datosThread->memoria, 0);
        levantarSemaforo(datosThread->idSemaforo);
        break;
      case EVT_JUNTAR_AGUA_FIN:
        printf("Hormiga %d: terminó de juntar agua\n", hormigaNumero);
        esperarSemaforo(datosThread->idSemaforo);
        recursoAgua = leerRecursoAgua(datosThread->memoria, 0);
        levantarSemaforo(datosThread->idSemaforo);
        break;
      default:
        break;
    }
    printf("Recurso Comida: %d unidades\n", recursoComida);
    printf("Recurso Hoja: %d unidades\n", recursoHoja);
    printf("Recurso Rama: %d unidades\n", recursoRama);
    printf("Recurso Agua: %d unidades\n", recursoAgua);
    if (recursoComida >= TOTAL_RECURSO || recursoHoja >= TOTAL_RECURSO || recursoRama >= TOTAL_RECURSO || recursoAgua >= TOTAL_RECURSO)
    {
      finJuego = 1;
      printf("Se alcanzó recurso máximo\n");
      for (i = 0; i < cantidadHormigas; i++)
      {
        enviarMensaje(datosThread->idColaMensajes, MSG_HORMIGA + i, MSG_REINA, EVT_FIN, "");
      }
      break;
    }
    unlockMutex(&mutex);
    if (finJuego == 1)
    {
      break;
    }

    opcion = -1;
    while(opcion < 1 || opcion > 4)
    {
      printf("Hormiga %d\n", hormigaNumero);
      printf("Opcion 1: Juntar Comida\n");
      printf("Opcion 2: Juntar Hoja\n");
      printf("Opcion 3: Juntar Rama\n");
      printf("Opcion 4: Juntar Agua\n");

      printf("Ingresar Opcion:\n");
      scanf("%d",&opcion); 
    }

    switch (opcion) {
      case AC_JUNTAR_COMIDA:
        printf("Hormiga %d: Juntar Comida\n", hormigaNumero);
        enviarMensaje(datosThread->idColaMensajes, MSG_HORMIGA + hormigaNumero, MSG_REINA, EVT_JUNTAR_COMIDA, "");
        break;
      case AC_JUNTAR_HOJA:
        printf("Hormiga %d: Juntar Hoja\n", hormigaNumero);
        enviarMensaje(datosThread->idColaMensajes, MSG_HORMIGA + hormigaNumero, MSG_REINA, EVT_JUNTAR_HOJA, "");  
        break;
      case AC_JUNTAR_RAMA: 
        printf("Hormiga %d: Juntar Rama\n", hormigaNumero);
        enviarMensaje(datosThread->idColaMensajes, MSG_HORMIGA + hormigaNumero, MSG_REINA, EVT_JUNTAR_RAMA, "");
        break;
      case AC_JUNTAR_AGUA: 
        printf("Hormiga %d: Juntar Agua\n", hormigaNumero);
        enviarMensaje(datosThread->idColaMensajes, MSG_HORMIGA + hormigaNumero, MSG_REINA, EVT_JUNTAR_AGUA, "");
        break;
      default:
        break;
    }

    usleep(INTERVALO_REINA_MS * 1000);
  }
  return 0;
}
