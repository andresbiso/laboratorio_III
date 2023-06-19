/*Standard Library*/
#include "stdio.h"
/*File Header*/
#include "menus.h"

int mostrarMenuReina(int numeroHormiga)
{
    int opcion;
    opcion = -1;

    while((opcion <= AC_NINGUNA) || (opcion >= AC_MAX))    
    {
      printf("Hormiga %d\n", numeroHormiga);
      printf("Menu\n\n");
      printf("1.\tJuntar Comida\n");
      printf("2.\tJuntar Hoja\n");
      printf("3.\tJuntar Rama\n");
      printf("4.\tJuntar Agua\n\n");
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
