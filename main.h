/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.h
 * Author: jose
 *
 * Created on 5 de Março de 2018, 20:10
 */
#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include "Pilha.h"

//Slot é a casa onde as cartas são postas
//Em FreeCell, você tem 8 slots vazios na primeira linha(sendo 4 "bases") e 8 slots com cartas

Pile *top_slots[4]; //Slots da esquerda de cima, inicialmente vazios
Pile *base_slots[4]; //Slots base, para onde as cartas vão. Talvez não precise utilizar Pile aqui?
Pile *mid_slots[8]; //Slots do meio. No inicio do jogo, têm as cartas distribuídas neles


//Funções de main.c
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
//Usarei minha própria função max
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