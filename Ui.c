#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include "main.h"
#include "Pilha.h"

void drawCard(Item *card)
{
    if(card != NULL)
    {
        char *c = malloc(sizeof(char[3]));
        cardToStr(card, c);
        printf("{%s} ", c);
        free(c);
    }
    else
    printf("{   } ");
}


void drawBoard()
{
    system("cls");
    int i;

    if(top_slots[0] == NULL)
        return;
/*

      #1   #2    #3    #4       C     O     P     E
    {   } {   } {   } {   } | {   } {   } {   } {   }
    -------------------------------------------------
    {   } {   } {   } {   }   {   } {   } {   } {   }
    {   } {   } {   } {   }   {   } {   } {   } {   }
    {   } {   } {   } {   }   {   } {   } {   } {   }
    {   } {   } {   } {   }   {   } {   } {   } {   }
    {   } {   } {   } {   }   {   } {   } {   } {   }
    {   } {   } {   } {   }   {   } {   } {   } {   }
    {   } {   } {   } {   }   {   } {   } {   } {   }
    {   } {   } {   } {   }   {   } {   } {   } {   }
    {   } {   } {   } {   }   {   } {   } {   } {   }
    {   } {   } {   } {   }   {   } {   } {   } {   }
      a     b     c     d       e     f     g     h

    In which column is the card you want to take? _

    (depois de selecionar a carta)
    To where you want to send this card?
    Valid options: 1,2,3,4,a,b,c,d,e,f,g,h,BASE
    Enter with the target: _


   // NOTA: opções possíveis também são o, out, base, nipe


*/

    printf(" #1    #2    #3    #4       \3     \4     \5     \6 \n");
    for(i=0;i<4;i++)
        drawCard(top_slots[i]->start);

    printf("| ");

    for(i=0;i<4;i++)
        drawCard(base_slots[i]->start);
    //base e topo escritas

    printf("\n");
    printf("------------------------------------------------- \n");

    //escrever o meio
    drawMiddle();

    printf("\n\n");
    //Perguntas
    drawRequestHandle();

    //Solicitar o usuário a executar um comando
    if(gameStatus != GAME_STATUS_DEFEAT && gameStatus != GAME_STATUS_VICTORY)
        receiveUserInput();
}



void drawMiddle()
{
    //Função separada para organizar
    //Para o jogo, é mais fácil manter pilhas de baixo para cima (pelo display)
    //Porém para escrever, é mais fácil utilizar pilhas de cima para baixo

    //Então vou criar novas pilhas temporárias que são cópias das globais
    //E utilizar estas para imprimir
    if(mid_slots[0] == NULL)
        return;

    Pile *tempPile[8];
    Item *tempItem;
    Item *tmpVector[8];
    int i, j, max_length;
    max_length = -1; //Inicialização necessária para garantir o uso

    for(i=0;i<8;i++)
    {
        //Terei de criar NOVAS cartas, pois as originais precisam manter seus atributos
        //Lembrar de deletar tudo ao fim da função
        tempPile[i] = createPile();
        tempItem = mid_slots[i]->start;
        while(tempItem != NULL)
        {
            addNewItemPile(tempPile[i], tempItem->value);
            tempItem = tempItem->next;
        }

        max_length = max(max_length, tempPile[i]->length); //serão usadas mais tarde

    }

    //Desenhar
    for(i = 0; i < max_length; i++)
    {
        for(j = 0; j < 8; j++)
        {
            if(i == 0)
                tmpVector[j] = tempPile[j]->start;
            else if(tmpVector[j] != NULL){
                tmpVector[j] = tmpVector[j]->next;
            }

            drawCard(tmpVector[j]);
            if(j == 3)
                printf("  "); //Alinhar as cartas
        }
        printf("\n");
    }


    printf("  a     b     c     d       e     f     g     h   \n");

    //deletar pilas temporárias
    for(i= 0; i < 8; i++)
        deletePile(tempPile[i]);
    //funçõoes em pile.h já lidam com os items criados
}

void drawRequestHandle()
{
    //Função para escrever as perguntas
    switch(gameStatus)
    {
        case GAME_STATUS_START:
            printf("Bem-vindo ao Freecel! Acima, voce vera suas cartas!\n");
        case GAME_STATUS_CHOSECARD:
            printf("Escolha a fileira da carta ao qual deseja mover!");
            printf("\nOpcoes validas: a, b, c, d, e, f, g, h, 1, 2, 3, 4\n");
            break;
        case GAME_STATUS_CHOSETARGET:
            printf("Escolha a fileira de destino da carta ");
            drawCard(selectedSlot->start);
            printf("\nOpcoes validas: a, b, c, d, e, f, g, h, 1, 2, 3, 4, base\n");
            break;
        case GAME_STATUS_DEFEAT:
            printf("Nao ha mais possibilidades de movimento. Jogo Encerrado!");
            break;
        case GAME_STATUS_VICTORY:
            printf("Parabens, voce ganhou!!!");
            break;
    }
}

void receiveUserInput()
{
    char *c = malloc(sizeof(char[5]));
    int i;
    scanf("%5s", c);
    //verificar estado do jogo
    if(gameStatus == GAME_STATUS_START || gameStatus == GAME_STATUS_CHOSECARD)
    {
        //if(c[0] == 'a') i = 0;
        //if
        if(c[0] >= 'a' && c[0] <= 'h')
        {
            i = (int)(c[0] - 'a'); //a=0, b=1, c=2, d=3, e=4, f=5, g=6, h=7
            selectedSlot = mid_slots[i];
        }
        else if(c[0] >= '1' && c[0] <= '4')
        {
            i = (int)(c[0] - '1');
            selectedSlot = top_slots[i];
        }
        else{
            printf("Selecao Invalida! \nAs opcoes validas sao: a,b,c,d,e,f,g,h,1,2,3,4!\n");
            free(c);
            receiveUserInput();
            return;
        }


        if(selectedSlot->start == NULL)
        {
            printf("Nesta pilha nao ha cartas para mover! Por favor escolha outro lugar.\n");
            free(c);
            receiveUserInput();
            return;
        }

        gameStatus = GAME_STATUS_CHOSETARGET;
    }
    else if(gameStatus == GAME_STATUS_CHOSETARGET)
    {
        Pile *targetSlot;
        if(strcasecmp(c, "base") == 0)
        {
            strcpy(c, "     ");
            free(c);
            if(canMoveToBase(selectedSlot) == 1)
            {
                moveCardToBase(selectedSlot);
                checkGameStatus();
                selectedSlot = NULL;
                drawBoard();
                return;
            }
            else
            {
                selectedSlot = NULL;
                printf("Movimento Invalido! Por favor, selecione outra carta.\n");
                gameStatus = GAME_STATUS_CHOSECARD;
                receiveUserInput();
                return;
            }

        }
        else if(c[0] >= 'a' && c[0] <= 'h')
        {
            i = (int)(c[0] - 'a'); //a=0, b=1, c=2, d=3, e=4, f=5, g=6, h=7
            targetSlot = mid_slots[i];
        }
        else if(c[0] >= '1' && c[0] <= '4')
        {
            i = (int)(c[0] - '1');
            targetSlot = top_slots[i];
            //top_slots may only receive one card at a time
            if(targetSlot->length > 0)
            {
                printf("Movimento invalido! Por favor, selecione outra carta para mover.\n");
                free(c);
                selectedSlot = NULL;
                gameStatus = GAME_STATUS_CHOSECARD;
                receiveUserInput();
                return;
            }
        }
        else{
            printf("Selecao Invalida! \nOpcoes validas: a,b,c,d,e,f,g,h,1,2,3,4,base!");
            free(c);
            receiveUserInput();
            return;
        }

        if(canMove(selectedSlot, targetSlot) == 1)
        {
            moveCardToPile(selectedSlot, targetSlot);
            checkGameStatus();
        }
        else{
            printf("Movimento invalido! Por favor, selecione outra carta para mover.\n");
            free(c);
            selectedSlot = NULL;
            gameStatus = GAME_STATUS_CHOSECARD;
            receiveUserInput();
            return;
        }
    }

    free(c);
    drawBoard();
}

void checkGameStatus()
{
    //Ler os slots e verificar se o jogo acabou, e determinar o status do jogo

    //se o length dos top_slots for 13, eles estão cheios e o jogo acabou em vitória
    if(top_slots[0]->length == 13 && top_slots[1]->length == 13 && top_slots[2]->length == 13 && top_slots[4]->length == 13){
        gameStatus = GAME_STATUS_VICTORY;
        return;
    }

    //Se nenhum movimento for possível, o jogo resulta em derrota
    Pile *a, *b;
    int j;
    int isDefeat = 1; //Assume que há derrota inicialmente; se achar um movimento válido, vira vitória

    a = mid_slots[0];
    for(j=0; j<8; j++)
    {
        b = mid_slots[j];
        if(canMove(a, b) == 1 || canMove(b, a) == 1){
            isDefeat = 0;
            break; //Já foi determinado que não há derrota
        }
        if(j<4)
        {
            b = top_slots[j];
            if(top_slots[j]->length == 0)
            {
                isDefeat = 0;
                break;
            }
        }
    }

    if(isDefeat == 1)
        gameStatus = GAME_STATUS_DEFEAT;
    else
        gameStatus = GAME_STATUS_CHOSECARD;

}
