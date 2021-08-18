//20.2.4002
//Marcus Vinicius Pereira Xavier
//Turma 32

#include <stdio.h>
#include <stdlib.h>
// #include <ctype.h>
#include <string.h>
#include "main.h"
#include "utils/colors.h"
#include "jogador.h"
#include "menu.h"
#include "jogo.h"

void jogada(Jogador *jogador);
// void printarTabuleiro(Jogador player1, Jogador player2);
int main(int argc, char *argv[])
{   
    //Informações úteis para todo o programa;
    Jogador jogador1, jogador2;
    //
    jogador1.qtd_pecas = 12; jogador2.qtd_pecas = 12;
    preencherMatriz(&jogador1.pecas, 'o');
    preencherMatriz(&jogador2.pecas, 'x');
    printMenu(&jogador1, &jogador2);
    desenharTabuleiro(jogador1, jogador2);
    for(int i = 0; i < 8; i++)
    {
        if(i % 2 == 0){
            jogada(&jogador1);
        }
        else{
            jogada(&jogador2);
        }
        
    }
    printf("%s\n%s\n",jogador1.nome, jogador2.nome); //* Só pra testar mesmo
    
    return 0;
}

void jogada(Jogador *jogador)
{
    char message[50], input[50];
    char c1, c2;
    int i1, i2, qtd_input;
    sprintf(message, "%s, é a sua vez: ", jogador->nome);
    getInputFromUser(message, input);
    qtd_input = sscanf(input,"%c%d %c%d", &c1, &i1, &c2, &i2);
    while(qtd_input != 4){
        printf("Por favor, insira um input válido\n");
        getInputFromUser(message, input);
        qtd_input = sscanf(input,"%c%d %c%d", &c1, &i1, &c2, &i2);
    }
    printf("Sua jogada %c%d %c%d\n", c1,i1,c2,i2);
}