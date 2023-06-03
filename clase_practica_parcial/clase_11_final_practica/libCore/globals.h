#ifndef _GLOBALS_H
#define _GLOBALS_H
/*Standard Library*/
#include "pthread.h"
struct tipo_jugador
{
  int nroJugador;
  int cantidadPasos;
  int intervalo;
};
typedef struct tipo_jugador jugador;
enum destinos
{
  MSG_NADIE, /*0*/
  MSG_CARRERA,
  MSG_JUGADOR
};
enum eventos
{
  EVT_NINGUNO, /*0*/
  EVT_CAMINAR,
  EVT_PASO,
  EVT_DESCANSO,
  EVT_FIN
};
typedef enum destinos Destinos;
typedef enum eventos Eventos;
extern pthread_mutex_t mutex;
#endif
