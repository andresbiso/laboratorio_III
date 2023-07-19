#ifndef _THREAD_EQUIPO_H
#define _THREAD_EQUIPO_H
/*Headers Library*/
#include "libCore/defines.h"
#include "libCore/memoria_core.h"
struct tipo_equipo
{
  int idColaMensajes;
  dato_memoria* memoria;
  /*custom*/
  int nroJugador;
  int nroEquipo;
};
typedef struct tipo_equipo equipo;
void* equipoThread(void*);
#endif
