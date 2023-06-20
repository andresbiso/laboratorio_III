#ifndef _THREAD_JUGADOR_H
#define _THREAD_JUGADOR_H
/*Headers Library*/
#include "libCore/memoria_core.h"
struct tipo_jugador
{
  int idColaMensajes;
  dato_memoria* memoria;
  /*custom*/
  int nroJugador;
  int recursoComida;
  int recursoHoja;
  int recursoRama;
  int recursoAgua;
};
typedef struct tipo_jugador jugador;
void* jugadorThread(void*);
#endif
