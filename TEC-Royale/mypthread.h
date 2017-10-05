#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <mutex.h>
#include <string.h>

#ifndef MYTHREAD_H
#define MYTHREAD_H

#define FALSE 0
#define TRUE 1

#define RUNNING 0
#define READY 	1 //espera para ser agendado (scheduling)
#define BLOCKED 2 //esperando unirse
#define DEFUNCT 3 //muerto

typedef struct mythread_attr {
	//valor por defecto: SIGSTKSZ
	unsigned long stackSize;
}mythread_attr_t;

typedef struct mythread {
	pid_t tid;
}mythread_t;

/*
 * Thread Control Block (TCB)
 */
typedef struct mythread_private {

	pid_t tid; 				
	int state; 				
	//funcion donde esta asignado el hilo
	void * (*start_func) (void *);
	//argumentos de la funcion
	void *args; 				
	//valor de retorno de la funcion
	void *returnValue; 			
	struct mythread_private *blockedForJoin;
	//mutex utilizado por el despachador para programar este hilo
	struct mutex sched_mutex;
	struct mythread_private *prev, *next; 

}mythread_private_t;

//puntero a la cabeza de la cola
extern mythread_private_t *mythread_q_head;

mythread_t mythread_self(void);

/*
 * Prepara el contexto de un nuevo hilo, attr se ignora por el momento
 */
int mythread_create(mythread_t *new_thread_ID,
					mythread_attr_t *attr,
					void * (*start_func)(void *),
					void *arg);

/*
 * cambia de un hilo ejecutandose a otro que este listo para ejecutarse (READY)
 */
int mythread_yield(void);


/*
 * suspende la llamada del hilo si el hilo actual no ha terminado,
 * en cola el hilo actual, luego dispatch y lo marca como ready para
 * volver a ser llamado
*/
int mythread_join(mythread_t target_thread, void **status);

/*
 * desencola un hilo y lo mata
 */
void mythread_end(void *retval);

pid_t __mythread_gettid();

mythread_private_t *__mythread_selfptr();

int my_thread_detach(mythread_private_t *);

void __mythread_debug_futex_init();

/*
 * Solo se usa con el debuguer
 */
extern char debug_msg[1000];
extern struct mutex debug_futex;

#ifdef DEBUG
#define DEBUG_PRINTF(...) __mythread_debug_futex_init(); \
			mutex_down(&debug_futex); \
			sprintf(debug_msg, __VA_ARGS__); \
			write(1, debug_msg, strlen(debug_msg)); \
			mutex_up(&debug_futex);
#else
#define DEBUG_PRINTF(...) do {} while(0);
#endif

#define ERROR_PRINTF(...) __mythread_debug_futex_init(); \
			mutex_down(&debug_futex); \
			sprintf(debug_msg, __VA_ARGS__); \
			write(1, debug_msg, strlen(debug_msg)); \
			mutex_up(&debug_futex);

#define LOG_PRINTF(...) __mythread_debug_futex_init(); \
			mutex_down(&debug_futex); \
			sprintf(debug_msg, __VA_ARGS__); \
			write(1, debug_msg, strlen(debug_msg)); \
			mutex_up(&debug_futex);

#endif /* MYTHREAD_H */
