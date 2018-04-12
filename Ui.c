/* IFPB - Equipe: Julierme Jadon, José Ferreira, Alisson, Juvenal */
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

        Em qual coluna está o cartão que você quer levar?

        (depois de selecionar a carta)
        Para onde você quer enviar este cartão?
        Opções válidas: 1,2,3,4, a, b, c, d, e, f, g, h, BASE
        Entre com o alvo: _


       // NOTA: opïnioes possiveis tambem sao o, out, base, nipe


    */
	printf("====================================================\n");
	printf("Bem-vindo ao Freecel! Abaixo, voce vera suas cartas!\n");
	printf("====================================================\n \n");
    printf(" #1    #2    #3    #4       \3     \4     \5     \6 \n");
    for(i=0; i<4; i++)
        drawCard(top_slots[i]->start);

    printf("| ");

    for(i=0; i<4; i++)
        drawCard(base_slots[i]->start);
    //base e topo escritas

    printf("\n");
    printf("------------------------------------------------- \n");

    //escrever o meio
    drawMiddle();

    printf("\n\n");
    //Perguntas
    drawRequestHandle();

    //Solicitar o usuario a executar um comando
    if(gameStatus != GAME_STATUS_DEFEAT && gameStatus != GAME_STATUS_VICTORY)
        receiveUserInput();
}



void drawMiddle()
{
    //Funcao separada para organizar
    //Para o jogo, eh mais facil manter pilhas de baixo para cima (pelo display)
    //Porem para escrever, eh mais facil utilizar pilhas de cima para baixo

    //Entï¿½o vou criar novas pilhas temporarias que sï¿½o cï¿½pias das globais
    //E utilizar estas para imprimir
    if(mid_slots[0] == NULL)
        return;

    Pile *tempPile[8];
    Item *tempItem;
    Item *tmpVector[8];
    int i, j, max_length;
    max_length = -1; //Inicializacao necessaria para garantir o uso

    for(i=0; i<8; i++)
    {
        //Terei de criar NOVAS cartas, pois as originais precisam manter seus atributos
        //Lembrar de deletar tudo ao fim da funcao
        tempPile[i] = createPile();
        tempItem = mid_slots[i]->start;
        while(tempItem != NULL)
        {
            addNewItemPile(tempPile[i], tempItem->value);
            tempItem = tempItem->next;
        }

        max_length = max(max_length, tempPile[i]->length); //servico usadas mais tarde

    }

    //Desenhar
    for(i = 0; i < max_length; i++)
    {
        for(j = 0; j < 8; j++)
        {
            if(i == 0)
                tmpVector[j] = tempPile[j]->start;
            else if(tmpVector[j] != NULL)
            {
                tmpVector[j] = tmpVector[j]->next;
            }

            drawCard(tmpVector[j]);
            if(j == 3)
                printf("  "); //Alinhar as cartas
        }
        printf("\n");
    }


    printf("  a     b     c     d       e     f     g     h   \n");

    //deletar pilas temporarias
    for(i= 0; i < 8; i++)
        deletePile(tempPile[i]);
    //funcoes em pile.h ja lidam com os items criados
}

void drawRequestHandle()
{
    //Funcao para escrever as perguntas
    switch(gameStatus)
    {
    case GAME_STATUS_START:
        
    case GAME_STATUS_CHOSECARD:
        printf("Escolha a fileira da carta ao qual deseja mover!");
        printf("\nOpcoes validas: a, b, c, d, e, f, g, h, 1, 2, 3, 4\n");
        break;
    case GAME_STATUS_CHOSETARGET:
        printf("Escolha a fileira de destino da carta ");
        drawCard(selectedSlot->start);
        printf("\nOpcoes validas: a, b, c, d, e, f, g, h, 1, 2, 3, 4\n");
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
        else
        {
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
            //top_slots só pode receber um cartão de cada vez
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
        else
        {
            printf("Selecao Invalida! \nOpcoes validas: a,b,c,d,e,f,g,h,1,2,3,4!");
            free(c);
            receiveUserInput();
            return;
        }

        if(canMove(selectedSlot, targetSlot) == 1)
        {
            moveCardToPile(selectedSlot, targetSlot);
            checkGameStatus();
        }
        else
        {
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

    //se o length dos top_slots for 13, eles estao cheios e o jogo acabou em vitoria
    if(top_slots[0]->length == 13 && top_slots[1]->length == 13 && top_slots[2]->length == 13 && top_slots[4]->length == 13)
    {
        gameStatus = GAME_STATUS_VICTORY;
        return;
    }

    //Se nenhum movimento for possivel, o jogo resulta em derrota
    Pile *a, *b;
    int j;
    int isDefeat = 1; //Assume que ha derrota inicialmente; se achar um movimento valido, vira vitoria

    a = mid_slots[0];
    for(j=0; j<8; j++)
    {
        b = mid_slots[j];
        if(canMove(a, b) == 1 || canMove(b, a) == 1)
        {
            isDefeat = 0;
            break; //Ja foi determinado que nao houve derrota
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
