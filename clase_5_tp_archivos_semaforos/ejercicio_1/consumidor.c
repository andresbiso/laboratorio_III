#include "stdio.h"
#include "string.h"
#include "defines.h"
#include "funciones.h"
#include "gestionararchivos.h"

void leerReservas()
{
  char reserva[100+1];
  memset(reserva,0x00,sizeof(reserva));
  printf("Los productos ingresados son:\n");
  while(!esFinArchivo())
  {
    leerArchivo(reserva);

    if (strstr(reserva, "1000")!=0)
    {
      
    }
    printf("VUELO DESTINO PASAJEROS\n");
    printf("%s\n",producto);
    memset(reserva,0x00,sizeof(producto));
  }
}
