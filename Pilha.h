/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Pilha.h
 * Author: jose
 *
 * Created on 5 de Março de 2018, 20:02
 */

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
//////////////////////////Funcoes de Pilha(stack)//////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////


#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED

#include <stdlib.h>

// Definir Pilha(Pile) e suas funções para o uso no jogo
// Usar nomes genéricos para usos futuros

typedef struct ItemList
{
    int value; //No futuro, achar um método de transformar este tipo em algo mais dinâmico
    struct ItemList *next;
}Item;

typedef struct PileStructure
{
    Item *start;
    int length; // length ao inves de size, pois size ja é definido para outras coisas
}Pile;


// Pile* createPile();
// Retorna uma NOVA pilha inicializada
// Retorna NULL caso não consiga criar uma nova pilha
Pile* createPile();


// int addItemPile(Pile* pile, int value)
// Cria e adiciona um novo item à pilha, com valor value
// Retorna -1 se não for bem sucedido, 0 se for bem sucedido
int addNewItemPile(Pile* pile, int value);
int addItemPile(Pile* pile, Item* item);

// Item* removeTopItemPile(Pile* pile)
// remove o primeiro item da pilha
// retorna NULL se houver algum erro, ou o item removido para uso futuro
// O "next" do item removido vira NULL, pois ele é removido da pilha.
// Nota: o item NÃO É DELETADO DA MEMÓRIA.
Item* removeTopItemPile(Pile* pile);

// int deleteItem(Item* item)
// deleta e remove o item da memória
// retorna -1 se o next não for NULL, pois siginifica que ainda está em uma pilha
// retorna 0 se for bem sucedido
int deleteItem(Item* item);

// int deletePile(Pile* pile)
// deleta a pilha e remove da memória
// remove e deleta qualquer item que esteja na pilha
// retorna -1 se a pilha não existir
int deletePile(Pile* pile);

//Item* getPreviousItemOnPile(Item *item, Pile *pile)
// retorna o item anterior ao item requerido na pilha
// retorna o próprio item se ele for o topo da pilha
// retorna NULL se não for possível, ou se o item não estiver na pilha
Item* getPreviousItemOnPile(Item *item, Pile *pile);

#endif // PILHA_H_INCLUDED