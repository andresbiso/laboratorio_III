#include "gestionararchivos.h"
#include "stdio.h"


void abrirArchivo(char* ruta, char* mode, FILE* fp)
{
        fp = fopen(ruta, mode);
}

void cerrarArchivo(FILE* fp)
{
        fclose(fp);
}
