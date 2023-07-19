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
#include "libCore/menus.h"
/*File Header*/
#include "thread_partido.h"

int calcularDestinoJugador(int nroEquipo, int nroJugador)
{
  return MSG_EQUIPO + ((nroEquipo - 1) * cantidadJugadoresEquipo) + nroJugador;
}

int validarGanador(partido* datosThread)
{
  int i;
  int j;
  int golesGanador;
  int intentosGanador;
  int golesequipo;
  int intentosequipo;
  int posicionGanador;
  for (i = 0; i < cantidadEquipos; i++)
  {
    golesequipo = leerGoles(datosThread->memoria, i);
    if (golesequipo >= MAX_GOLES)
    {
      golesGanador = golesequipo;
      intentosGanador = leerIntentos(datosThread->memoria, i);
      posicionGanador = i;
      for (j = 0; j < cantidadEquipos; j++)
      {
        intentosequipo = leerIntentos(datosThread->memoria, j);
        /*Si al menos un equipo no alcanzó la misma cantidad de intentos*/
        if (intentosequipo != intentosGanador)
        {
          return -1;
        }
      }
      return posicionGanador;
    }
  }
  return -1;
}

int partidoAcciones(int opcion, int idColaMensajes, int nroEquipo, int nroJugador)
{
  int evento;
  evento = -1;
  switch (opcion) {
    case AC_PATEAR:
      evento = obtenerNumeroAleatorio(EVENTO_MIN, EVENTO_MAX);
      enviarMensaje(idColaMensajes, calcularDestinoJugador(nroEquipo, nroJugador), MSG_PARTIDO, EVT_PATEAR, "");
      usleep(100 * 1000);
      break;
    default:
      break;
  }
  return evento;
}

void* partidoThread(void* parametro)
{
  mensaje* msg;
  partido* datosThread;
  int opcion;
  int nroEquipo;
  int nroJugador;
  int intentosEquipo;
  int ganador;
  int i;
  int equipoMensaje;

  datosThread = (partido*)parametro;
  opcion = -1;
  nroEquipo = 1;
  nroJugador = 1;
  intentosEquipo = 0;
  ganador = -1;
  equipoMensaje = 0;

  msg = (mensaje*)malloc(sizeof(mensaje));

  intentosEquipo = leerIntentos(datosThread->memoria, 0);
  intentosEquipo++;
  printf("Intento Nº %d\n", intentosEquipo);
  opcion = mostrarMenuPartido(nroEquipo, nroJugador);
  partidoAcciones(opcion, datosThread->idColaMensajes, nroEquipo, nroJugador);

  while(1)
  {
    memset(msg, 0x00, sizeof(mensaje));
    msg->longDest = MSG_NADIE;
    msg->intRte = MSG_NADIE;
    msg->intEvento = EVT_NINGUNO;

    recibirMensajeSinEspera(datosThread->idColaMensajes, MSG_PARTIDO, msg);
    usleep(100 * 1000);

    numequipo = msg->intRte - MSG_EQUIPO;
    strcpy(nomequipo, obtenerNombreequipoPorNumero(numequipo));

    switch(msg->intEvento)
    {
      case EVT_NINGUNO:
        break;
      case EVT_GOL:
        printf("Gol de %s\n", nomequipo);
        for (i = 0; i < cantidadequipoes; i++)
        {
          printf("equipo %s: %d goles\n", obtenerNombreequipoPorNumero(i), leerGoles(datosThread->memoria, i));
        }
        break;
      case EVT_FUERA:
        printf("equipo %s: fuera\n", nomequipo);
        break;
      case EVT_PALO:
        printf("equipo %s: palo\n", nomequipo);
        break;
      case EVT_ATAJA:
        printf("equipo %s: atajado\n", nomequipo);
        break;
      default:
        break;
    }

    if (msg->intEvento != EVT_NINGUNO)
    {
      ganador = validarGanador(datosThread);
      if (ganador >= 0)
      {
        strcpy(nomequipo, obtenerNombreequipoPorNumero(ganador));
        printf("equipo %s: ganó el partido con %d goles\n", nomequipo, leerGoles(datosThread->memoria, ganador));
        for (i = 0; i < cantidadequipoes; i++)
        {
          escribirFinPartido(datosThread->memoria, i, 1);
          usleep(100 * 1000);
        }
        break;
      }

      equipoMensaje = 0;
      for(i = 0; i < cantidadequipoes; i++)
      {
        if (leerIntentos(datosThread->memoria, equipoMensaje) > leerIntentos(datosThread->memoria, i))
        {
          equipoMensaje = i;
        }
      }

      intentosequipo = leerIntentos(datosThread->memoria, equipoMensaje);
      strcpy(nomequipo, obtenerNombreequipoPorNumero(equipoMensaje));
      intentosequipo++;
      printf("Intento Nº %d\n", intentosequipo);
      opcion = mostrarMenuPartido(nomequipo);
      partidoAcciones(opcion, datosThread->idColaMensajes, equipoMensaje);
    }

    usleep(INTERVALO_PARTIDO_MS * 1000);
  }
  free(msg);
  return 0;
}
