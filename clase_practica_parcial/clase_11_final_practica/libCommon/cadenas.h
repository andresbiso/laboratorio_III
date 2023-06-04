#ifndef _CADENAS_H
#define _CADENAS_H
#define DELIMITADOR_BASE "|"
char letraMayuscula(char);
char letraMinuscula(char);
void cadenaMayuscula(char*, char*);
void cadenaMinuscula(char*, char*);
void unirCadenas(char*, char*);
void unirCadenasConDelimitador(char*, char*, char*);
void separarCadenaConDelimitador(char*, char*);
int contarSeparacionesCadena(char*, char*);
#endif
