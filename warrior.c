#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <mypthread.h>

#include "warrior.h"
#include "kbhit.h"
//#include "deck.h"

//Se debe de dar la configuracion desde un archivo .ini por mientras se hace asi
Gigante *create_gigante(){

    Gigante *gigante = calloc(1, sizeof(Gigante));
    
    gigante->class = 'G';
    gigante->scheduler = 'R';//round robin
    gigante->atk = 2;
    gigante->life = 8;
    gigante->level = G_LVL;

    return gigante;

}

Valquiria *create_valquiria(){

    Valquiria *valquiria = calloc(1, sizeof(Valquiria));

    valquiria->class = 'V';
    valquiria->scheduler = 'S';//sorteo
    valquiria->atk = 6;
    valquiria->life = 4;
    valquiria->level = V_LVL;

    return valquiria;

}

Bombardero *create_bombardero(){

    Bombardero *bombardero = calloc(1, sizeof(Bombardero));

    bombardero->class = 'B';
    bombardero->scheduler = 'S';//sorteo
    bombardero->atk = 4;
    bombardero->life = 1;
    bombardero->level = B_LVL;

    return bombardero;

}

Caballero *create_caballero(){

    Caballero *caballero = calloc(1, sizeof(Caballero));

    caballero->class = 'C';
    caballero->scheduler = 'S';//sorteo
    caballero->atk = 5;
    caballero->life = 5;
    caballero->level = C_LVL;

    return caballero;

}

Esbirro *create_esbirro(){

    Esbirro *esbirro = calloc(1, sizeof(Esbirro));

    esbirro->class = 'E';
    esbirro->scheduler = 'S';//sorteo
    esbirro->atk = 4;
    esbirro->life = 3;
    esbirro->level = E_LVL;

    return esbirro;

}

Duende *create_duende(){

    Duende *duende = calloc(1, sizeof(Duende));

    duende->class = 'L';
    duende->scheduler = 'S';//sorteo
    duende->atk = 2;
    duende->life = 2;
    duende->level = L_LVL;

    return duende;

}

Principe *create_principe(){

    Principe *principe = calloc(1, sizeof(Principe));

    principe->class = 'P';
    principe->scheduler = 'S';//sorteo
    principe->atk = 9;
    principe->life = 6;
    principe->level = P_LVL;

    return principe;

}

Montapuerco *create_montapuerco(){

    Montapuerco *montapuerco = calloc(1, sizeof(Montapuerco));

    montapuerco->class = 'K';
    montapuerco->scheduler = 'S';//sorteo
    montapuerco->atk = 6;
    montapuerco->life = 4;
    montapuerco->level = K_LVL;

    return montapuerco;

}

Dragon *create_dragon(){

    Dragon *dragon = calloc(1, sizeof(Dragon));

    dragon->class = 'D';
    dragon->scheduler = 'S';//sorteo
    dragon->atk = 8;
    dragon->life = 7;
    dragon->level = D_LVL;

    return dragon;

}

Mago *create_mago(){

    Mago *mago = calloc(1, sizeof(Mago));

    mago->class = 'M';
    mago->scheduler = 'S';//sorteo
    mago->atk = 9;
    mago->life = 6;
    mago->level = M_LVL;

    return mago;

}

Warrior_t *choose_warrior(int i){
	switch (i){
		case 0:
			return create_gigante();
		case 1:
			return create_valquiria();
		case 2:
			return create_bombardero();
		case 3:
			return create_caballero();
		case 4:
			return create_esbirro();
		case 5:
			return create_duende();
		case 6:
			return create_principe();
		case 7:
			return create_montapuerco();
		case 8:
			return create_dragon();
		case 9:
			return create_mago();
	
	}
	return 0;
}

int choose_lvl(char class){
	switch (class){
		case 'G':
			return G_LVL;
		case 'V':
			return ++V_LVL;
		case 'B':
			return ++B_LVL;
		case 'C':
			return ++C_LVL;
		case 'E':
			return ++E_LVL;
		case 'L':
			return ++L_LVL;
		case 'P':
			return ++P_LVL;
		case 'K':
			return ++K_LVL;
		case 'D':
			return ++D_LVL;
		case 'M':
			return ++M_LVL;
	}
	return 0;
}

void lvl_init(){
	
	G_LVL = 1;
	V_LVL = 1;
	B_LVL = 1;
	C_LVL = 1;
	E_LVL = 1;
	L_LVL = 1;
	P_LVL = 1;
	K_LVL = 1;
	D_LVL = 1;
	M_LVL = 1;

}

Warrior_t *choose_card(int i){
	Deck *aux = start;
	Warrior_t *warrior_aux;
	if (i < 0 || i > 5){
		return NULL;
	}
	if (i == 1) {
		start = start->next;
		start->back = NULL;
		return aux->warrior_deck;
	}
	i--;
	while (i > 0) {
		aux = aux->next;
		i--;
	}
	
	warrior_aux = aux->warrior_deck;
	
	aux->back->next = aux->next;
	aux->next->back = aux->back;
	
	return warrior_aux;
}

void *move_warrior(void *arg){
	Move_t *move = (Move_t *) arg;
	int x = move->x;
	int y = move->y;
	Warrior_t *new_warrior;
	while(x+1 < 15){
		new_warrior = battlefield[y][x];
		battlefield[y][x] = NULL;
		x++;
		battlefield[y][x] = new_warrior;
		mythread_yield();
	}
	return NULL;
}

void reset_warrior(){
	for (int i = 0; i < ROW; i++){
		for (int j = 0; j < COL; j++){
			if (battlefield[i][j] != NULL){
				battlefield[i][j]->flag = 0;
			}
		}
	}
}

int move_warrior_t_help(int i, int j){
	if (i == TOWER_P_X && j == TOWER_P_Y) {
		return 1;
	}else if (i == TOWER_N_X && j == TOWER_N_Y) {
		return 1;
	}else if (i == TOWER_S_X && j == TOWER_S_Y) {
		return 1;
	}
	return 0;
}

void move_warrior_t(){
	int aux;
	for (int i = 0; i < ROW; i++){
		for (int j = 0; j < COL; j++){
			if (move_warrior_t_help(i, j)) {
				continue;
			}else if (battlefield[i][j] != NULL){
				if (i == POS_X && j == POS_Y) {
					if (rand()%2) {
						battlefield[i-1][j] = battlefield[i][j];
						battlefield[i-1][j]->status = '^';
					}else{
						battlefield[i+1][j] = battlefield[i][j];
						battlefield[i+1][j]->status = 'v';
					}
					battlefield[i][j] = NULL;
				}else{
					if (!battlefield[i][j]->flag){
						if (battlefield[i][j]->status == '^'){
							if (i > 4){
								battlefield[i-1][j] = battlefield[i][j];
								battlefield[i-1][j]->flag = 1;
							}else{
								battlefield[i][j+1] = battlefield[i][j];
								battlefield[i][j+1]->status = '>';
								battlefield[i][j+1]->flag = 1;
								j++;
							}
							battlefield[i][j] = NULL;
						}else if (battlefield[i][j]->status == '>'){
							//validar choque con torres y ataques
							aux = j + move_warrior_t_help(i, j+1);
							battlefield[i][aux+1] = battlefield[i][j];
							battlefield[i][aux+1]->flag = 1;
							battlefield[i][j] = NULL;
							j = aux;
							j++;
						}else if (battlefield[i][j]->status == '<'){
							//validar choque con torres y ataques
							battlefield[i][j-1] = battlefield[i][j];
							battlefield[i][j-1]->flag = 1;
							battlefield[i][j] = NULL;
							j--;
						}else if (battlefield[i][j]->status == 'v'){
							if (i < 25){
								battlefield[i+1][j] = battlefield[i][j];
								battlefield[i+1][j]->flag = 1;
							}else{
								battlefield[i][j+1] = battlefield[i][j];
								battlefield[i][j+1]->status = '>';
								battlefield[i][j+1]->flag = 1;
								j++;
							}
							battlefield[i][j] = NULL;
						}
					}
				}
			}
		}
	}
}

int aux(){
	
	//mythread_t threads[NTHREADS];
	//my_thread_init();
	
	//rutina para insertar
	init_keyboard();
	battlefield_init();
	battlefield_complete();
	//Valquiria *v = create_valquiria();
	//battlefield_insert(0,3,v); 
	//battlefield_print();
	
	//rutina para crear el deck
	srand (time(NULL)); 
	lvl_init();
	//deck_init();
	create_deck();
	//deck_print();
	system("clear");
	char card;
	Warrior_t *new_warrior;
	//int card, x, y;
	//Move_t *move = calloc(1, sizeof(Move_t));
	//int num_threads = 0;
	//char *status;
	//my_thread_chsched(0);
	while(1){
		battlefield_print();
		deck_print();
		if (kbhit() == 1) {
			card = readch();
			if (card == 'q' || card == 'Q') {
				close_keyboard();
				exit(0);
			}
			new_warrior = choose_card(card-48);
			battlefield_insert(POS_X,POS_Y,new_warrior); 
		}
		usleep(500000);
		reset_warrior();
		move_warrior_t();
		//printf("\nCarta: ");
		//scanf("%i", &card);
		//printf("\nDonde quiere colocar al guerrero?\n->X: ");
		//validar que coordenas sean diferentes a las torres
		//scanf("%i", &x);
		//printf("\n->Y: ");
		//scanf("%i", &y);
		//move->x = x-1;
		//move->y = y-1;
		//new_warrior = choose_card(card-48);
		//battlefield_insert(POS_Y,POS_X,new_warrior); 
		//mythread_create(&threads[num_threads], NULL, move_warrior, move, 4);
		//mythread_join(threads[num_threads], (void **)&status);
		//num_threads++;
		system("clear");

	}
	return 0;
}

int main () {
	//rutina para insertar en el tablero
	
	/*battlefield_init();
	Valquiria *v = create_valquiria();
	battlefield_insert(0,3,v); 
	battlefield_print();
	
	//rutina para crear el deck
	srand (time(NULL)); 
	lvl_init();
	deck_init();
	create_deck();
	deck_print();
	system("clear");
	char tecla;
	while(1){
		battlefield_print();
		deck_print();
		//if (kbhit() == 1) {
			//tecla = readch();
			//printf("holaaaaa: %c\n", tecla);
		//}
		usleep(500000);
		system("clear");

	}
	
	
	for (int i =0;i<DECK_LEN;i++){
		printf("%c ", deck[i]->class);
	}
	*/
	aux();
	return 0;
}
