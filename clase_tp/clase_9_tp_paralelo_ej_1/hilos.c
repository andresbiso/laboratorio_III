#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include "pthread.h"
#include "defines.h"
#include "globals.h"
#include "funciones.h"

void iniciarMutex(pthread_mutex_t* mutex)
{
  pthread_mutex_init(mutex, 0);
}

void destruirMutex(pthread_mutex_t* mutex)
{
  pthread_mutex_destroy(mutex);
}

void iniciarAttr(pthread_attr_t* atributos)
{
  pthread_attr_init(atributos);
  pthread_attr_setdetachstate(atributos, PTHREAD_CREATE_JOINABLE);
}

void joinThread(pthread_t* hilo)
{
  pthread_join(*hilo, 0);
}

/*Ejemplo uso: joinThreadValorSalida(&idHilo, (void*)&valorDevuelto)*/
/*char* valorDevuelto; valorDevuelto = 0;*/
/*No responde bien al free(valorDevuelto) luego del pthread_exit()*/
void joinThreadValorSalida(pthread_t* hilo, char* valorDevuelto)
{
    pthread_join(*hilo, (void**)valorDevuelto);
}

void lockMutex(pthread_mutex_t* mutex)
{
  pthread_mutex_lock(mutex);
}

void unlockMutex(pthread_mutex_t* mutex)
{
  pthread_mutex_unlock(mutex);
}

void* funcionThread(void* parametro)
{
  int numeroPensadoJugador;
  int intervalo;
  jugador* datosThread;
  numeroPensadoJugador = 0;
  intervalo = 0;
  datosThread = (jugador*)parametro;
  while(1)
  {
    lockMutex(&mutex);
    printf("Jugador %d: Pensando número...\n", datosThread->nroJugador);
    numeroPensadoJugador = obtenerNumeroAleatorio(NUM_MIN, NUM_MAX);
    printf("Jugador %d: Número pensado %d\n",  datosThread->nroJugador, numeroPensadoJugador);
    datosThread->cantidadIntentos++;
    if (numeroPensadoJugador == numeroPensadoJugador)
    {
       datosThread->alguienAcerto = datosThread->nroJugador;
       break;
    }
    intervalo = obtenerNumeroAleatorio(INTERVALO_JUGADOR_MS_MIN, INTERVALO_JUGADOR_MS_MAX);
    unlockMutex(&mutex);
    usleep(intervalo * 1000);
  }
  return 0;
  
  /*Alternativa:*/
  /*Permite retornar un valor*/
  /*pthread_exit((void*)0);*/
}

int crearThread(pthread_t* hilo, pthread_attr_t* atributos, void* arg)
{
  return pthread_create(hilo, atributos, funcionThread, arg) == 0;
}
