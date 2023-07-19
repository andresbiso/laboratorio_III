#ifndef _GLOBALS_H
#define _GLOBALS_H
/*Standard Library*/
#include <pthread.h>
/*Message Queue*/
enum destinos
{
  MSG_NADIE, /*0*/
  MSG_PARTIDO,
  MSG_EQUIPO
};
enum eventos
{
  EVT_NINGUNO, /*0*/
  EVT_PATEAR,
  EVT_GOL,
  EVT_FUERA
};
typedef enum destinos Destinos;
typedef enum eventos Eventos;
/*Shared Global Variables*/
extern pthread_mutex_t mutex;
extern int cantidadEquipos;
extern int cantidadJugadoresEquipo;
#endif
