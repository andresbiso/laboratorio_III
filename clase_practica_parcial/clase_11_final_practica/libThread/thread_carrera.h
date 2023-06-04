#ifndef _THREAD_CARRERA_H
#define _THREAD_CARRERA_H
struct tipo_tablero
{
  int idColaMensajes;
  int idSemaforo;
  int idMemoria;
};
typedef struct tipo_tablero tablero;
void* carreraThread(void*);
#endif
