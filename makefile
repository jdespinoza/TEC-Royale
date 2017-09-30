
BANDERAS = -g -lm --std=c11
SALIDA = prueba

all:
	gcc $(BANDERAS) guerreros.c guerreros.h  -o $(SALIDA)


.PHONY clean:
	rm *.o $(SALIDA)
