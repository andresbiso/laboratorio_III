#include "stdio.h"
#include "gestionararchivos.h"

void abrirArchivo(char* ruta, char* mode, FILE* fp)
{
        fp = fopen(ruta, mode);
}

void cerrarArchivo(FILE* fp)
{
        fclose(fp);
}
