#ifndef _MEMORIA_CORE_H
#define _MEMORIA_CORE_H
#define CLAVE_BASE_INI 34
struct tipo_dato_memoria_ini
{
  int inicializado;
  int finalizado;
};
typedef struct tipo_dato_memoria_ini dato_memoria_ini;
void configurarMemoriaIni(dato_memoria_ini*);
void verificarMemoriaIni(dato_memoria_ini*);
void configurarFinalizarMemoriaIni(dato_memoria_ini*);
void verificarFinalizarMemoriaIni(dato_memoria_ini*, char*);
#endif
