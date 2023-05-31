/*Standard Library*/
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
/*Headers Library*/
#include "defines.h"
#include "globals.h"
#include "funciones.h"
/*File Header*/
#include "productor.h"

void iniciarMemoriaInicial(inicial* memoria)
{
  memoria[POS_INI_MEM].inicializado = 1;
}
