#include <stdio.h>
#include <stdlib.h>
//#include "deck.h"
#include "warrior.h"

void deck_print(){
	Deck *aux = start;
	Deck *aux2 = start;
	printf("\n");
	printf("\n");
	int i;
	for (i = 0; i < HAND; i++) {
		printf("╔════════════╦═══════════╗ ");
	}
	printf("\n");
	for (i = 0; i < HAND; i++) {
		printf("║");
		printf("Clase:  %c   ║ Nivel: %i  ", aux->warrior_deck->class, aux->warrior_deck->level);
		printf("║ ");
		aux = aux->next;
	}
	printf("\n");
	for (i = 0; i < HAND; i++) {
		printf("╠════════════╬═══════════╣ ");
	}
	printf("\n");
	for (i = 0; i < HAND; i++) {
		printf("║");
		printf("Ataque: %i   ║ Vida:  %i  ", aux2->warrior_deck->atk, aux2->warrior_deck->life);
		printf("║ ");
		aux2 = aux2->next;
	}
	printf("\n");
	for (i = 0; i < HAND; i++) {
		printf("╚════════════╩═══════════╝ ");
	}
	printf("\n");
	for (i = 0; i < HAND; i++) {
		printf("             %i             ", i+1);
	}
	printf("\n");
}

Deck *deck_search(int pos){
	Deck *aux = start;
	for (int i = 0; i < pos; i++) {
		aux = aux->next;
	}
	return aux;
}

Deck *create_Node(){
	Deck *node = calloc(1, sizeof(Deck));
	return node;
}

int create_deck(){
	deck = calloc(1, sizeof(Deck));
	start = deck;
	int i;
	int deck_max = 9;
	int deck_min = 0;
	int factor;
	Warrior_t *aux;
	deck->warrior_deck = choose_warrior(0);
	deck->next = create_Node();
	deck->back = NULL;
	deck->next->back = deck;
	deck = deck->next;
	for (i = 1; i < 10; i++){
		deck->warrior_deck = choose_warrior(i);
		deck->next = create_Node();
		deck->next->back = deck;
		if (i == 4) {
			max_hand = deck;
		}
		deck = deck->next;
	}
	for (i = 10; i < DECK_LEN; i++){
		factor = deck_search(deck_min)->warrior_deck->class + deck_search(deck_max)->warrior_deck->class + (rand() % 1000);
		aux = choose_warrior(factor%10);
		aux->atk = ((deck_search(deck_min)->warrior_deck->atk + deck_search(deck_max)->warrior_deck->atk) / 2) + (rand() % 3);
		aux->life = ((deck_search(deck_min)->warrior_deck->life + deck_search(deck_min)->warrior_deck->life) / 2) + (rand() % 3);
		aux->level = choose_lvl(aux->class);
		deck->warrior_deck = aux;
		deck->next = create_Node();
		deck->next->back = deck;
		deck = deck->next;
		deck_min++;
		deck_max++;
	}
	return 0;
}



