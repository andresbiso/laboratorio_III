/*Standard Library*/
#include <stdio.h>
/*Headers Library*/
#include "libCommon/pantalla.h"
/*File Header*/
#include "menus.h"

int mostrarMenuPartido(char* nombreequipo)
{
    int tecla;
    tecla = 0;
    while(tecla != TECLA_ENTER)    
    {
      printf("equipo %s\n", nombreequipo);
      tecla = solicitarCaracter("Presione [Enter] para patear al arco");
    }
    return AC_PATEAR;
}
