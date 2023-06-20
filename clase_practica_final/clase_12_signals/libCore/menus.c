/*Standard Library*/
#include "stdio.h"
/*File Header*/
#include "menus.h"

int mostrarMenuPartido(char* nombreJugador)
{
    int opcion;
    opcion = -1;

    while((opcion <= AC_NINGUNA) || (opcion >= AC_MAX))    
    {
      printf("Jugador %d\n", nombreJugador);
      printf("Menu\n");
      printf("1.Patear al arco\n");
      printf("Ingresar Opcion:\n");
      if ((scanf("%d", &opcion) != 1)
        || (opcion <= AC_NINGUNA)
        || (opcion >= AC_MAX))
      {
        printf("Opcion Invalida!\n");
      }
    }
    return opcion;
}
