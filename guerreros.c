#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct guerrero{
    char tipo;
    char direccion;
    char scheduler;
    int ataque;
    int defensa;
    int dano;
    int nivel;
    int vida;
};
//Se debe de dar la configuracion desde un archivo .ini por mientras se hace asi
struct guerrero *gigante(){

    struct guerrero *gigante = calloc(1, sizeof(struct guerrero));
    gigante->tipo = 'G';
    gigante->direccion = '>';
    gigante->scheduler = 'R';//round robin
    gigante->ataque = 5;
    gigante->defensa = 9;
    gigante->dano = 7;
    gigante->nivel = 2;
    gigante->vida = 100;

    return gigante;

}
struct guerrero *valquiria(){

    struct guerrero *valquiria = calloc(1, sizeof(struct guerrero));

    valquiria->tipo = 'V';
    valquiria->direccion = '<';
    valquiria->scheduler = 'S';//sorteo
    valquiria->ataque = 6;
    valquiria->defensa = 8;
    valquiria->dano = 5;
    valquiria->nivel = 3;
    valquiria->vida = 100;

    return valquiria;

}

void atacar_guerrero(struct guerrero *guerrero1, struct guerrero *guerrero2){

	int dano_resivido = abs(guerrero1->ataque - guerrero2->defensa);

	guerrero2-> vida -= dano_resivido;

}

void imprime_guerrero(struct guerrero *guerrero1){
    printf("|%c",guerrero1->tipo);
    printf("|%c",guerrero1->direccion);
    printf("|\n");
    printf("|%i",guerrero1->nivel);
    printf("|%c",guerrero1->direccion);
    printf("|\n");

}

void imprime_maso(struct guerrero *maso){
  for (int i = 0; i<10; i++){
    //printf("|%c",maso[i]->tipo);
    //printf("|%c",maso[i]->direccion);
    printf("|  ");
  }
  for (int i = 0; i<10; i++){
    //printf("|%i",maso[i]->nivel);
  //  printf("|%c",maso[i]->direccion);
    printf("|  \n");
  }
}

void maso(){
  struct guerrero *maso[10];
  for(int i = 0; i<10; i++){
    int y = rand()%10;
    switch(y) {
      case 0 :

        maso[i] = gigante();
        //imprime_guerrero(maso[i]);
        break;
      case 1 :

        maso[i] = valquiria();
        //imprime_guerrero(maso[i]);
        break;
      case 2 :

        maso[i] = gigante();
        //imprime_guerrero(maso[i]);
        break;
      case 3 :

        maso[i] = valquiria();
        //imprime_guerrero(maso[i]);
        break;
      case 4 :

        maso[i] = gigante();
        //imprime_guerrero(maso[i]);
        break;
      case 5 :

        maso[i] = valquiria();
        //imprime_guerrero(maso[i]);
        break;
      case 6 :

        maso[i] = gigante();
        //imprime_guerrero(maso[i]);
        break;
      case 7 :

        maso[i] = valquiria();
        //imprime_guerrero(maso[i]);
        break;
      case 8 :

        maso[i] = gigante();
        //imprime_guerrero(maso[i]);
          break;
      default :

        maso[i] = valquiria();
        //imprime_guerrero(maso[i]);
    }

  }//AQUI SE LLAMA A LA QUE IMPRIME PERO NO SABIA COMO RETORNAR LA LISTA DE STRUCT
  for (int i = 0; i<10; i++){
    printf("|%c",(maso[i])->tipo);
    printf("|%c",(maso[i])->direccion);
    printf("|  ");
  }
  printf("\n");
  for (int i = 0; i<10; i++){
    printf("|%i",(maso[i])->nivel);
    printf("|%c",(maso[i])->direccion);
    printf("|  ");
  }
  printf("\n");


}

int main(){
  maso();
    //struct guerrero *g1, *g2;
    //g1 = gigante();
  //  g2 = valquiria();
  //  atacar_guerrero(g1,g2);
    //imprime_guerrero(g2);
    //printf("%c",g2->direccion);
    return 0;
}
