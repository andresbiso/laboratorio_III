#ifndef _THREAD_ARBITRO_H
#define _THREAD_ARBITRO_H
/*Headers Library*/
#include "libCore/memoria_core.h"
struct tipo_arbitro
{
  int idColaMensajes;
  dato_memoria* memoria;
};
typedef struct tipo_arbitro arbitro;
void* arbitroThread(void*);
void arbitroAcciones(int, int, int);
#endif
