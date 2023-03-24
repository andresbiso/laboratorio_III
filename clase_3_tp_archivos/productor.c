#include "stdio.h"
#include "defines.h"
#include "gestionararchivos.h"

int main(int argc, char *argv[]) {
	FILE* fp;	
	fp = 0;
	abrirArchivo(RUTA_PRODUCTO, "w", fp);
	if (fp == 0)
	{
		printf("Error al querer abrir el archivo %s", RUTA_PRODUCTO);
	}
	return 0;
}
