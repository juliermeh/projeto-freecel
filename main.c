/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.c
 * Author: jose
 *
 * Created on 5 de Março de 2018, 19:58
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#include "main.h"

/////////////////////////////////
// Cartas são enumeradas de 0 a 51
// 0 = A Copas
// 51 = K Espadas
// 0-12 = copas
// 13-25 = ouros
// 26-38 = paus
// 39-51 = espadas

// (valor+1)/13 = categoria(copas/espadas/ouros/paus); 0=C 1=O 2=P 3=E
// (valor+1)%13 = número(A,2,3,4,5,6,7,8,9,10,J,Q,K)
/////////////////////////////////

// void cardToStr(Item *card, char *c)
// transforma *c na carta
void cardToStr(Item *card, char *c)
{
    if(card == NULL)
    {
        strcpy(c, "   ");
        return;
    }

    int category = getCardNipe(card);
    int value = getCardNumber(card);
    c[0] = ' '; c[1] = ' '; c[2] = ' ';
    switch(value)
    {
        case 0: c[1] = 'A'; break; //A
        case 9: c[0] = '1'; c[1] = '0'; break; //10
        case 10: c[1] = 'J'; break; //J
        case 11: c[1] = 'Q'; break; //Q
        case 12: c[1] = 'K'; break; //K
        default: c[1] = '1'+value; break; //Isto só é possível pois os casos para números > 9 já foram cobertos acima

    }

    switch(category)
    {
        case 0: c[2] = '\3'; break;
        case 1: c[2] = '\4'; break;
        case 2: c[2] = '\5'; break;
        case 3: c[2] = '\6'; break;
        default: c[2] = ' '; break;
    }
}

void shuffleArray(int *arr, size_t n)
{
    if(n>1)
    {
        size_t i, j;
        for(i = 0; i < n-1; i++)
        {
            j = i + (rand() / (RAND_MAX / (n - i) + 1));
            int t = arr[j];
            arr[j] = arr[i];
            arr[i] = t;
        }
    }
}

void initializeCards()
{
    srand(time(NULL)); //modifica a base do gerador aleatório para não sair a mesma combinação para toda execução
    int ar[52];
    size_t i;
    //Baralho padrão, não embaralhado
    for(i=0; i<52; i++)
    {
        ar[i] = i;
    }

    shuffleArray(ar, 52); // Embaralhado


    for(i=0; i<=3; i++)
    {
        top_slots[i] = createPile();
        base_slots[i] = createPile();
        mid_slots[i] = createPile();
        mid_slots[i+4] = createPile(); //Não precisa de 2 loops
    }

    //Colocar as cartas nos mid_slots
    for(i=0; i<52; i++){
        addNewItemPile(mid_slots[i%8], ar[i]);
    }

    //Inicializar status do jogo
    gameStatus = GAME_STATUS_START;
}

void writeCards()
{
    if(!mid_slots[0])
        return;

    int i;
    Item* item;
    char *c = malloc(sizeof(char[3]));

    for(i=0; i<8; i++)
    {
        if(mid_slots[i])
        {
            item = mid_slots[i]->start;
            while(item->next != NULL)
            {
                cardToStr(item, c);
                printf("%s   ", c);
                item = item->next;
            }
            printf("\n");
        }
    }
    free(c);
}

//int moveCardToPile(Pile* from, Pile* to)
//Move a carta do topo da pilha from para a pilha to
//retorna -1 se nao conseguir, 0 se conseguir
int moveCardToPile(Pile* from, Pile* to)
{
    if(from == NULL || to == NULL)
        return -1;

    Item *prev = removeTopItemPile(from);
    if(prev == NULL)
        return -1;

    return addItemPile(to, prev);
}

int moveCardToBase(Pile *from)
{
    if(from == NULL)
        return -1;

    Item *prev = removeTopItemPile(from);
    if(prev == NULL)
        return -1;

    return addItemPile(base_slots[getCardNipe(prev)], prev);
}


//int getCardNipe
//retorna 0 para copas, 1 para ouros, 2 para paus, 3 para espadas, -1 para erro
int getCardNipe(Item* card)
{
    if(card != NULL)
        return (int)(card->value / 13);
    return -1;
}

//int getCardNumber
//retorna o número da carta, de 0 a 12
//0=A, 1=2, 2=3, etc...
int getCardNumber(Item* card)
{
    if(card != NULL)
        return (int)(card->value % 13);
    return -1;
}

//int canMove(Pile *from, Pile *to)
//retorna 1 se é possível mexer a carta do topo de from para to
//retorna 0 se não
//Toma como base apenas as regras do jogo para as pilhas do meio
//Não leva em consideração as pilhas do topo direito, que têm funcionamento diferente.
int canMove(Pile *from, Pile *to)
{
    if(from == NULL || to == NULL)
        return 0;

    if(from->start == NULL)
        return 0;

    Item *toMove = from->start;
    Item *toReceive = to->start;
    if(toReceive == NULL)
        return 1; //Sem carta = pode mecher qualquer carta

    //verificar se o número é válido
    if(getCardNumber(toMove) != getCardNumber(toReceive)-1)
        return 0; //só pode mexer uma carta 1 numero menor do que a carta alvo, ex 2 para 3

    //verificar se o nipe é válido
    //0 não pode combinar com 1, 2 não pode combinar com 3.
    //A XOR C, pois se o bit da esquerda é diferente, torna o movimento válido
    if((getCardNipe(toMove) ^ getCardNipe(toReceive)) > 1) //>1 significa 10 ou 11 vs 00 ou 01
        return 1;

    return 0;
}

//int canMoveToBase(Pile *from)
//retorna 1 de a carta pode ser posta em uma pilha base
//retorna 0 se não
int canMoveToBase(Pile *from)
{
    if(from == NULL || base_slots[0] == NULL)
        return -1;

    Item *toMove = from->start;
    if(toMove == NULL)
        return -1;


    //Verifica na pilha do nipe da carta
    Item *toReceive = base_slots[getCardNipe(toMove)]->start;
    if(toReceive != NULL)
    {
        if(getCardNumber(toReceive) == getCardNumber(toMove)-1)
            return 1;
    }
    else if(getCardNumber(toMove) == 0)
        return 1;

    //Verifica se a carta na pilha é antecessora a esta


    return 0;
}

// Função main() executa o programa.
int main()
{
    initializeCards();
    drawBoard();
    //writeCards();
    return 0;
}
