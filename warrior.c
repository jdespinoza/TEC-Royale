#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <mypthread.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "warrior.h"
#include "kbhit.h"

//#include "deck.h"

char buffer[1024];

//Se debe de dar la configuracion desde un archivo .ini por mientras se hace asi
void leer(){
	  FILE *archivo;
  char caracteres[100];
  
  int i = 0;
  archivo = fopen("configuracion.ini","r");
 	if (archivo == NULL)
 		exit(1);
 	else
        {
 	    while (fgets(caracteres,100,archivo) != NULL)
 	    {
          char* token = strtok(caracteres, "=");
          token = strtok(NULL, "=");
          if(token != NULL){
            lista[i] = malloc(strlen(token) * sizeof(char));
            strcpy(lista[i], token);
            i++;
          }
 	    }

        }
    fclose(archivo);
	
}

Gigante *create_gigante(){
	


    Gigante *gigante = calloc(1, sizeof(Gigante));

    gigante->class = lista[0][0];
    gigante->scheduler = lista[1][0];//round robin
    gigante->atk = lista[2][0]-48;
    gigante->life = lista[3][0]-48;
    gigante->level = lista[4][0]-48;

    return gigante;

}

Valquiria *create_valquiria(){

    Valquiria *valquiria = calloc(1, sizeof(Valquiria));

      valquiria->class = lista[5][0];
      valquiria->scheduler = lista[6][0];
      valquiria->atk = lista[7][0]-48;
      valquiria->life = lista[8][0]-48;
      valquiria->level = lista[9][0]-48;

    return valquiria;

}

Bombardero *create_bombardero(){

    Bombardero *bombardero = calloc(1, sizeof(Bombardero));

      bombardero->class = lista[10][0];
      bombardero->scheduler = lista[11][0];
      bombardero->atk = lista[12][0]-48;
      bombardero->life = lista[13][0]-48;
      bombardero->level = lista[14][0]-48;

    return bombardero;

}

Caballero *create_caballero(){

    Caballero *caballero = calloc(1, sizeof(Caballero));

      caballero->class = lista[15][0];
      caballero->scheduler = lista[16][0];
      caballero->atk = lista[17][0]-48;
      caballero->life = lista[18][0]-48;
      caballero->level = lista[19][0]-48;

    return caballero;

}

Esbirro *create_esbirro(){

    Esbirro *esbirro = calloc(1, sizeof(Esbirro));

      esbirro->class = lista[20][0];
      esbirro->scheduler = lista[21][0];
      esbirro->atk = lista[22][0]-48;
      esbirro->life = lista[23][0]-48;
      esbirro->level = lista[24][0]-48;

    return esbirro;

}

Duende *create_duende(){

    Duende *duende = calloc(1, sizeof(Duende));

      duende->class = lista[25][0];
      duende->scheduler = lista[26][0];
      duende->atk = lista[27][0]-48;
      duende->life = lista[28][0]-48;
      duende->level = lista[29][0]-48;

    return duende;

}

Principe *create_principe(){

    Principe *principe = calloc(1, sizeof(Principe));

      principe->class = lista[30][0];
      principe->scheduler = lista[31][0];
      principe->atk = lista[32][0]-48;
      principe->life = lista[33][0]-48;
      principe->level = lista[34][0]-48;

    return principe;

}

Montapuerco *create_montapuerco(){

    Montapuerco *montapuerco = calloc(1, sizeof(Montapuerco));

      montapuerco->class = lista[35][0];
      montapuerco->scheduler = lista[36][0];
      montapuerco->atk = lista[37][0]-48;
      montapuerco->life = lista[38][0]-48;
      montapuerco->level = lista[39][0]-48;

    return montapuerco;

}

Dragon *create_dragon(){

    Dragon *dragon = calloc(1, sizeof(Dragon));

	  dragon->class = lista[40][0];
      dragon->scheduler = lista[41][0];
      dragon->atk = lista[42][0]-48;
      dragon->life = lista[43][0]-48;
      dragon->level = lista[44][0]-48;

    return dragon;

}

Mago *create_mago(){

    Mago *mago = calloc(1, sizeof(Mago));

	mago->class = lista[45][0];
	mago->scheduler = lista[46][0];
	mago->atk = lista[47][0]-48;
	mago->life = lista[48][0]-48;
	mago->level = lista[49][0]-48;

    return mago;

}

Warrior_t *choose_warrior(int i){
		leer();
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

int move_warrior_t_bridge(int i, int j){
	if (BRIDGE_N_X == i && BRIDGE_N_Y == j){
		strcpy(buffer,"Puente\n");
		return 1;
	}else if (BRIDGE_S_X == i && BRIDGE_S_Y ==j){
		strcpy(buffer,"Puente\n");
		return 1;
	}
	strcpy(buffer,"Hello World\n");
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
				}else if (move_warrior_t_bridge(i, j)) {
					continue;
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
						}else if (battlefield[i][j]->status == '<'){
							//validar choque con torres y ataques
							if(j > POS_Y){
								
								aux = j - move_warrior_t_help(i, j-1);
								if(aux != j){
									battlefield[i][aux]->life = battlefield[i][aux]->life - battlefield[i][j]->atk;
									//if (battlefield[i][aux]->life <= 0){
										//battlefield[i][aux] = NULL;
									//}
									battlefield[i][aux-1] = battlefield[i][j];
									battlefield[i][aux-1]->flag = 1;
									battlefield[i][j] = NULL;
								}else if(battlefield[i][j-1] != NULL){
									battlefield[i][j-1]->life = battlefield[i][j-1]->life - battlefield[i][j]->atk;
									battlefield[i][j]->life = battlefield[i][j]->life - battlefield[i][j-1]->atk;
									if (battlefield[i][j-1]->life <= 0){
										battlefield[i][j-1] = NULL;
									}
									if (battlefield[i][j]->life <= 0) {
										battlefield[i][j] = NULL;
									}
									battlefield[i][j] = NULL;
								}else{
									battlefield[i][j-1] = battlefield[i][j];
									battlefield[i][j-1]->flag = 1;
									battlefield[i][j] = NULL;
								}
								
								j--;
							}else{
								if (i == 4){
									battlefield[i][j]->status = 'v';
									battlefield[i+1][j] = battlefield[i][j];
									battlefield[i+1][j]->flag = 1;
								}else{
									battlefield[i][j]->status = '^';
									battlefield[i-1][j] = battlefield[i][j];
									battlefield[i-1][j]->flag = 1;
								}
								battlefield[i][j] = NULL;
							}
						}else if (battlefield[i][j]->status == '>'){
							//validar choque con torres y ataques
							aux = j + move_warrior_t_help(i, j+1);
							battlefield[i][aux+1] = battlefield[i][j];
							battlefield[i][aux+1]->flag = 1;
							battlefield[i][j] = NULL;
							j = aux;
							j++;
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



int client_aux(){
  int clientSocket;
  
  struct sockaddr_in serverAddr;
  socklen_t addr_size;

  /*---- Create the socket. The three arguments are: ----*/
  /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  clientSocket = socket(PF_INET, SOCK_STREAM, 0);
  
  /*---- Configure settings of the server address struct ----*/
  /* Address family = Internet */
  serverAddr.sin_family = AF_INET;
  /* Set port number, using htons function to use proper byte order */
  serverAddr.sin_port = htons(7891);
  /* Set IP address to localhost */
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  /* Set all bits of the padding field to 0 */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  /*---- Connect the socket to the server using the address struct ----*/
  addr_size = sizeof serverAddr;
  
  
	connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
  /*---- Read the message from the server into the buffer ----*/
  /*---- Send message to the socket of the incoming connection ----*/
  
	send(clientSocket,buffer,13,0);  
  return 0;	
	
}

void *jason_hilo(void *arg){
	while(1){
		client_aux();
		mythread_yield();
	}
	return NULL;
}

void *server_aux(void *arg){
  int welcomeSocket, newSocket;
  char buffer[1024];
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;

  /*---- Create the socket. The three arguments are: ----*/
  /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);
  
  /*---- Configure settings of the server address struct ----*/
  /* Address family = Internet */
  serverAddr.sin_family = AF_INET;
  /* Set port number, using htons function to use proper byte order */
  serverAddr.sin_port = htons(7891);
  /* Set IP address to localhost */
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  /* Set all bits of the padding field to 0 */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  /*---- Bind the address struct to the socket ----*/
  bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

  /*---- Listen on the socket, with 5 max connection requests queued ----*/
  if(listen(welcomeSocket,5)==0)
    printf("Listening\n");
  else
    printf("Error\n");

  /*---- Accept call creates a new socket for the incoming connection ----*/
  addr_size = sizeof serverStorage;
  

  while (1){
	  newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
	   /*---- Read the message from the server into the buffer ----*/
	  recv(newSocket, buffer, 1024, 0);

  /*---- Print the received message ----*/
	  printf("Data received: %s",buffer);  
	  //jason = 1234;
	  mythread_yield();

  }
  return NULL;
}

void *enemy(void *arg) {
	Warrior_t *warrior_arr [10];
	for (int i = 0; i < 10; i++) {
		warrior_arr[i] = choose_warrior(i);
		warrior_arr[i]->status = '<';
		mythread_yield();
	}
	for (int j = 0; j < 10; j++) {
		mythread_yield();
		if(rand()%2){
			battlefield[BRIDGE_N_X][BRIDGE_N_Y-1] = warrior_arr[j];
		}else{
			battlefield[BRIDGE_S_X][BRIDGE_S_Y-1] = warrior_arr[j];
		}
		mythread_yield();
	}
	
	mythread_end(NULL);
	return NULL;
	
}

void *aux(void *arg){
	
	//mythread_t threads[NTHREADS];
	//my_thread_init();
	
	//rutina para insertar
	if(!boot){
		init_keyboard();
	}
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
	int time_boot = 2;
	int card_boot;
	//int card, x, y;
	//Move_t *move = calloc(1, sizeof(Move_t));
	//int num_threads = 0;
	//char *status;
	//my_thread_chsched(0);
	while(1){
		battlefield_print();
		deck_print();
		if(!boot){
			if (kbhit() == 1) {
				card = readch();
				if (card == 'q' || card == 'Q') {
					close_keyboard();
					exit(0);
				}
				new_warrior = choose_card(card-48);
				battlefield_insert(POS_X,POS_Y,new_warrior); 
			}
		}else{
			time_boot++;
			if (time_boot == 3){
				time_boot = 0;
				card_boot = (rand()%5)+1;
				new_warrior = choose_card(card_boot);
				battlefield_insert(POS_X,POS_Y,new_warrior);
			} 
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
		
		//printf("\n%i", jason);
		system("clear");
		mythread_yield();
		

	}
	return NULL;
}

int main (int argc, char **argv) {
	
	int c;
	int c_flag = 0;
	while ((c = getopt (argc, argv, "c:")) != -1){
		switch (c){
			case 'c':
				c_flag = 1;
				break;
			default:
				exit(0);
		}
	}
	if(!c_flag){
		printf("Por favor escriba el comando -c [archivo]\n");
		exit(0);
	}
	
	strcpy(buffer,"Hello World\n");
	printf("Boot? ");
	scanf("%i", &boot);
	printf("\n");
	
	mythread_t threads[NTHREADS];
	int count[NTHREADS];
	int i;
	char *status;
	
	my_thread_init();
	
	mythread_create(&threads[0], NULL, jason_hilo, &count[0], 8);
	
	mythread_create(&threads[1], NULL, aux, &count[0], 6);
	
	mythread_create(&threads[2], NULL, enemy, &count[0], 6);
	
	my_thread_chsched(0);
	
	for (i = 0; i < 3; i++) {
		LOG_PRINTF("Main: Will now wait for thread %ld. Yielding..\n", (unsigned long)threads[i].tid);
		mythread_join(threads[i], (void **)&status);
		LOG_PRINTF("Main: Thread %ld exited and increment count to %d\n", (unsigned long)threads[i].tid, count[i]);
	}
	LOG_PRINTF("Main: All threads completed execution. Will now exit..\n");
	mythread_end(NULL);
	
	//aux();
	return 0;
}
