/*Standard Library*/
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
/*Headers Library*/
#include "libCommon/archivos.h"
#include "libCore/defines.h"
/*File Header*/
#include "consumidor.h"

void leerLineas()
{
  char* linea;
  char caracter;
  int valorNumerico;

  memset(&caracter,0x00,sizeof(caracter));

  linea = (char*)malloc((LARGO_LINEA)*sizeof(char));
  memset(linea,0x00,sizeof(linea));
  while(leerLineaArchivo(linea) != 0)
  {
    sscanf(linea, FORMATO_OUTPUT_ARCHIVO, &caracter, &valorNumerico);
    printf(FORMATO_OUTPUT_PANTALLA, caracter, valorNumerico);
  
    memset(linea,0x00,sizeof(linea));
    memset(caracter,0x00,sizeof(caracter));
  }
  free(linea);
  free(caracter);
}
