#include <stdio.h>
#include <stdlib.h>
//#include "battlefield.h"
#include "warrior.h"

int battlefield_complete(){
	Warrior_t *tower_P = calloc(1, sizeof(Warrior_t));
	Warrior_t *tower_N = calloc(1, sizeof(Warrior_t));
	Warrior_t *tower_S = calloc(1, sizeof(Warrior_t));
	
	tower_P->life = 9;
	tower_N->life = 5;
	tower_S->life = 5;
	
	battlefield[TOWER_P_X][TOWER_P_Y] = tower_P;
	battlefield[TOWER_N_X][TOWER_N_Y] = tower_N;
	battlefield[TOWER_S_X][TOWER_S_Y] = tower_S;
	
	return 0;
}

int battlefield_init(){
	for (int i = 0; i < ROW; i++){
		for (int j = 0; j < COL; j++){
			battlefield[i][j] = NULL;
		}
	}
	return 0;
}

int verify_life(int i, int j){
	if (battlefield[i][j]->life <= 0) {
		printf("[MUERTA] ");
		return 1;
	}
	return 0;
}

int battlefield_print_help(int i, int j){
	if (i == TOWER_P_X && j == TOWER_P_Y) {
		if (!verify_life(i, j)){
			printf("[TP / %i] ", battlefield[i][j]->life);
		}
		return 1;
	}else if (i == TOWER_N_X && j == TOWER_N_Y) {
		if (!verify_life(i, j)){
			printf("[TN / %i] ", battlefield[i][j]->life);
		}
		return 1;
	}else if (i == TOWER_S_X && j == TOWER_S_Y) {
		if (!verify_life(i, j)){
			printf("[TS / %i] ", battlefield[i][j]->life);
		}
		return 1;
	}else if (i == BRIDGE_N_X && j == BRIDGE_N_Y) {
		printf("╠═══════");
		return 1;
	}else if (i == BRIDGE_S_X && j == BRIDGE_S_Y) {
		printf("╠═══════");
		return 1;
	}
	return 0;
}

void battlefield_print(){
	printf("   ");
	for (int k = 0; k < COL; k++){
		if (k < 9){
			printf("    %i    ", k+1);
		} else {
			printf("   %i    ", k+1);
		}
	}
	printf("\n");
	for (int i = 0; i < ROW; i++){
		if (i < 9){
			printf("%i  ", i+1);
		}else{
			printf("%i ", i+1);
		}
		for (int j = 0; j < COL; j++){
			if (battlefield_print_help(i, j)) {
				continue;
			}else if (battlefield[i][j] != NULL){
				if (battlefield[i][j]->atk < 10 && battlefield[i][j]->life < 10){
					printf("[%c/%i/%i ] ",battlefield[i][j]->class, battlefield[i][j]->atk, battlefield[i][j]->life);
				}else{
					printf("[%c/%i/%i] ",battlefield[i][j]->class, battlefield[i][j]->atk, battlefield[i][j]->life);
				}
			}else{
				printf("[      ] ");
			}
		}
		printf("\n");
	}
}

void battlefield_insert(int i, int j, struct warrior *warrior){
	battlefield[i][j] = warrior;
}
