#include "stdio.h"
#include "string.h"
#include "defines.h"
#include "gestionararchivos.h"

int main(int argc, char *argv[]) {
  char producto[32+1];
  char nom[32+1];
  int lote;
  FILE *cfptr;
  memset(nom,0x00,sizeof(nom));
  memset(producto,0x00,sizeof(producto));
	printf("Los productos ingresados son:\n");
  if ((cfptr=fopen(RUTA_ARCHIVO_PRODUCTO,"r"))==NULL)
  {
    printf("Hubo un error al querer abrir el archivo\n");
  }
  else
  {
    while(!feof(cfptr))
    {
      fscanf(cfptr,"%s %s %d\n",producto,nom,&lote);
      printf("%s Nombre:%s Cantidad:%d\n",producto,nom,lote);
      memset(nom,0x00,sizeof(nom));
      memset(producto,0x00,sizeof(producto));
    }
  }
  fclose(cfptr);
	return 0;
}
