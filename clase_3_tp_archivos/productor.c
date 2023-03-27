#include "stdio.h"
#include "string.h"
#include "defines.h"
#include "gestionararchivos.h"

int main(int argc, char *argv[]) {  int cantProd;
  int i;
  char nom[32+1];
  FILE *cfptr;
  memset(nom,0x00,sizeof(nom));
  if (abrirArchivo(RUTA_ARCHIVO_PRODUCTO,"w",&cfptr))
  {
    printf("Hubo un error al querer abrir el archivo\n");
  }
  else
  {
    printf("Ingrese cantidad de productos:");
    scanf("%d",&cantProd);
    i = 1;
    while(i <= cantProd)
    {
      printf("Ingrese Nombre del Producto %d:\n", i);
      scanf("%s",nom);
      fprintf(cfptr,"PRODUCTO-%02d %s %d\n",i,nom,UNIDADES_LOTE);
      memset(nom,0x00,sizeof(nom));
      i++;
    }
  }  cerrarArchivo(cfptr);
  return 0;
}


