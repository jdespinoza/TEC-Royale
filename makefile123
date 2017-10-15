
BANDERAS = -g -lm --std=c11
SALIDA = prueba

all:
	gcc $(BANDERAS) warrior.c warrior.h battlefield.c kbhit.c kbhit.h deck.c -o $(SALIDA)


.PHONY clean:
	rm *.o $(SALIDA)
