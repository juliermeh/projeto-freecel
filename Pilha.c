#include "Pilha.h"

// Pile* createPile();
// Retorna uma NOVA pilha inicializada
// Retorna NULL caso não consiga criar uma nova pilha
Pile* createPile()
{
    Pile* newPile = (Pile*)malloc(sizeof(Pile));
    if(newPile == NULL) //se não puder achar memória no sistema
        return NULL;

    newPile->start = NULL;
    newPile->length = 0;
    return newPile;
}


// int addItemPile(Pile* pile, int value)
// Cria e adiciona um novo item à pilha, com valor value
// Retorna -1 se não for bem sucedido, 0 se for bem sucedido
int addNewItemPile(Pile* pile, int value)
{
    Item* newItem;
    if(pile == NULL)
        return -1;

    newItem = (Item*)malloc(sizeof(Item));
    if(newItem == NULL)
        return -1;

    newItem->value = value;
    newItem->next = pile->start;
    pile->start = newItem;
    pile->length++;
    return 0;
}

int addItemPile(Pile* pile, Item* item)
{
    if(item == NULL)
        return -1;

    if(item->next != NULL) //se o next != NULL, ele está em alguma pilha
        return -1;

    item->next = pile->start;
    pile->start = item;
    pile->length++;
    return 0;
}

// Item* removeTopItemPile(Pile* pile)
// remove o primeiro item da pilha
// retorna NULL se houver algum erro, ou o item removido para uso futuro
// O "next" do item removido vira NULL, pois ele é removido da pilha.
// Nota: o item NÃO É DELETADO DA MEMÓRIA.
Item* removeTopItemPile(Pile* pile)
{
    Item* removedItem;
    if(pile == NULL || pile->length <= 0)
        return NULL;

    removedItem = pile->start;
    pile->start = removedItem->next;
    pile->length--;
    removedItem->next = NULL;
    return removedItem;
}

// int deleteItem(Item* item)
// deleta e remove o item da memória
// retorna -1 se o next não for NULL, pois siginifica que ainda está em uma pilha
// retorna 0 se for bem sucedido
int deleteItem(Item* item)
{
    if(item == NULL || item->next != NULL)
        return -1;

    free(item);
    return 0;
}

// int deletePile(Pile* pile)
// deleta a pilha e remove da memória
// remove e deleta qualquer item que esteja na pilha
// retorna -1 se a pilha não existir
int deletePile(Pile* pile)
{
    Item* item;
    if(pile == NULL)
        return -1;

    while(pile->length > 0)
    {
        item = removeTopItemPile(pile); //reduz o valor da pilha automaticamente
        if(item != NULL)
            deleteItem(item);
    }

    free(pile);
    return 0;
}

//Item* getPreviousItemOnPile(Item *item, Pile *pile)
// retorna o item anterior ao item requerido na pilha
// retorna o próprio item se ele for o topo da pilha
// retorna NULL se não for possível, ou se o item não estiver na pilha
Item* getPreviousItemOnPile(Item *item, Pile *pile)
{
    if(item == NULL || pile == NULL)
        return NULL;

    Item* Q = pile->start;
    if(Q == NULL) return NULL;
    if(Q == item) return item;

    while(Q->next != NULL)
    {
        if(Q->next == item) return Q;

        Q = Q->next;
    }

    return NULL;
}