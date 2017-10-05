#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mypthread.h>

//numero de hilos, se puede definir desde una funcion
#define NTHREADS	8

/*
 * aumenta el contador en 50,
 * cuando tiene el control de regreso le suma otros 50 y sale
 */
void *thread_func(void *arg)
{
	int *count = (int *)arg;

	*count = *count + 50;
	LOG_PRINTF("Thread %ld: Incremented count by 50 and will now yield\n", (unsigned long)mythread_self().tid);
	mythread_yield();
	*count = *count + 50;
	LOG_PRINTF("Thread %ld: Incremented count by 50 and will now exit\n", (unsigned long)mythread_self().tid);
	mythread_end(NULL);
	return NULL;
}

/*
 * ejemplo de uso de la biblioteca
 */
int main()
{
	mythread_t threads[NTHREADS];
	int count[NTHREADS];
	int i;
	char *status;

	for (i = 0; i < NTHREADS; i++) {
		count[i] = i;
		mythread_create(&threads[i], NULL, thread_func, &count[i]);
	}
	for (i = 0; i < NTHREADS; i++) {
		LOG_PRINTF("Main: Will now wait for thread %ld. Yielding..\n", (unsigned long)threads[i].tid);
		mythread_join(threads[i], (void **)&status);
		LOG_PRINTF("Main: Thread %ld exited and increment count to %d\n", (unsigned long)threads[i].tid, count[i]);
	}
	LOG_PRINTF("Main: All threads completed execution. Will now exit..\n");
	mythread_end(NULL);

	return 0;
}
