#ifndef MYPTHREADS_H
#define MYPTHREADS_H 1

#define	LF_NOERROR	0
#define	LF_MAXTHREADS	1
#define LF_MALLOCERROR	2
#define LF_CLONEERROR	3
#define	LF_INTHREAD	4
#define LF_SIGNALERROR	5

#ifdef LF_DEBUG

#include <stdio.h>
#define LF_DEBUG_OUT( string ) fprintf( stderr, "mypthreads debug: " string "\n")
#define LF_DEBUG_OUT1( string, arg ) fprintf( stderr, "mypthreads debug: " string "\n", arg )

#else

#define LF_DEBUG_OUT( string )
#define LF_DEBUG_OUT1( string, arg )

#endif

//MAXIMO DE HILOS QUE PUEDEN ESTAR ACTIVOS A LA VEZ
#define MAX_THREADS 10
//TAMANIO DE LA PILA POR CADA HILO
#define THREAD_STACK (1024*1024)


extern void my_thread_create();

extern int my_thread_join( void (*func)(void) );

extern void my_thread_yield();

extern int my_thread_end();

/* Define VALGRIND to include valgrind specific code */
#ifdef VALGRIND
#include <valgrind/valgrind.h>
#else
#define VALGRIND_STACK_REGISTER(start, end) (0)
#define VALGRIND_STACK_DEREGISTER(id)
#endif

#endif
