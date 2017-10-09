#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct guerrero{
    int ataque;
    int defensa;
    int dano;
    char scheduler;
    int nivel;
    int evasion;
    int vida;
};

struct guerrero *gigante(){

    struct guerrero *gigante = calloc(1, sizeof(struct guerrero));

    gigante->ataque = 5;
    gigante->defensa = 9;
    gigante->dano = 7;
    gigante->nivel = 2;
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
    valquiria->nivel = 3;
    valquiria->scheduler = 'S';
    valquiria->evasion = 3;
    valquiria->vida = 100;

    return valquiria;

}
void atacar_guerrero(struct guerrero *guerrero1, struct guerrero *guerrero2){

	int evadir = (rand() % 10)*100;
	int dano_resivido = abs(guerrero1->ataque - guerrero2->defensa);

	if (evadir > guerrero2->evasion){
    printf("%i",dano_resivido);
    printf("\n");
		guerrero2-> vida -= dano_resivido;
	}
	else{
		guerrero2-> vida = guerrero2-> vida;
	}

}

int main(){
    struct guerrero *g1, *g2;
    g1 = gigante();
    g2 = valquiria();
    atacar_guerrero(g1,g2);
    printf("%i",g2->vida);
    return 0;
}
