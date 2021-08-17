//20.2.4002
//Marcus Vinicius Pereira Xavier
//Turma 32

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "main.h"
#include "utils/colors.h"
#include "jogador.h"
#include "menu.h"
void printarTabuleiro(Jogador player1, Jogador player2);
int main(int argc, char *argv[])
{   
    //Informações úteis para todo o programa;
    Jogador jogador1, jogador2;
    //
    jogador1.qtd_pecas = 12; jogador2.qtd_pecas = 12;
    preencherMatriz(&jogador1.pecas, 'x');
    preencherMatriz(&jogador2.pecas, 'o');
    printMenu(&jogador1, &jogador2);
    printarTabuleiro(jogador1, jogador2);
    printf("%s\n%s\n",jogador1.nome, jogador2.nome); //* Só pra testar mesmo
    
    return 0;
}

void printarTabuleiro(Jogador player1, Jogador player2)
{
    char matriz[8][8];
    for (int i = 0; i < 8; i++) for (int j = 0; j <8; j++) matriz[i][j] = ' ';
    for(int linha = 0; linha < player1.qtd_pecas; linha ++){
        matriz[player1.pecas[linha][0]][player1.pecas[linha][1]] = player1.pecas[linha][2];
    }
    for(int linha = 0; linha < player2.qtd_pecas; linha ++){
        matriz[player2.pecas[linha][0]][player2.pecas[linha][1]] = player2.pecas[linha][2];
    }

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(i % 2 == 0){
                if(j % 2 == 0){
                    printf(BG_WHITE(BLACK(" %c ")), matriz[i][j]);
                }
                else{
                    printf(BG_BLACK(" %c "), matriz[i][j]);
                }
            }
            else{
                if(j % 2 != 0){
                    printf(BG_WHITE(BLACK(" %c ")), matriz[i][j]);
                }
                else{
                    printf(BG_BLACK(" %c "), matriz[i][j]);
                }
            }
        }
        printf("\n");
    }
    printf("\n");
}

