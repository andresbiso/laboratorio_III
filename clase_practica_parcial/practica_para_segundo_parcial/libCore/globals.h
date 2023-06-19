#ifndef _GLOBALS_H
#define _GLOBALS_H
/*Standard Library*/
#include "pthread.h"
/*Message Queue*/
enum destinos
{
  MSG_NADIE, /*0*/
  MSG_REINA,
  MSG_HORMIGA
};
enum eventos
{
  EVT_NINGUNO, /*0*/
  EVT_JUNTAR_COMIDA,
  EVT_JUNTAR_COMIDA_FIN,
  EVT_JUNTAR_HOJA,
  EVT_JUNTAR_HOJA_FIN,
  EVT_JUNTAR_RAMA,
  EVT_JUNTAR_RAMA_FIN,
  EVT_JUNTAR_AGUA,
  EVT_JUNTAR_AGUA_FIN,
  EVT_FIN_HORMIGA
};
typedef enum destinos Destinos;
typedef enum eventos Eventos;
/*Shared Global Variables*/
extern pthread_mutex_t mutex;
extern int cantidadHormigas;
#endif
