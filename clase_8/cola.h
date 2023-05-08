#ifndef _MEMORIA_H
#define _MEMORIA_H
#include "defines.h"
struct tipo_mensaje
{
  long longDest; /*Destinatario*/
  int intRte; /*Remitente*/
  int intEvento; /*NroEvento*/
  char charMensaje[LARGO_MENSAJE]; /*Mensaje*/
};
typedef struct tipo_mensaje mensaje;
void* crearColaMensajes(int);
void borrarMensajes(int);
void recibirMensaje(int, long, mensaje*);
void enviarMensaje(int, long, int, int, char*);
#endif
