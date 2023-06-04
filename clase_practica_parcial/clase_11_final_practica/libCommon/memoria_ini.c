/*Standard Library*/
#include "stdio.h"
/*Headers Library*/
#include "libCommon/memoria.h"
#include "libCommon/pantalla.h"
/*File Header*/
#include "memoria_ini.h"

inicial* crearMemoriaInicial(int* extIdMemoria)
{
  return (inicial*)crearMemoriaConClave(sizeof(inicial), idMemoriaInicial, CLAVE_BASE_INI);
}

void configurarMemoriaInicial(inicial* memoria)
{
  memoria[POS_INI_MEM].inicializado = 1;
}

void verificarMemoriaInicial(inicial* memoria, char* nombrePrograma)
{
  while (memoria[POS_INI_MEM].inicializado != 1)
  {
    printf("Atención: Recuerde levantar el programa inicial \"%s\". Presione \"enter\" para continuar...\n", nombrePrograma);
    getchar();
  }
}
