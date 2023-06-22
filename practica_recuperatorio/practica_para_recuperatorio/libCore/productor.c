/*Standard Library*/
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
/*Headers Library*/
#include "libCommon/archivos.h"
#include "defines.h"
#include "globals.h"
#include "funciones.h"
#include "menus.h"
/*File Header*/
#include "productor.h"

void escribirOrden(comida* nuevaOrden, int numComida)
{
  char* lineaOrden;
  lineaOrden = (char*)malloc((LARGO_LINEA+1)*sizeof(char));
  memset(lineaOrden,0x00,sizeof(lineaOrden));
  sprintf(lineaOrden , FORMATO_OUTPUT, numComida, nuevaOrden->precio, nuevaOrden->descripcion);
  escribirArchivo(lineaOrden);
  printf(FORMATO_MENU, numComida, nuevaOrden->precio, nuevaOrden->descripcion);
  free(lineaOrden);
}
