#ifndef _MEMORIA_CORE_H
#define _MEMORIA_CORE_H
#define CLAVE_BASE_INI 34
struct tipo_inicial
{
  int inicializado;
};
typedef struct tipo_inicial inicial;
void configurarMemoriaInicial(inicial*);
void verificarMemoriaInicial(inicial*);
#endif
