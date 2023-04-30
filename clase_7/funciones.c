#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "defines.h"
#include "funciones.h"

int obtenerNumeroAleatorio(int desde, int hasta) {
	int num = 0;
	num = (rand()%(hasta-desde+1))+desde;
	return num;
}

void obtenerNumerosAleatorios(int desde, int hasta, int tamanio, int* nums) {
	int i;
	for (i = 0; i < tamanio; i++)
	{
		int valor = (rand()%(hasta-desde+1))+desde;
		nums[i] = valor;
	}
}

void limpiarPantalla()
{
  int i;
  i = 0;
  while (i<LINEAS_PANTALLA)
  {
    printf("\n");
    i++;
  }
}

char letraMayuscula(char valor)
{
  const int delta = 'a' - 'A';
  /* Devuelve 32 en decimal
  que es la diferencia entre 'a'
  que es en ASCII decimal 97
  y 'A' que es en ASCII decimal 65 */
  if (valor <= 'z' && valor >= 'a')
  {
    valor -= delta;
  }
  return valor;
}

char letraMinuscula(char valor)
{
  const int delta = 'a' - 'A';
  /* Devuelve 32 en decimal
  que es la diferencia entre 'a'
  que es en ASCII decimal 97
  y 'A' que es en ASCII decimal 65 */
  if (valor >= 'A' && valor <= 'Z')
  {
    valor += delta;
  }
  return valor;
}

char* cadenaMayuscula(char* cadena)
{
  int largo;
  int i;
  char* cadenaMayusc;
  largo = strlen(cadena);
  cadenaMayusc = (char*)malloc((largo+1)*sizeof(char));
  memset(cadenaMayusc,0x00,sizeof(cadenaMayusc));
  cadenaMayusc[largo] = '\0';
  for (i = 0; i < largo; i++)
  {
    cadenaMayusc[i] = letraMayuscula(cadena[i]);
  }
  return cadenaMayusc;
}

char* cadenaMinuscula(char* cadena)
{
  int largo;
  int i;
  char* cadenaMinusc;
  largo = strlen(cadena);
  cadenaMinusc = (char*)malloc((largo+1)*sizeof(char));
  memset(cadenaMinusc,0x00,sizeof(cadenaMinusc));
  cadenaMinusc[largo] = '\0';
  for (i = 0; i < largo; i++)
  {
    cadenaMinusc[i] = letraMinuscula(cadena[i]);
  }
  return cadenaMinusc;
}
