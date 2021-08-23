//20.2.4002
//Marcus Vinicius Pereira Xavier
//Turma 32

#include "utils/colors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "jogador.h"
#include "menu.h"
#include "jogo.h"

int verifyIfGameEnded(Jogador jogador1, Jogador jogador2, int *contador);
int main(int argc, char *argv[])
{   
    //Informações úteis para todo o programa;
    Jogador jogador1, jogador2;
    //
    int rodada;
    char nome_arquivo[50] = "\0";
    int contador_empate = 0;
    printMenu(&jogador1, &jogador2, &rodada, nome_arquivo);
    desenharTabuleiro(jogador1, jogador2);
    while(!verifyIfGameEnded(jogador1, jogador2, &contador_empate))
    {
        if(rodada == 1){
            jogada(&jogador1, &jogador2, &rodada, nome_arquivo);
        }else if(rodada == 2){
            jogada(&jogador2, &jogador1, &rodada, nome_arquivo);
        }
        desenharTabuleiro(jogador1, jogador2);
    }    
    return 0;
}

int verifyIfGameEnded(Jogador jogador1, Jogador jogador2, int *contador)
{
    int damas_1, damas_2;
    if(jogador1.qtd_pecas == 0 || jogador2.qtd_pecas == 0){
        if(jogador1.qtd_pecas > jogador2.qtd_pecas){
            printf(BOLD("\nO jogador %s venceu!\n"), jogador1.nome);
        }else{
            printf(BOLD("\nO jogador %s venceu!\n"), jogador2.nome);
        }
        return 1;
    }
    damas_1 = contarQtdDamas(jogador1);
    damas_2 = contarQtdDamas(jogador2);
    if(jogador1.qtd_pecas < 3 && jogador2.qtd_pecas < 3){
        if(*contador == 10){
            printf(BOLD("\nJogo empatado!\n"));
            return 1;
        }
        int test1 = (damas_1 == 2 && damas_2 == 2) || (damas_1 == 1 && damas_2 == 2);
        int test2 = (damas_1 == 2 && damas_2 == 1) || (damas_1 == 1 && damas_2 == 1);
        if( test1 || test2) *contador = *contador + 1;
    }
    
    return 0;
}