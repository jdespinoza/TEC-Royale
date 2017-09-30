#include <stdlib.h>
#include <stdio.h>

/**
 *Entradas: esta funcion no recive nada como parametros.
 * Esta funcion se encarga de generar un gigante.
 * Salida: esta funcion retorna un struct guerrero, un gigante.
 */
struct guerrero{
    int ataque;
    int defensa;
    int dano;
    char scheduler;
    int evasion;
    int vida;
};

struct guerrero *gigante(){
    
    struct guerrero *gigante = calloc(1, sizeof(struct guerrero));
    
    gigante->ataque = 5;
    gigante->defensa = 9;
    gigante->dano = 7;
    gigante->scheduler = 'R';
    gigante->evasion = 2;
    gigante->vida = 100;
    
    return gigante;
    
}
struct guerrero *valquiria(){
    
    struct guerrero *valquiria = calloc(1, sizeof(struct guerrero));
    
    valquiria->ataque = 6;
    valquiria->defensa = 8;
    valquiria->dano = 5;
    valquiria->scheduler = 'S';
    valquiria->evasion = 3;
    valquiria->vida = 100;
    
    return valquiria;
    
}

int main(){
    struct guerrero *g1, *g2;
    g1 = gigante();
    g2 = valquiria();
    printf("%i",g2->dano);
    return 0;
}
