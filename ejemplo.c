#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <mypthread.h>

//numero de hilos, se puede definir desde una funcion
//#define NTHREADS	8
#define NOT_RT		-1

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

void *server(void *arg){
  int welcomeSocket, newSocket;
  char buffer[1024];
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;

  /*---- Create the socket. The three arguments are: ----*/
  /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);
  
  /*---- Configure settings of the server address struct ----*/
  /* Address family = Internet */
  serverAddr.sin_family = AF_INET;
  /* Set port number, using htons function to use proper byte order */
  serverAddr.sin_port = htons(7891);
  /* Set IP address to localhost */
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  /* Set all bits of the padding field to 0 */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  /*---- Bind the address struct to the socket ----*/
  bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

  /*---- Listen on the socket, with 5 max connection requests queued ----*/
  if(listen(welcomeSocket,5)==0)
    printf("Listening\n");
  else
    printf("Error\n");

  /*---- Accept call creates a new socket for the incoming connection ----*/
  addr_size = sizeof serverStorage;
  

  while (1){
	  newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
	   /*---- Read the message from the server into the buffer ----*/
	  recv(newSocket, buffer, 1024, 0);

  /*---- Print the received message ----*/
	  printf("Data received: %s",buffer);   

  }
  return NULL;
}
/*
 * ejemplo de uso de la biblioteca
 *//*
int main(int argc, char *argv[])
{
	mythread_t threads[NTHREADS];
	int count[NTHREADS];
	int i;
	char *status;
	
	my_thread_init();

	for (i = 0; i < NTHREADS; i++) {
		count[i] = i;
		mythread_create(&threads[i], NULL, thread_func, &count[i], NOT_RT);
	}*/
	
	//ejemplo para probar tiempo real
	//mythread_create(&threads[0], NULL, server, &count[0], 8);
	//mythread_create(&threads[1], NULL, thread_func, &count[1], 4);
	//mythread_create(&threads[2], NULL, thread_func, &count[2], 10);
	//mythread_create(&threads[3], NULL, thread_func, &count[3], 1);
	//mythread_create(&threads[4], NULL, thread_func, &count[4], 8);
	//mythread_create(&threads[5], NULL, thread_func, &count[5], 6);
	//mythread_create(&threads[6], NULL, thread_func, &count[6], 7);
	//mythread_create(&threads[7], NULL, thread_func, &count[7], 2);
	//termina ejemplo
	/*my_thread_chsched(atoi(argv[1]));
	
	for (i = 0; i < 1; i++) {
		LOG_PRINTF("Main: Will now wait for thread %ld. Yielding..\n", (unsigned long)threads[i].tid);
		mythread_join(threads[i], (void **)&status);
		LOG_PRINTF("Main: Thread %ld exited and increment count to %d\n", (unsigned long)threads[i].tid, count[i]);
	}
	LOG_PRINTF("Main: All threads completed execution. Will now exit..\n");
	mythread_end(NULL);

	return 0;
}*/
