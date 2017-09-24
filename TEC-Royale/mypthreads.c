//los hilos en el user space son llamados fibers
//los hilos en el kernel space son llamados threads
//solo un thread puede modificar un recurso compartido a la vez
//solo un fiber puede ser ejecutado a la vez

#define _GNU_SOURCE /* Para que funcione sched.h */
#include "mypthreads.h"
#include <sched.h> /* For clone */
#include <signal.h> /* For SIGCHLD */
#include <stdlib.h>
#include <sys/types.h> /* For pid_t */
#include <sys/wait.h> /* For wait */
#include <unistd.h> /* For getpid */

//clone es un system call, es como se crea los hilos
//la senial que se enviara cuando el hilo exista es SIGCHLD
//wait regresa (return) cuando un hilo exista


/* 
 * Contiene la informacion individual de cada hilo
 */
typedef struct
{
	pid_t pid; /* El pid del hilo hijo */
	void* stack; /* Puntero de la pila */
} thread;

struct ThreadArguments {
	void (*function)();
};

/* Cola de hilos */
static thread threadList[ MAX_THREADS ];
/* El pid del proceso padre */
static pid_t parentPid;
/* el numero de hilos activos */
static int numThread = 0;

/* 
 * Crea los hilos con valores nulos (0) 
 */
void my_thread_create()
{
	int i;
	for ( i = 0; i < MAX_THREADS; ++ i )
	{
		threadList[i].pid = 0;
		threadList[i].stack = 0;
	}
	
	parentPid = getpid();
}

/* 
 * Llama al system call sched_yield que mueve el proceso actual al fina
 * de la cola de procesos
 */
void my_thread_yield()
{
	sched_yield();
}
/*
struct ThreadArguments {
	void (*function)();
};
*/

/* Exists to give the proper function type to clone. */
/*
 * Aun no lo he usado
 */
static int threadStart( void* arg )
{
	struct ThreadArguments* arguments = (struct ThreadArguments*) arg;
	void (*function)() = arguments->function;
	free( arguments );
	arguments = NULL;

	LF_DEBUG_OUT1( "Hilo hijo creado y llamando funcion = %p", arg );
	function();
	return 0;
}

/*
 * Asocia una funcion con un hilo ya creado
 */
int my_thread_join( void (*func)(void) )
{
	struct ThreadArguments* arguments = NULL;
	
	//si no hay mas hilos libres, no se asocia
	if ( numThread == MAX_THREADS ) return LF_MAXTHREADS;

	// ubicar en la pila
	threadList[numThread].stack = malloc( THREAD_STACK );
	
	//Si no se logra ubicar en la pila
	if ( threadList[numThread].stack == 0 )
	{
		LF_DEBUG_OUT( "Error: No se pudo ubicar en la pila." );
		return LF_MALLOCERROR;
	}

	// crear la estructura de los argumentos
	arguments = (struct ThreadArguments*) malloc( sizeof(*arguments) );
	
	//si no se logra crear
	if ( arguments == 0 ) {
		free( threadList[numThread].stack );
		LF_DEBUG_OUT( "Error: No se pudo ubicar los argumentos del hilo." );
		return LF_MALLOCERROR;
	}
	
	//func es el parametro de esta funcion
	arguments->function = func;

	//llama al system call "clone", el cual crea el HILO HIJO
	threadList[numThread].pid = clone( &threadStart, (char*) threadList[numThread].stack + THREAD_STACK,
		SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, arguments );
		
	//clone retorna -1 si no logra creal el hilo hijo
	if ( threadList[numThread].pid == -1 )
	{
		free( threadList[numThread].stack );
		free( arguments );
		LF_DEBUG_OUT( "Error: Fallos del system call \"clone\"." );
		return LF_CLONEERROR;
	}
	
	numThread ++;
	
	return LF_NOERROR;
}

/*
 * Espera por todos los hilos para salir.
 * Libera los recursos asociados a cada uno.
 */
int my_thread_end()
{
	pid_t pid;
	int i;
	int threadsRemaining = 0;
		
	//revisa si estamos en un hilo, si no entonces no se ejecuta la funcion
	pid = getpid();
	if ( pid != parentPid ) return LF_INTHREAD;			
		
	//espera por los hilos para salir, luego se libera la pila
	while ( numThread > threadsRemaining )
	{
		pid = wait( 0 );
		if ( pid == -1 )
		{
			LF_DEBUG_OUT( "Error: Fallos del system call \"wait\"." );
			exit( 1 );
		}
		
		/* Find the fiber, free the stack, and swap it with the last one */
		//busca el hilo, libera la pila, y este se cambia con el ultimo hilo
		for ( i = 0; i < numThread; ++ i )
		{
			if ( threadList[i].pid == pid )
			{
				LF_DEBUG_OUT1( "Pid del hilo hijo = %d, salio", pid );
				numThread--;
				
				free( threadList[i].stack );
				
				if ( i != numThread )
				{
					threadList[i] = threadList[numThread];
				}
				
				i = -1;
				break;
			}
		}
		if ( i == numThread )
		{
			LF_DEBUG_OUT1( "No se encontro el pid del hilo hijo = %d en la lista de los hilos", pid ); 
		}
	}
	
	return LF_NOERROR;
}
