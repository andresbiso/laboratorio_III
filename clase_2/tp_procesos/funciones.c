#include "funciones.h"
#include "stdlib.h"
#include "stdio.h"

int obtenerNumeroAleatorio(int desde, int hasta) {
	int num = 0;
	num = (rand()%(hasta-desde+1))+desde;
	return num;
}

int* obtenerNumerosAleatorios(int desde, int hasta, int tamanio) {
	int i;
	int* nums;
	nums = malloc(tamanio * sizeof(int));
	for (i = 0; i < tamanio; i++)
	{
		int valor = (rand()%(hasta-desde+1))+desde;
		nums[i] = valor;
	}
	return nums;
}
