#include "mypthreads.h"
#include <stdio.h>
#include <unistd.h>

void thread1()
{
	int i;
	for ( i = 0; i < 5; ++ i )
	{
		printf( "Hey, I'm thread #1: %d\n", i );
		my_thread_yield();
	}
	return;
}

void thread2()
{
	int i;
	for ( i = 0; i < 5; ++ i )
	{
		printf( "Hey, I'm thread #2: %d\n", i );
		my_thread_yield();
	}
	return;
}

void thread3()
{
	int i;
	for ( i = 0; i < 5; ++ i )
	{
		printf( "Hey, I'm thread #3: %d\n", i );
		my_thread_yield();
	}
	return;
}

void thread4()
{
	int i;
	for ( i = 0; i < 5; ++ i )
	{
		printf( "Hey, I'm thread #4: %d\n", i );
		my_thread_yield();
	}
	return;
}

void thread5()
{
	int i;
	for ( i = 0; i < 5; ++ i )
	{
		printf( "Hey, I'm thread #5: %d\n", i );
		my_thread_yield();
	}
	return;
}

void thread6()
{
	int i;
	for ( i = 0; i < 5; ++ i )
	{
		printf( "Hey, I'm thread #6: %d\n", i );
		my_thread_yield();
	}
	return;
}

void thread7()
{
	int i;
	for ( i = 0; i < 5; ++ i )
	{
		printf( "Hey, I'm thread #7: %d\n", i );
		my_thread_yield();
	}
	return;
}

void thread8()
{
	int i;
	for ( i = 0; i < 5; ++ i )
	{
		printf( "Hey, I'm thread #8: %d\n", i );
		my_thread_yield();
	}
	return;
}

void thread9()
{
	int i;
	for ( i = 0; i < 5; ++ i )
	{
		printf( "Hey, I'm thread #9: %d\n", i );
		my_thread_yield();
	}
	return;
}

void thread10()
{
	int i;
	for ( i = 0; i < 5; ++ i )
	{
		printf( "Hey, I'm thread #10: %d\n", i );
		my_thread_yield();
	}
	return;
}

void fibonacchi()
{
	int i;
	int fib[2] = { 0, 1 };
	
	/*sleep( 2 ); */
	printf( "fibonacchi(0) = 0\nfibonnachi(1) = 1\n" );
	for( i = 2; i < 15; ++ i )
	{
		int nextFib = fib[0] + fib[1];
		printf( "fibonacchi(%d) = %d\n", i, nextFib );
		fib[0] = fib[1];
		fib[1] = nextFib;
		my_thread_yield();
	}
}

void squares()
{
	int i;
	
	/*sleep( 5 ); */
	for ( i = 0; i < 10; ++ i )
	{
		printf( "%d*%d = %d\n", i, i, i*i );
		my_thread_yield();
	}
}

int main()
{
	//crear hilos
	my_thread_create();
	
	//asignar hilos
	//apenas asigno comienzan a ejecutar
	//si se asigna mas del limite entonces no ejecuta ni asigna
	//los que se quedaron sin hilos
	my_thread_join( &thread1 );
	my_thread_join( &thread2 );
	my_thread_join( &thread3 );
	my_thread_join( &thread4 );
	my_thread_join( &thread5 );
	my_thread_join( &thread6 );
	my_thread_join( &thread7 );
	my_thread_join( &thread8 );
	my_thread_join( &thread9 );
	my_thread_join( &fibonacchi );
	my_thread_join( &squares );

	//espera que todos terminen para liberar la memoria
	my_thread_end();
	
	return 0;
}
