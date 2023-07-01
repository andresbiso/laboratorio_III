/*Standard Library*/
#include <stdio.h>
/*File Header*/
#include "menus.h"

int mostrarMenuPartido(char* nombreJugador)
{
    int tecla;
    tecla = 0;
;
    while(tecla != TECLA_ENTER)    
    {
      printf("Jugador %s\n", nombreJugador);
      printf("Presione [Enter] para patear al arco\n");
      tecla = getchar();
    }
    return AC_PATEAR;
}
