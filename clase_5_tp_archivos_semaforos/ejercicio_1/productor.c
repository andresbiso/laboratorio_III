#include "stdio.h"
#include "string.h"
#include "defines.h"
#include "gestionararchivos.h"
#include "productor.h"

void escribirReservas()
{
  int numVuelo;
  char pasajero[32+1];
  char destino[32+1];
  char reserva[100+1];
  numVuelo = -1;
  while(numVuelo != 0 && (numVuelo < NUM_VUELO_MIN || numVuelo > NUM_VUELO_MAX))
  {
    printf("Ingrese número de vuelo (1000-1010) o '0' para finalizar:");
    scanf("%d",&numVuelo);
  }

  memset(pasajero,0x00,sizeof(pasajero));
  memset(destino,0x00,sizeof(destino));
  memset(reserva,0x00,sizeof(reserva));
 
  while(numVuelo != 0)
  {
    strcpy(destino, obtenerDestino(numVuelo));
    printf("Ingrese Nombre del Pasajero para vuelo %d:\n", numVuelo);
    scanf("%s",pasajero);
    sprintf(reserva,"Vuelo %04d\nDESTINO %s\nNOMBRE %s\n",numVuelo,destino,pasajero);    
    escribirArchivo(reserva);
    memset(pasajero,0x00,sizeof(pasajero));
    memset(destino,0x00,sizeof(destino));
    memset(reserva,0x00,sizeof(reserva));
    printf("Ingrese número de vuelo (1000-1010) o '0' para finalizar:");
    scanf("%d",&numVuelo);
  }
}

char* obtenerDestino(int numVuelo)
{
  switch(numVuelo)
  {
    case 1000:
      return "SEATTLE";
    case 1001:
      return "HELSINKI";
    case 1002:
      return "DENVER";
    case 1003:
      return "DUBLIN";
    case 1004:
      return "MONACO";
    case 1005:
      return "SAO PAULO";
    case 1006:
      return "HOUSTON";
    case 1007:
      return "TOKYO";
    case 1008:
      return "BUENOS AIRES";
    case 1009:
      return "MONTEVIDEO";
    case 1010:
      return "VANCOUVER";
    default:
      return "";
  }
}



