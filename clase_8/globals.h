#ifndef _GLOBALS_H
#define _GLOBALS_H
#include "defines.h"
struct tipo_inicial
{
  int inicializado;
};
struct tipo_dato
{
  char nombreJugador[LARGO_NOMBRE]; /*nombreJugador[LARGO_NOMBRE]*/
  int numeroPensado; /*0:sin número; 1-99:número a verificar*/
  int estadoAcierto; /*0:no acierto;1: acierto*/
};
enum destinos
{
  MSG_NADIE /*0*/
};
enum eventos
{
  EVT_NINGUNO /*0*/
};
typedef struct tipo_dato dato;
typedef struct tipo_inicial inicial;
typedef enum destinos Destinos;
typedef enum eventos Eventos;
#endif
