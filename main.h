#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include "Pilha.h"

//Slot sao a casa onde as cartas sao postas
//Em FreeCell, voce tem 8 slots vazios na primeira linha(sendo 4 "bases") e 8 slots com cartas

Pile *top_slots[4]; //Slots da esquerda de cima, inicialmente vazios
Pile *base_slots[4]; //Slots base, para onde as cartas vao. Talvez nÃ£o precise utilizar Pile aqui?
Pile *mid_slots[8]; //Slots do meio. No inicio do jogo, tem as cartas distribui­das neles


//Funcoes de main.c
void cardToStr(Item *card, char *c);
void shuffleArray(int *arr, size_t n);
void initializeCards();
int moveCardToPile(Pile *from, Pile *to);
int moveCardToBase(Pile *from);
int getCardNipe(Item *card);
int getCardNumber(Item *card);
int canMove(Pile *from, Pile *to);
int canMoveToBase(Pile *from);



#define NOMINMAX 1
//Usarei minha propria funcao max
#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })


void drawCard(Item *card);
void drawBoard();
void drawMiddle();
void drawRequestHandle();
void receiveUserInput();
void checkGameStatus();


int gameStatus; //estado do jogo
#define GAME_STATUS_START 0
#define GAME_STATUS_CHOSECARD 1
#define GAME_STATUS_CHOSETARGET 2
#define GAME_STATUS_DEFEAT 3
#define GAME_STATUS_VICTORY 4

Pile *selectedSlot; //pilha selecionada para mover

#endif // MAIN_H_INCLUDED
