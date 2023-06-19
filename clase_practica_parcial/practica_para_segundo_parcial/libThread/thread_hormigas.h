#ifndef _THREAD_HORMIGAS_H
#define _THREAD_HORMIGAS_H
/*Headers Library*/
#include "libCore/memoria_core.h"
struct tipo_hormiga
{
  int idColaMensajes;
  dato_memoria* memoria;
  /*custom*/
  int nroHormiga;
};
typedef struct tipo_hormiga hormiga;
void* hormigasThread(void*);
#endif
