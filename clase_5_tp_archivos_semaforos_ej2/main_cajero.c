#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "time.h"
#include "defines.h"
#include "gestionararchivos.h"
#include "semaforos.h"
#include "funciones.h"
#include "consumidor.h"

int main(int argc, char *argv[])
{
  int idSemaforoCajero;
  int cajeroElegido;
  char* rutaArchivo;

  if (argc != 2)
  {
    printf("Uso: ./cajero [1-3]\n");
    return 0;
  }

	cajeroElegido = atoi(argv[1]);
  
  srand(time(0));
  rutaArchivo = (char*)malloc((LARGO_RUTA+1)*sizeof(char));
  memset(rutaArchivo,0x00,sizeof(rutaArchivo));

  strcpy(rutaArchivo, obtenerRutaArchivoPanel(panelElegido));

  idSemaforoCajero = creoSemaforo();

  while(1)
  {
    /*printf("PANEL: Esperando Acceso...\n");*/
    esperaSemaforo(idSemaforoPanel);
    if (abrirLectura(rutaArchivo))
    {
      printf("PANEL: Hubo un error al querer abrir el archivo\n");
      levantaSemaforo(idSemaforoPanel);
      usleep(INTERVALO_CCI_MS*10000);
      esperaSemaforo(idSemaforoPanel);
    }

    cerrarArchivo();
    levantaSemaforo(idSemaforoPanel);
    usleep(INTERVALO_PANEL_MS * 1000);
  }
  free(rutaArchivo);
  free(mensajeActual);
  return 0;
}
