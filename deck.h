#include <stdio.h>
#include <stdlib.h>

#define DECK_LEN 100

struct Node{
	Warrior_t *warrior_deck;
	struct Node *next;
	struct Node *back;
};

typedef struct Node Deck;

Deck *deck;

Deck *start;

Deck *max_hand;

Deck *deck_search(int pos);

Deck *create_Node();

int create_deck();

