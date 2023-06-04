#ifndef _THREAD_JUGADORES_H
#define _THREAD_JUGADORES_H
struct tipo_jugador
{
  int idColaMensajes;
  int idSemaforo;
  int idMemoria;
  /*custom*/
  int nroJugador;
};
typedef struct tipo_jugador jugador;
void* jugadoresThread(void*);
#endif
