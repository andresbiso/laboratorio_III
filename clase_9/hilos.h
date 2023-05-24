#ifndef _HILOS_H
#define _HILOS_H
#include "pthread.h"
void iniciarMutex(pthread_mutex_t*);
void iniciarAttr(pthread_attr_t*);
void joinThread(pthread_t*);
void lockMutex(pthread_mutex_t*);
void unlockMutex(pthread_mutex_t*);
void* funcionThread(void*);
int crearThread(pthread_t*, pthread_attr_t*, void*);
#endif
