/*Standard Library*/
#include <stdio.h>
/*Headers Library*/
#include "libCommon/pantalla.h"
/*File Header*/
#include "menus.h"

int mostrarMenuPartido(int nroEquipo, int nroJugador)
{
    int tecla;
    tecla = 0;
    while(tecla != TECLA_ENTER)    
    {
      printf("equipo %d: jugador %d\n", nroEquipo, nroJugador);
      tecla = solicitarCaracter("Presione [Enter] para patear al arco");
    }
    return AC_PATEAR;
}
