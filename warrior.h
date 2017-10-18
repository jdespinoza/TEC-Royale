#include <stdlib.h>
#include <stdio.h>

#define ROW 30
#define COL 15
#define HAND 5
#define DECK_LEN 100
#define TOWER_P_X 15
#define TOWER_P_Y 0
#define TOWER_N_X 4
#define TOWER_N_Y 7
#define TOWER_S_X 25
#define TOWER_S_Y 7
#define BRIDGE_N_X 4
#define BRIDGE_N_Y 14
#define BRIDGE_S_X 25
#define BRIDGE_S_Y 14
#define POS_X 15
#define POS_Y 1

struct warrior{
    char class;
    char status;
    char scheduler;
    int atk;
    int life;
    int level;
    int flag;
};

struct Move{
	int x;
	int y;
};

typedef struct warrior Warrior_t;

typedef struct Move Move_t;

typedef struct warrior Gigante;

typedef struct warrior Valquiria;

typedef struct warrior Bombardero;

typedef struct warrior Caballero;

typedef struct warrior Esbirro;

typedef struct warrior Duende;

typedef struct warrior Principe;

typedef struct warrior Montapuerco;

typedef struct warrior Dragon;

typedef struct warrior Mago;

struct warrior *battlefield[ROW][COL];

int battlefield_init();

int battlefield_complete();

int battlefield_print_help(int i, int j);

void battlefield_print();

void battlefield_insert(int i, int j, struct warrior *warrior);

int G_LVL;

int V_LVL;

int B_LVL;

int C_LVL;

int E_LVL;

int L_LVL;

int P_LVL;

int K_LVL;

int D_LVL;

int M_LVL;

Gigante *create_gigante();

Valquiria *create_valquiria();

Bombardero *create_bombardero();

Caballero *create_caballero();

Esbirro *create_esbirro();

Duende *create_duende();

Principe *create_principe();

Montapuerco *create_montapuerco();

Dragon *create_dragon();

Mago *create_mago();

Warrior_t *choose_warrior(int i);

int choose_lvl(char class);

void lvl_init();

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

void deck_print();

int boot;

char *lista[50];
