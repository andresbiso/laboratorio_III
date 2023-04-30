#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "defines.h"
#include "semaforos.h"
#include "funciones.h"

int main(int argc, char *argv[])
{
  if (argc != 1)
  {
    printf("Uso: ./dos \n");
    return 0;
  }

  printf("Atención: Recuerde levantar el programa incial \"uno\". Presione \"enter\" para continuar...");
  getchar();
  limpiarPantalla();

  return 0;
}
